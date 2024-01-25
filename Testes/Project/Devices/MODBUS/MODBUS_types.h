/*
 * Path:    Project/Devices/MODBUS/
 * File:    MODBUS_types.h
 * Author:  João Cunha
 *
 * Created on 08/01/2024
 * Modified on 08/01/2024
 */
/*
 * Github:
 *
 */


#ifndef __PROJECT_DEVICES_MODBUS_MODBUS_TYPES_H__
#define	__PROJECT_DEVICES_MODBUS_MODBUS_TYPES_H__


/* ************************************************************************************ */
/* * Device in use                                                                    * */
/* ************************************************************************************ */
#include "../../Defines/MODBUS_defines.h"
#if (defined(__MODBUS_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* CeNTI library. */
#include "../../CeNTI_Library/lib/CeNTI_lib_includes.h"


/* ************************************************************************************ */
/* * Typedefs                                                                         * */
/* ************************************************************************************ */
typedef et_RET  (*t_uart__initialize_ptr)   (void);
typedef et_RET  (*t_uart__write_ptr)        (uint8_t *pData, size_t Size);
typedef et_RET  (*t_uart__read_ptr)         (uint8_t *pData, size_t Size);
typedef size_t  (*t_uart__getremain_ptr)    (void);
typedef void	(*t_uart__clearrxfifo_ptr)	(void);
typedef void    (*t_gpio__setlevel_ptr)     (t_LEVEL level);
typedef et_RET  (*t_delay__ms_ptr) 	       	(uint16_t ms);

typedef ut_u2B_big_endian ut_MODBUS_u2B;

/* ************************************************************************************ */
/* * Enumeration                                                                      * */
/* ************************************************************************************ */

typedef enum _enum_modbus_function_code
{
	MODBUS_FUNCTION_CODES__NONE = 0x00,
	MODBUS_FUNCTION_CODES__READ_COIL = 0x01,
	MODBUS_FUNCTION_CODES__READ_DISCRETE_INPUT = 0x02,
	MODBUS_FUNCTION_CODES__READ_MULTIPLE_HOLDING_REGISTERS = 0x03,
	MODBUS_FUNCTION_CODES__READ_INPUT = 0x04,
	MODBUS_FUNCTION_CODES__WRITE_SINGLE_COIL = 0x05,
	MODBUS_FUNCTION_CODES__WRITE_SINGLE_REGISTER = 0x06,
	MODBUS_FUNCTION_CODES__WRITE_MULTIPLE_COILS = 0x0F,
	MODBUS_FUNCTION_CODES__WRITE_MULTIPLE_HOLDING_REGISTERS = 0x10
} et_MODBUS_FUNCTION_CODES;

typedef enum _enum_DEVICE_registers {
	DEVICE_REGISTER__TEMPERATURE = 0x1520	,
	DEVICE_REGISTER__HUMIDITY = 0x1521		,
	DEVICE_REGISTER__IRRADIANCE = 0x1522
}et_DEVICE_REGISTERS;


/* ************************************************************************************ */
/* * Structures                                                                       * */
/* ************************************************************************************ */

typedef struct _struct_MODBUS_configuration {
    t_uart__initialize_ptr  uart__Initialize;
    t_uart__write_ptr       uart__Write;
    t_uart__read_ptr        uart__Read;
    t_uart__getremain_ptr   uart__GetRemain;
    t_uart__clearrxfifo_ptr uart__ClearRxFifo;
    t_gpio__setlevel_ptr    gpio__Setlevel;
    t_delay__ms_ptr         delay__ms;
} st_MODBUS_conf;

typedef struct _struct_MODBUS_command {
	uint8_t         			slave_addr;
	et_MODBUS_FUNCTION_CODES    function_code;
	ut_MODBUS_u2B   			register_addr;
	ut_MODBUS_u2B   			size;
	ut_MODBUS_u2B   			crc_16;
} st_MODBUS_COMMAND;

typedef struct _struct_MODBUS_command_write {
	uint8_t         			slave_addr;
	et_MODBUS_FUNCTION_CODES    function_code;
	ut_MODBUS_u2B   			register_addr;
	ut_MODBUS_u2B   			register_value;
	ut_MODBUS_u2B   			crc_16;
} st_MODBUS_COMMAND_WRITE;

typedef struct _struct_MODBUS_response {
	uint8_t         			slave_addr;
	et_MODBUS_FUNCTION_CODES    function_code;
	uint8_t         			size;
	ut_MODBUS_u2B   			data;
	ut_MODBUS_u2B   			crc_16;
} st_MODBUS_response;


#endif /* (defined(__MODBUS_IN_USE__)) */

#endif	/* __PROJECT_DEVICES_MODBUS_MODBUS_TYPES_H__ */

/* -- End of file -- */
