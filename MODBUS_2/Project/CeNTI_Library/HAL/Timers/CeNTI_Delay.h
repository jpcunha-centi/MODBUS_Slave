/* 
 * Path:   Project/HAL/Timers/
 * File:   CeNTI_Delay.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_TIMERS_DELAY_H__
#define	__PROJECT_CENTI_LIBRARY_HAL_TIMERS_DELAY_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Timers_defines.h"
#if (DELAY_SOURCE != DELAY_SOURCE_NONE)


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "../../lib/CeNTI_lib_includes.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Delay (milliseconds).
 * 
 * @param[in]   msec    Delay time in milliseconds.
 * 
 * @return      None.
 */
void Delay__ms(uint16_t ms);


#endif /* (DELAY_SOURCE != DELAY_SOURCE_NONE) */

#endif	/* __PROJECT_CENTI_LIBRARY_HAL_TIMERS_CENTI_DELAY_H__ */

/* -- End of file -- */
