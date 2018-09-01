/*!
 *	@startuml
 *
 *	class AdcOneChannel {
 *		{field}-
 *		{field}-
 *		{field}-
 *		{field}-
 *		__Constructor__
 *		{method}+
 *		__Public methods__
 *		{method}+
 *		__Private methods__
 *		{method}-
 *		{method}-
 *	}
 *
 *	@enduml
 */

#pragma once

#ifdef __cplusplus

#include "platform.h"

#ifdef HAL_UART_MODULE_ENABLED

#include "dma.h"
#include "pin.h"
#include "mc_hardware_interfaces_uart.h"
#include "user_os.h"

struct uartCfg {
	USART_TypeDef*				uart;
	Pin*						de;
	uint32_t					baudrate;
	uint32_t					mode;						// UART_MODE_RX/UART_MODE_TX/UART_MODE_TX_RX.
	DMA_Stream_TypeDef*			dmaTx;						// Из мерии DMAx_Streamx.
	uint32_t					dmaTxCh;					// Из серии DMA_CHANNEL_x.
};

class Uart : public UartBase {
public:
	Uart( const uartCfg* const cfg, const uint32_t countCfg = 1 );

	BaseResult		reinit						( uint32_t numberCfg					 = 0 );

	BaseResult		on							(	void	);
	void			off							(	void	);

	BaseResult		tx							(	const uint8_t*		const txArray,
													uint16_t			length			=	1,
													uint32_t			timeoutMs		=	100	);

	BaseResult		getByte						(	uint8_t*			retrunData,
													uint32_t			timeoutMs		=	100	);

	BaseResult		getByteWitchout				(	uint8_t* 			retrunData	);

	void			irqHandler					(	void	);

	/// Для внутреннего пользования HAL-а.
	void			giveSemaphore				(	void	);

private:
	bool 			clkInit						(	void	);
	bool			clkDeinit					(	void	);

private:
	const uartCfg*								const cfg;
	const uint32_t								countCfg;

	DMA_HandleTypeDef							dmaTx;
	UART_HandleTypeDef							uart;
	USER_OS_STATIC_BIN_SEMAPHORE				s = nullptr;
	USER_OS_STATIC_MUTEX						m = nullptr;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER			sb;
	USER_OS_STATIC_MUTEX_BUFFER					mb;
};

#endif

#endif
