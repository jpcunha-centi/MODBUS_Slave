/*
 * Path:    Project/Defines/
 * File:    MODBUS_defines.h
 * Author:  João Cunha
 *
 * Created on 08/01/2024
 * Modified on 08/01/2024
 */


#ifndef __PROJECT_DEFINES_MODBUS_DEFINES_H__
#define	__PROJECT_DEFINES_MODBUS_DEFINES_H__


/* ************************************************************************************ */
/* * Enable MODBUS API                                                           * */
/* ************************************************************************************ */
/* Comment if not in use. */
#define __MODBUS_IN_USE__
//#define __MODBUS_AS_MASTER__
#define __MODBUS_AS_SLAVE__


/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */
#define MODBUS_MODE_READ (LEVEL_LOW)
#define MODBUS_MODE_WRITE (LEVEL_HIGH)

#define DEVICE_ADDR = 0xAB;



#endif	/* __PROJECT_DEFINES_MODBUS_DEFINES_H__ */

/* -- End of file -- */
