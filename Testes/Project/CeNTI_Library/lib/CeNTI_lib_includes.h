/* 
 * Path:    Project/CeNTI_Library/lib/
 * File:    CeNTI_lib_includes.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_CENTI_LIB_INCLUDES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_CENTI_LIB_INCLUDES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Include library to deal with standard inputs and outputs. */
#include <stdio.h>

/* Include library with standard libraries. */
#include <stdlib.h>

/* CeNTI library defines. */
#include "Defines/CeNTI_Defines_includes.h"

/* Utilities. */
#include "Utils/CeNTI_Utils_includes.h"

/* Debug library. */
#if (defined(__CENTI_DEBUG_IN_USE__))
    #include "Debug/CeNTI_Debug.h"
#endif

/* Time library. */
#if (defined(__CENTI_TIME_IN_USE__))
    #include "Time/CeNTI_Time.h"
#endif

/* SoftTimer library. */
#if (defined(__CENTI_SOFTTIMER_IN_USE__))
    #include "SoftTimer/CeNTI_SoftTimer.h"
#endif

/* CRC library. */
#if (defined(__CENTI_CRC_IN_USE__))
    #include "CRC/CeNTI_CRC.h"
#endif

/* FIFO library. */
#if (defined(__CENTI_FIFO_IN_USE__))
	#include "FIFO/CeNTI_FIFO.h"
#endif

/* ArrayList library. */
#if (defined(__CENTI_ARRAYLIST_IN_USE__))
    #include "ArrayList/CeNTI_ArrayList.h"
#endif

#endif /* __PROJECT_CENTI_LIBRARY_LIB_CENTI_LIB_INCLUDES_H__ */

/* -- End of file -- */
