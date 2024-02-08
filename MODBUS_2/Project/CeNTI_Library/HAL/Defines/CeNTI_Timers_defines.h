/*
 * Path:    Project/HAL/Defines/
 * File:    CeNTI_Timers_defines.h
 * Author:  CeNTI
 * 
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_DEFINES_CENTI_TIMERS_DEFINES_H__
#define __PROJECT_CENTI_LIBRARY_HAL_DEFINES_CENTI_TIMERS_DEFINES_H__


/* ************************************************************************************ */
/* * Delay                                                                            * */
/* ************************************************************************************ */
/* Disable delay functions. */
#define DELAY_SOURCE_NONE               (0)
/* Use SoftTimer as source for the delay function. */
#define DELAY_SOURCE_SOFTTIMER          (1)
/* Use generated functions for the delay. */
#define DELAY_SOURCE_DEFAULT_FUNCTION   (2)

#define DELAY_SOURCE    DELAY_SOURCE_NONE


#endif /* __PROJECT_CENTI_LIBRARY_HAL_DEFINES_CENTI_TIMERS_DEFINES_H__ */

/* -- End of file -- */
