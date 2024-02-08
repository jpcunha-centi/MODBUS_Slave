/* 
 * Path:    Project/Defines/
 * File:    Project_defines.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_DEFINES_PROJECT_DEFINES_H__
#define	__PROJECT_DEFINES_PROJECT_DEFINES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* CeNTI library. */
#include "../CeNTI_Library/lib/CeNTI_lib_includes.h"


/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */
/* Number of initialization retries. */
#define NUM_RETRIES 3

/* Hardware version. */
#define VERSION_HW  0

/* Firmware version. */
#define VERSION_FW  0


/* ************************************************************************************ */
/* * Timers                                                                           * */
/* ************************************************************************************ */
#if (defined(__CENTI_TIME_IN_USE__))

    /* Delay before initialize. */
    static const t_time_msec DELAY_INIT_MS = 100;

    /* Delay between initialization tries. */
    static const t_time_msec DELAY_RETRY_MS = 100;

#endif


#endif /* __PROJECT_DEFINES_PROJECT_DEFINES_H__ */

/* -- End of file -- */