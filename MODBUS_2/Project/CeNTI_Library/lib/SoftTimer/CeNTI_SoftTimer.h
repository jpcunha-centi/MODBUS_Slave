/* 
 * Path:    Project/CeNTI_Library/lib/SoftTimer/
 * File:    CeNTI_SoftTimer.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_SOFTTIMER_CENTI_SOFTTIMER_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_SOFTTIMER_CENTI_SOFTTIMER_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_SoftTimer_defines.h"
#if (defined(__CENTI_SOFTTIMER_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_SoftTimer_types.h"
#include "../Debug/CeNTI_Debug_Returns.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Initialize all the SoftTimers.
 * 
 * @param   None.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET SoftTimer__Initialize(void);

/**
 * @brief Delay for milliseconds.
 * 
 * @param[in]   delay_msec  Delay time in milliseconds.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK      Everything worked fine.
 * @retval      Other       See et_RET.
 */
et_RET SoftTimer__Delay_msec(t_time_msec delay_msec);

/**
 * @bried Delay for seconds.
 * 
 * @param[in]   delay_sec   Delay time in seconds.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK      Everything worked fine.
 * @retval      Other       See et_RET.
 */
et_RET SoftTimer__Delay_sec(t_time_sec delay_sec);

/**
 * @brief Start a timer.
 * 
 * @param[in]   et_softtimer    SoftTimer instance.
 * @param[in]   st_timer_time   Total time.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET SoftTimer__Start(et_SOFTTIMER_INSTANCE et_softtimer,\
                        st_TIME               st_timer_time);

/**
 * @brief Stop a timer.
 * 
 * @param[in]   et_softtimer    SoftTimer instance.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET SoftTimer__Stop(et_SOFTTIMER_INSTANCE et_softtimer);

/**
 * @brief Restart a timer.
 * 
 * @param[in]   et_softtimer    SoftTimer instance.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET SoftTimer__Restart(et_SOFTTIMER_INSTANCE et_softtimer);

/**
 * @brief Get running state. Indicates if the timer is still running. This function
 *          updates the timer states.
 * 
 * @param[in]   et_softtimer    SoftTimer instance.
 * 
 * @return Returns the running state. See et_SOFTTIMER_RUNNING_STATE for more info.
 */
et_SOFTTIMER_RUNNING_STATE SoftTimer__Get_RunningState(\
        et_SOFTTIMER_INSTANCE et_softtimer);

/**
 * @brief Get elapsed state. Indicates if the timer has already elapsed. This function
 *          updates the timer states.
 * 
 * @param[in]   et_softtimer    SoftTimer instance.
 * 
 * @return Return the elapsed state. See et_SOFTTIMER_ELAPSED_STATE for more info.
 */
et_SOFTTIMER_ELAPSED_STATE SoftTimer__Get_ElapsedState(\
        et_SOFTTIMER_INSTANCE et_softtimer);


#endif /* (defined(__CENTI_SOFTTIMER_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_SOFTTIMER_CENTI_SOFTTIMER_H__ */

/* -- End of file -- */
