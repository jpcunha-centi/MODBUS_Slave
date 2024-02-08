/*
 * Path:    Project/Configs/
 * File:    MODBUS_configs.h
 * Author:  João Cunha
 *
 * Created on 08/01/2024
 * Modified on 08/01/2024
 */
/*
  * Pinout Table
 * ||===================================||==============================||=============||
 * || Type                              || Pins                         || MC Pins	   ||
 * ||===================================||==============================||=============||
 * || UART1	RX		    	            || RX                           || PA10        ||
 * || UART1	TX			                || TX                           || PA9         ||
 * || DE ENABLE			                || DE 		                    || PC9         ||
 * ||===================================||==============================||=============||
 */


#ifndef __PROJECT_CONFIGS_MODBUS_CONFIGS_H__
#define	__PROJECT_CONFIGS_MODBUS_CONFIGS_H__


/* ************************************************************************************ */
/* * Device in use                                                                    * */
/* ************************************************************************************ */
#include "../Defines/MODBUS_defines.h"
#if (defined(__MODBUS_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* MODBUS types. */
#include "../Devices/MODBUS/MODBUS_types.h"

/* CeNTI Hardware Abstraction Layer library. */
#include "../CeNTI_Library/HAL/CeNTI_HAL_includes.h"


/* ************************************************************************************ */
/* * Configuration                                                                    * */
/* ************************************************************************************ */
#define MODBUS_DEFAULT_CONF \
{ \
    .uart__Initialize   = UART_1_RingBuffer__Initialize         , \
	.uart__Write        = UART_1_RingBuffer__Write              , \
	.uart__Read         = UART_1_RingBuffer__Read               , \
	.uart__GetRemain    = UART_1_RingBuffer__GetRxRemainSize    , \
	.uart__ClearRxFifo	= UART_1_RingBuffer__ClearRxFIFO		, \
	.gpio__Setlevel     = GPIO__MODBUS_DE_SetLevel              , \
	.delay__ms          = SoftTimer__Delay_msec                   \
}


/* ************************************************************************************ */
/* * Devices                                                                          * */
/* ************************************************************************************ */
#define FOREACH_MODBUS(DEVICE)\
        /*    | Name                            | Configuration                     | */ \
        DEVICE( MODBUS_DEFAULT                  , MODBUS_DEFAULT_CONF               )

#define GENERATE_MODBUS_ENUM(ENUM, CONF) ENUM,
#define GENERATE_MODBUS_CONF(ENUM, CONF) CONF,

typedef enum _enum_MODBUS {
    FOREACH_MODBUS(GENERATE_MODBUS_ENUM)
    MODBUS_TOTAL
} et_MODBUS;


#endif /* (defined(__MODBUS_IN_USE__)) */

#endif	/* __PROJECT_CONFIGS_MODBUS_CONFIGS_H__ */

/* -- End of file -- */
