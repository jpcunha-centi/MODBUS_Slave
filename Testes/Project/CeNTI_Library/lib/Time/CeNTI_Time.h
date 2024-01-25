/* 
 * Path:    Project/CeNTI_Library/lib/Time/
 * File:    CeNTI_Time.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_TIME_CENTI_TIME_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_TIME_CENTI_TIME_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Time_defines.h"
#if (defined(__CENTI_TIME_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Time_types.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Add 1 microsecond to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where the microsecond will be added.
 * 
 * @return      None.
 */
#if (CENTI_TIME_USEC == CENTI_ENABLE)
    void Time__Add_usec(st_TIME *const st_time_ptr);
#endif

/**
 * @brief Add 1 millisecond to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where the millisecond will be added.
 * 
 * @return      None.
 */
void Time__Add_msec(st_TIME *const st_time_ptr);

/**
 * @brief Add 1 second to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where the second will be added.
 * 
 * @return      None.
 */
void Time__Add_sec(st_TIME *const st_time_ptr);

/**
 * @brief Add 1 minute to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where the minute will be added.
 * 
 * @return      None.
 */
#if (CENTI_TIME_MINUTE == CENTI_ENABLE)
    void Time__Add_minute(st_TIME *const st_time_ptr);
#endif

/**
 * @brief Add 1 hour to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where the hour will be added.
 * 
 * @return      None.
 */
#if (CENTI_TIME_HR == CENTI_ENABLE)
    void Time__Add_hr(st_TIME *const st_time_ptr);
#endif

/**
 * @brief Add N microseconds to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where will be added.
 * @param[in]   n_usec          Amount of microseconds to add.
 * 
 * @return      None.
 */
#if (CENTI_TIME_USEC == CENTI_ENABLE)
    void Time__AddN_usec(st_TIME *const st_time_ptr,\
                         t_time_usec    n_usec);
#endif

/**
 * @brief Add N milliseconds to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where will be added.
 * @param[in]   n_msec          Amount of milliseconds to add.
 * 
 * @return      None.
 */
void Time__AddN_msec(st_TIME *const st_time_ptr,\
                     t_time_msec    n_msec);

/**
 * @brief Add N seconds to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where will be added.
 * @param[in]   n_sec           Amount of seconds to add.
 * 
 * @return      None.
 */
void Time__AddN_sec(st_TIME *const st_time_ptr,\
                    t_time_sec     n_sec);

/**
 * @brief Add N minute to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where will be added.
 * @param[in]   n_minute        Amount of minute to add.
 * 
 * @return      None.
 */
#if (CENTI_TIME_MINUTE == CENTI_ENABLE)
    void Time__AddN_minute(st_TIME *const st_time_ptr,\
                           t_time_minute  n_minute);
#endif

/**
 * @brief Add N hour to the given time.
 * 
 * @param[out]  st_time_ptr     Structure time where will be added.
 * @param[in]   n_hr            Amount of hours to add.
 * 
 * @return      None.
 */
#if (CENTI_TIME_HR == CENTI_ENABLE)
    void Time__AddN_hr(st_TIME *const st_time_ptr,\
                       t_time_hr      n_hr);
#endif

/**
 * @brief Compare time 1 with time 2.
 * 
 * @param[in]   st_time_1               Time 1.
 * @param[in]   st_time_2               Time 2.
 * 
 * @return Comparison between the two times.
 * @retval      TIME_COMPARE_EQUAL      Both times are equal.
 * @retval      TIME_COMPARE_BIGGER     Time 1 is bigger than time 2.
 * @retval      TIME_COMPARE_SMALLER    Time 1 is smaller than time 2.
 */
et_TIME_COMPARE Time__Compare(st_TIME st_time_1,\
                              st_TIME st_time_2);

/**
 * @brief Get difference time between two times.
 * 
 * @param[in]   st_time_1   Time 1.
 * @param[in]   st_time_2   Time 2.
 * 
 * @return Returns a Time structure with the remaining time between both times.
 */
st_TIME Time__Get_Remaining(st_TIME st_time_1,\
                            st_TIME st_time_2);

/**
 * @brief Add two times together.
 * 
 * @param[in]   st_time_1   Time 1.
 * @param[in]   st_time_2   Time 2.
 * 
 * @return Returns a Time structure with the time of both times added.
 */
st_TIME Time__Add_Times(st_TIME st_time_1,\
                        st_TIME st_time_2);


#endif /* (defined(__CENTI_TIME_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_TIME_CENTI_TIME_H__ */

/* -- End of file -- */
