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
} st_MODBUS_CONFIGURATION;


/* ************************************************************************************ */
/* * Enumeration                                                                      * */
/* ************************************************************************************ */

typedef enum _enum_modbus_states{
	MODBUS_STATE__IDLE = 0,
	MODBUS_STATE__INIT,
	MODBUS_STATE__GET_MSG,
	MODBUS_STATE__COMPLETE,
	MODBUS_STATE__ERROR,
}et_MODBUS_STATE;

typedef enum _enum_modbus_function_code
{
	READ_COIL = 0x01,
	READ_DISCRETE_INPUT = 0x02,
	READ_MULTIPLE_HOLDING_REGS = 0x03,
	READ_INPUT = 0x04,
	WRITE_SINGLE_COIL = 0x05,
	WRITE_SINGLE_REG = 0x06,
	WRITE_MULTIPLE_COILS = 0x0F,
	WRITE_MULTIPLE_HOLDING_REG = 0x10
} et_MODBUS_Function_Code;

typedef enum _enum_modbus_register
{
	MODBUS_REG_0101 = 0x0101,
	MODBUS_REG_0202 = 0x0202,
	MODBUS_REG_0303 = 0x0303,
	MODBUS_REG_0A0A = 0x0A0A,
} et_MODBUS_Rregister;


/* ************************************************************************************ */
/* * Structures                                                                       * */
/* ************************************************************************************ */

typedef struct _struct_MODBUS_command {
	uint8_t         			slave_addr;
	et_MODBUS_Function_Code     function_code;
	ut_MODBUS_u2B   			register_addr;
	ut_MODBUS_u2B   			size;
	ut_MODBUS_u2B   			crc_16;
} st_MODBUS_COMMAND;

typedef struct _struct_MODBUS_command_write {
	uint8_t         			slave_addr;
	et_MODBUS_Function_Code     function_code;
	ut_MODBUS_u2B   			register_addr;
	ut_MODBUS_u2B   			register_value;
	ut_MODBUS_u2B   			crc_16;
} st_MODBUS_COMMAND_WRITE;

typedef struct _struct_MODBUS_response {
	uint8_t         			slave_addr;
	et_MODBUS_Function_Code     function_code;
	uint8_t         			size;
	ut_MODBUS_u2B   			data;
	ut_MODBUS_u2B   			crc_16;
} st_MODBUS_RESPONSE;



#endif /* (defined(__MODBUS_IN_USE__)) */

#endif	/* __PROJECT_DEVICES_MODBUS_MODBUS_TYPES_H__ */

/* -- End of file -- */
