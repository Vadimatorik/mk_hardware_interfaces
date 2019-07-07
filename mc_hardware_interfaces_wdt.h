#pragma once

#ifdef __cplusplus

#include "mc_hardware_interfaces_base.h"

/*

@startuml

namespace McHardwareInterfaces {

interface Wdt {
	{abstract}{method}+	BaseResult		reinit			( uint32_t cfgNumber = 0 )
	{abstract}{method}+	void			reset			( void )
	{abstract}{method}+	void			resetService	( void )
}

}

@enduml

*/

namespace mc_interfaces {

class Wdt {
public:
    /*!
     * Сбрасывает текущие настройки WDT и инициализирует его заново.
     * После инициализации WDT автоматически запускается.
     *
     * \param[in]	cfgNumber		-	выбранный режим работы.
     *
     * \return		{	BASE_RESULT::OK					-	инициализация прошла успешно.
     *					BASE_RESULT::INPUT_VALUE_ERROR	-	несуществующий номер конфигурации.
     *					BASE_RESULT::ERROR_INIT			-	ошибка инициализации.
     */
    virtual res reinit (uint32_t cfgNumber = 0) = 0;
    
    /*!
     * Метод сбрасывает WDT на рабочее значение.
     */
    virtual void reset (void) = 0;
    
    /*!
     * Метод сбрасывает WDT на сервисное значение.
     */
    virtual void resetService (void) = 0;
    
};

}

#endif
