/* 
 * Path:    Project/HAL/COM/
 * File:    CeNTI_COM_includes.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_COM_CENTI_COM_INCLUDES_H__
#define	__PROJECT_CENTI_LIBRARY_HAL_COM_CENTI_COM_INCLUDES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Defines. */
#include "../Defines/CeNTI_COM_defines.h"


/* ************************************************************************************ */
/* * SPI Slave                                                                        * */
/* ************************************************************************************ */
#if (defined(__CENTI_SPI_0_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_0_Slave.h"
#endif
#if (defined(__CENTI_SPI_1_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_1_Slave.h"
#endif
#if (defined(__CENTI_SPI_2_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_2_Slave.h"
#endif
#if (defined(__CENTI_SPI_3_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_3_Slave.h"
#endif
#if (defined(__CENTI_SPI_4_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_4_Slave.h"
#endif
#if (defined(__CENTI_SPI_5_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_5_Slave.h"
#endif
#if (defined(__CENTI_SPI_6_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_6_Slave.h"
#endif
#if (defined(__CENTI_SPI_7_SLAVE__))
    #include "SPI/Slave/CeNTI_SPI_7_Slave.h"
#endif


/* ************************************************************************************ */
/* * SPI Master                                                                       * */
/* ************************************************************************************ */
#if (defined(__CENTI_SPI_0_MASTER__))
    #include "SPI/Master/CeNTI_SPI_0_Master.h"
#endif
#if (defined(__CENTI_SPI_1_MASTER__))
    #include "SPI/Master/CeNTI_SPI_1_Master.h"
#endif
#if (defined(__CENTI_SPI_2_MASTER__))
    #include "SPI/Master/CeNTI_SPI_2_Master.h"
#endif
#if (defined(__CENTI_SPI_3_MASTER__))
    #include "SPI/Master/CeNTI_SPI_3_Master.h"
#endif
#if (defined(__CENTI_SPI_4_MASTER__))
    #include "SPI/Master/CeNTI_SPI_4_Master.h"
#endif
#if (defined(__CENTI_SPI_5_MASTER__))
    #include "SPI/Master/CeNTI_SPI_5_Master.h"
#endif
#if (defined(__CENTI_SPI_6_MASTER__))
    #include "SPI/Master/CeNTI_SPI_6_Master.h"
#endif
#if (defined(__CENTI_SPI_7_MASTER__))
    #include "SPI/Master/CeNTI_SPI_7_Master.h"
#endif

/* ************************************************************************************ */
/* * I2C Slave                                                                        * */
/* ************************************************************************************ */
#if (defined(__CENTI_I2C_0_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_0_Slave.h"
#endif
#if (defined(__CENTI_I2C_1_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_1_Slave.h"
#endif
#if (defined(__CENTI_I2C_2_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_2_Slave.h"
#endif
#if (defined(__CENTI_I2C_3_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_3_Slave.h"
#endif
#if (defined(__CENTI_I2C_4_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_4_Slave.h"
#endif
#if (defined(__CENTI_I2C_5_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_5_Slave.h"
#endif
#if (defined(__CENTI_I2C_6_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_6_Slave.h"
#endif
#if (defined(__CENTI_I2C_7_SLAVE__))
    #include "I2C/Slave/CeNTI_I2C_7_Slave.h"
#endif


/* ************************************************************************************ */
/* * I2C Master                                                                       * */
/* ************************************************************************************ */
#if (defined(__CENTI_I2C_0_MASTER__))
    #include "I2C/Master/CeNTI_I2C_0_Master.h"
#endif
#if (defined(__CENTI_I2C_1_MASTER__))
    #include "I2C/Master/CeNTI_I2C_1_Master.h"
#endif
#if (defined(__CENTI_I2C_2_MASTER__))
    #include "I2C/Master/CeNTI_I2C_2_Master.h"
#endif
#if (defined(__CENTI_I2C_3_MASTER__))
    #include "I2C/Master/CeNTI_I2C_3_Master.h"
#endif
#if (defined(__CENTI_I2C_4_MASTER__))
    #include "I2C/Master/CeNTI_I2C_4_Master.h"
#endif
#if (defined(__CENTI_I2C_5_MASTER__))
    #include "I2C/Master/CeNTI_I2C_5_Master.h"
#endif
#if (defined(__CENTI_I2C_6_MASTER__))
    #include "I2C/Master/CeNTI_I2C_6_Master.h"
#endif
#if (defined(__CENTI_I2C_7_MASTER__))
    #include "I2C/Master/CeNTI_I2C_7_Master.h"
#endif


/* ************************************************************************************ */
/* * UART ASync                                                                       * */
/* ************************************************************************************ */
#if (defined(__CENTI_UART_0_ASYNC__))
    #include "UART/ASync/CeNTI_UART_0_ASync.h"
#endif
#if (defined(__CENTI_UART_1_ASYNC__))
    #include "UART/ASync/CeNTI_UART_1_ASync.h"
#endif
#if (defined(__CENTI_UART_2_ASYNC__))
    #include "UART/ASync/CeNTI_UART_2_ASync.h"
#endif
#if (defined(__CENTI_UART_3_ASYNC__))
    #include "UART/ASync/CeNTI_UART_3_ASync.h"
#endif
#if (defined(__CENTI_UART_4_ASYNC__))
    #include "UART/ASync/CeNTI_UART_4_ASync.h"
#endif
#if (defined(__CENTI_UART_5_ASYNC__))
    #include "UART/ASync/CeNTI_UART_5_ASync.h"
#endif
#if (defined(__CENTI_UART_6_ASYNC__))
    #include "UART/ASync/CeNTI_UART_6_ASync.h"
#endif
#if (defined(__CENTI_UART_7_ASYNC__))
    #include "UART/ASync/CeNTI_UART_7_ASync.h"
#endif


/* ************************************************************************************ */
/* * UART RingBuffer                                                                  * */
/* ************************************************************************************ */
#if (defined(__CENTI_UART_0_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_0_RingBuffer.h"
#endif
#if (defined(__CENTI_UART_1_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_1_RingBuffer.h"
#endif
#if (defined(__CENTI_UART_2_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_2_RingBuffer.h"
#endif
#if (defined(__CENTI_UART_3_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_3_RingBuffer.h"
#endif
#if (defined(__CENTI_UART_4_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_4_RingBuffer.h"
#endif
#if (defined(__CENTI_UART_5_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_5_RingBuffer.h"
#endif
#if (defined(__CENTI_UART_6_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_6_RingBuffer.h"
#endif
#if (defined(__CENTI_UART_7_RINGBUFFER__))
    #include "UART/RingBuffer/CeNTI_UART_7_RingBuffer.h"
#endif


#endif	/* __PROJECT_CENTI_LIBRARY_HAL_COM_CENTI_COM_INCLUDES_H__ */

/* -- End of file -- */
