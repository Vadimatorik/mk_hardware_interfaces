#include "uart.h"

#ifdef HAL_UART_MODULE_ENABLED

Uart::Uart( const uartCfg* const cfg, uint32_t countCfg  ) :
	cfg( cfg ), countCfg( countCfg ) {
	this->uart.Init.HwFlowCtl							= UART_HWCONTROL_NONE;
	this->uart.Init.OverSampling						= UART_OVERSAMPLING_8;
	this->uart.Init.Parity								= UART_PARITY_NONE;
	this->uart.Init.StopBits							= UART_STOPBITS_1;
	this->uart.Init.WordLength							= UART_WORDLENGTH_8B;

	if ( cfg->dmaTx != nullptr ) {
		this->uart.hdmatx = &this->dmaTx;

		this->uart.hdmatx->Init.Direction				= DMA_MEMORY_TO_PERIPH;
		this->uart.hdmatx->Init.PeriphInc				= DMA_PINC_DISABLE;
		this->uart.hdmatx->Init.MemInc					= DMA_MINC_ENABLE;
		this->uart.hdmatx->Init.PeriphDataAlignment		= DMA_PDATAALIGN_BYTE;
		this->uart.hdmatx->Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE;
		this->uart.hdmatx->Init.Mode					= DMA_NORMAL;
		this->uart.hdmatx->Init.Priority				= DMA_PRIORITY_HIGH;
		this->uart.hdmatx->Init.FIFOMode				= DMA_FIFOMODE_DISABLE;
	}

	this->uart.obj										= this;

	this->m = USER_OS_STATIC_MUTEX_CREATE( &this->mb );
	this->s = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &this->sb );
}

BaseResult Uart::reinit ( uint32_t numberCfg ) {
	if ( numberCfg >= this->countCfg )
		return BaseResult::errInputValue;

	this->clkDeinit();

	this->uart.Instance									= cfg[ numberCfg ].uart;
	this->uart.Init.Mode								= cfg[ numberCfg ].mode;
	this->uart.Init.BaudRate							= cfg[ numberCfg ].baudrate;
	this->uart.hdmatx->Instance							= this->cfg[ numberCfg ].dmaTx;
	this->uart.hdmatx->Init.Channel						= this->cfg[ numberCfg ].dmaTxCh;

	if ( cfg[ numberCfg ].dmaTx != nullptr ) {
		this->uart.hdmatx								= &this->dmaTx;
		this->uart.hdmatx->Parent						= &this->uart;
		dmaClkOn( this->cfg->dmaTx );
	}

	this->clkInit();

	HAL_StatusTypeDef r;

	r = HAL_UART_DeInit( &this->uart );
	if ( r != HAL_OK )
		return BaseResult::errInit;

	r = HAL_UART_Init( &this->uart );
	if ( r != HAL_OK )
		return BaseResult::errInit;

	if ( this->cfg->de != nullptr )    	this->cfg->de->reset();

	return BaseResult::ok;
}

BaseResult Uart::on ( void ) {
	if (   this->uart.gState == HAL_UART_STATE_RESET )
		return BaseResult::errInit;

	__HAL_UART_ENABLE( &this->uart );
	return BaseResult::ok;
}

void Uart::off ( void ) {
	__HAL_UART_DISABLE( &this->uart );
}

BaseResult Uart::tx (	const uint8_t*		const txArray,
						uint16_t			length,
						uint32_t			timeoutMs	) {
	USER_OS_TAKE_MUTEX( this->m, portMAX_DELAY );
	USER_OS_TAKE_BIN_SEMAPHORE ( this->s, 0 );

	if ( this->cfg->de != nullptr )    	this->cfg->de->set();

	if ( this->uart.hdmatx != nullptr ) {												// Если передача идет по DMA.
		HAL_UART_Transmit_DMA( &this->uart, ( uint8_t* )txArray, length );
	} else {																	// Если по прерываниям.
		HAL_UART_Transmit_IT( &this->uart, ( uint8_t* )txArray, length );
	}

	BaseResult rv = BaseResult::errTimeOut;
	if ( USER_OS_TAKE_BIN_SEMAPHORE ( this->s, timeoutMs ) == pdTRUE ) {
		rv = BaseResult::ok;
	}

	if ( this->cfg->de != nullptr )    		this->cfg->de->reset();

	USER_OS_GIVE_MUTEX( this->m );
	return rv;
}

BaseResult Uart::getByteWitchout (	uint8_t* retrunData	) {
	if (   this->uart.gState == HAL_UART_STATE_RESET )
		return BaseResult::errInit;

	/// Если есть данные.
	if ( __HAL_UART_GET_FLAG( &this->uart, UART_FLAG_RXNE ) ) {
		*retrunData = this->uart.Instance->DR;
		return BaseResult::ok;
	}

	return BaseResult::errNotData;
}

BaseResult Uart::getByte (	uint8_t*		retrunData,
							uint32_t		timeoutMs	) {
	if (   this->uart.gState == HAL_UART_STATE_RESET )
		return BaseResult::errInit;

	/// Если есть данные.
	if ( __HAL_UART_GET_FLAG( &this->uart, UART_FLAG_RXNE ) ) {
		*retrunData = this->uart.Instance->DR;
		return BaseResult::ok;
	}

	USER_OS_TAKE_MUTEX( this->m, portMAX_DELAY );
	USER_OS_TAKE_BIN_SEMAPHORE ( this->s, 0 );

	volatile BaseResult rv = BaseResult::errTimeOut;
	if ( USER_OS_TAKE_BIN_SEMAPHORE ( this->s, timeoutMs ) == pdTRUE ) {
		*retrunData = this->uart.Instance->DR;
		rv = BaseResult::ok;
	}

	USER_OS_GIVE_MUTEX( this->m );

	return rv;
}

void Uart::irqHandler ( void ) {
	HAL_UART_IRQHandler( &this->uart );
}

extern "C" {

void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart ) {
	((Uart*)huart->obj)->giveSemaphore();
}

void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart ) {
	((Uart*)huart->obj)->giveSemaphore();
}

}


// Private.
void Uart::giveSemaphore ( void ) {
	if ( this->s ) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR ( this->s, &xHigherPriorityTaskWoken);
	}
}

bool Uart::clkInit ( void ) {
	switch ( ( uint32_t )this->cfg->uart ) {
#ifdef USART1
	case	USART1_BASE:	 __HAL_RCC_USART1_CLK_ENABLE();		return true;
#endif
#ifdef USART2
	case	USART2_BASE:	 __HAL_RCC_USART2_CLK_ENABLE();		 return true;
#endif
#ifdef USART3
	case	USART3_BASE:	 __HAL_RCC_USART3_CLK_ENABLE();		return true;
#endif
#ifdef UART4
	case	UART4_BASE:		__HAL_RCC_UART4_CLK_ENABLE();		return true;
#endif
#ifdef UART5
	case	UART5_BASE:		__HAL_RCC_UART5_CLK_ENABLE();		return true;
#endif
#ifdef UART6
	case	UART6_BASE:		__HAL_RCC_UART6_CLK_ENABLE();		return true;
#endif
#ifdef UART7
	case	UART7_BASE:		__HAL_RCC_UART7_CLK_ENABLE();		return true;
#endif
#ifdef UART8
	case	UART8_BASE:		__HAL_RCC_UART8_CLK_ENABLE();		return true;
#endif
	};
	return false;
}

bool Uart::clkDeinit ( void ) {
	switch ( ( uint32_t )this->cfg->uart ) {
#ifdef USART1
	case	USART1_BASE:	 __HAL_RCC_USART1_CLK_DISABLE();	 return true;
#endif
#ifdef USART2
	case	USART2_BASE:	 __HAL_RCC_USART2_CLK_DISABLE();	 return true;
#endif
#ifdef USART3
	case	USART3_BASE:	 __HAL_RCC_USART3_CLK_DISABLE();	 return true;
#endif
#ifdef UART4
	case	UART4_BASE:		__HAL_RCC_UART4_CLK_DISABLE();		return true;
#endif
#ifdef UART5
	case	UART5_BASE:		__HAL_RCC_UART5_CLK_DISABLE();		return true;
#endif
#ifdef UART6
	case	UART6_BASE:		__HAL_RCC_UART6_CLK_DISABLE();		return true;
#endif
#ifdef UART7
	case	UART7_BASE:		__HAL_RCC_UART7_CLK_DISABLE();		return true;
#endif
#ifdef UART8
	case	UART8_BASE:		__HAL_RCC_UART8_CLK_DISABLE();		return true;
#endif
	};
	return false;
}

#endif
