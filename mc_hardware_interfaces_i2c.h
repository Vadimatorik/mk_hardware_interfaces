/*!
 * 	@startuml
 *
 *	interface I2cMasterBase {
 *		{abstract}{method}+	BaseResult		reinit		( uint32_t		numberCfg = 0 )
 *		{abstract}{method}+	BaseResult		on		( void )
 *		{abstract}{method}+	void			off		( void )
 *		{abstract}{method}+	BaseResult		read		( uint8_t		slaveDeviceAddress,\n\t\t\t\t\t  uint8_t*		rx,\n\t\t\t\t\t  uint8_t		readAddress,\n\t\t\t\t\t  uint16_t		countByte )
 *		{abstract}{method}+	BaseResult		readDma	( uint8_t		slaveDeviceAddress,\n\t\t\t\t\t  uint8_t*		rx,\n\t\t\t\t\t  uint8_t		readAddress,\n\t\t\t\t\t  uint16_t		countByte )
 *		{abstract}{method}+	BaseResult		writeByte	( uint8_t		slaveDeviceAddress,\n\t\t\t\t\t  uint8_t*		rx,\n\t\t\t\t\t  uint8_t		writeAddress )
 *	}
 *
 *	@enduml
 */

#pragma once

#ifdef __cplusplus

#include "mc_hardware_interfaces_base.h"

/*!
 * Класс переназначен для работы с I2C
 * в режиме ведущего устройства на шине.
 */
class I2cMasterBase {
public:
	/*!
	 * Сбрасывает текущие настройки I2C и инициализирует его заново.
	 * После инициализации I2C остается отключенным.
	 *
	 * Замечание: управление тактовым сигналом аппаратного
	 * модуля осуществляется внутри метода автоматически.
	 *
	 * \param[in]	numberCfg		-	выбранный режим работы.
	 *
	 * \return		{	BASE_RESULT::OK			-	инициализация прошла успешно.
	 *					BASE_RESULT::INPUT_VALUE_ERROR	-	несуществующий номер конфигурации.
	 *					BASE_RESULT::ERROR_INIT	-	в противном случае.	}
	 */
	virtual	BaseResult		reinit		( uint32_t		numberCfg = 0 )						= 0;

	/*!
	 * Запускает I2C.
	 *
	 * \return		{	BASE_RESULT::OK					-	передача прошла успешно.
	 *					BASE_RESULT::ERROR_INIT			-	SPI не был инициализирован ранее.	}
	 */
	virtual	BaseResult		on			( void )											= 0;

	/// Останавливает I2C.
	virtual	void			off			( void )											= 0;


	virtual	BaseResult		read		( uint8_t		slaveDeviceAddress,
										  uint8_t*		rx,
										  uint8_t		readAddress,
										  uint16_t		countByte )							= 0;

	virtual	BaseResult		readDma		( uint8_t		slaveDeviceAddress,
										  uint8_t*		rx,
										  uint8_t		readAddress,
										  uint16_t		countByte )							= 0;

	virtual	BaseResult		writeByte	( uint8_t		slaveDeviceAddress,
										  uint8_t*		rx,
										  uint8_t		writeAddress )						= 0;
};

#endif
