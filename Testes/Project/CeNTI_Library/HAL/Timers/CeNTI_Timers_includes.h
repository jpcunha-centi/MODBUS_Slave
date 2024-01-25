/*
 * Path:    Project/HAL/Timers/
 * File:    Timers_includes.h
 * Author:  CeNTI
 * 
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_TIMERS_TIMERS_INCLUDES_H__
#define __PROJECT_CENTI_LIBRARY_HAL_TIMERS_TIMERS_INCLUDES_H__

/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Timers defines. */
#include "../Defines/CeNTI_Timers_defines.h"

/* Delay functions. */
#if (DELAY_SOURCE != DELAY_SOURCE_NONE)
    #include "CeNTI_Delay.h"
#endif


#endif /* __PROJECT_CENTI_LIBRARY_HAL_TIMERS_TIMERS_INCLUDES_H__ */

/* -- End of file -- */
