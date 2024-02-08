/* 
 * Path:    Project/CeNTI_Library/lib/Defines/
 * File:    CeNTI_lib_defines.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_LIB_DEFINES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_LIB_DEFINES_H__


/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */
#define CENTI_ENABLE  (1)
#define CENTI_DISABLE (-1)


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Tools_defines.h"


/* ************************************************************************************ */
/* * Enables                                                                          * */
/* ************************************************************************************ */
/* Interrupts enable the system interrupt handler. */
#define CENTI_ENABLE_INTERRUPTS         CENTI_ENABLE

/* SoftTimer is a library that allows the use of a software timer. */
#define CENTI_ENABLE_SOFTTIMER          CENTI_ENABLE

/* Time is a library that allows to creation and manipulation of variables based on time
 * structures. */
#define CENTI_ENABLE_TIME               CENTI_ENABLE

/* CRC is a library that allows to calculation of the CRC for 8 and 16 bits. */
#define CENTI_ENABLE_CRC                CENTI_DISABLE

/* Debug is a library that gives some functionalities to debug. */
#define CENTI_ENABLE_DEBUG              CENTI_ENABLE

/* FIFO is a library that allows the use of a FIFO. */
#define CENTI_ENABLE_FIFO               CENTI_DISABLE

/* ArrayList is a library that implements a generic ArrayList data structure. */
#define CENTI_ENABLE_ARRAYLIST          CENTI_ENABLE


#endif /* __PROJECT_CENTI_LIBRARY_DEFINES_CENTI_LIB_DEFINES_H__ */

/* -- End of file -- */
