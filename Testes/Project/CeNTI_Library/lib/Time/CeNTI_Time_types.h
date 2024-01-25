/* 
 * Path:    Project/CeNTI_Library/lib/Time/
 * File:    CeNTI_Time_types.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_TIME_CENTI_TIME_TYPES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_TIME_CENTI_TIME_TYPES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Time_defines.h"
#if (defined(__CENTI_TIME_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Include data types. */
#include "../Utils/CeNTI_Data_types.h"


/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */
/* Amount of microseconds to 1 millisecond. */
#define TIME_USEC_TO_MSEC   (1000)

/* Amount of milliseconds to 1 second. */
#define TIME_MSEC_TO_SEC    (1000)

/* Amount of microseconds to 1 second. */
#define TIME_USEC_TO_SEC    (TIME_USEC_TO_MSEC * TIME_MSEC_TO_SEC)

/* Amount of seconds to 1 minute. */
#define TIME_SEC_TO_MINUTE  (60)

/* Amount of milliseconds to 1 minute. */
#define TIME_MSEC_TO_MINUTE (TIME_MSEC_TO_SEC * TIME_SEC_TO_MINUTE)

/* Amount of microseconds to 1 minute. */
#define TIME_USEC_TO_MINUTE (TIME_USEC_TO_SEC * TIME_SEC_TO_MINUTE)

/* Amount of minutes to 1 hour. */
#define TIME_MINUTE_TO_HOUR (60)

/* Amount of seconds to 1 hour. */
#define TIME_SEC_TO_HOUR    (TIME_SEC_TO_MINUTE * TIME_MINUTE_TO_HOUR)

/* Amount of milliseconds to 1 hour. */
#define TIME_MSEC_TO_HOUR   (TIME_MSEC_TO_MINUTE * TIME_MINUTE_TO_HOUR)

/* Amount of microseconds to 1 hour. */
#define TIME_USEC_TO_HOUR   (TIME_USEC_TO_MINUTE * TIME_MINUTE_TO_HOUR)


/* ************************************************************************************ */
/* * Data Types                                                                       * */
/* ************************************************************************************ */
/* Microsecond part of the time. */
#if (CENTI_TIME_USEC == CENTI_ENABLE)
    typedef uint16_t t_time_usec;
#endif
    
/* Milisecond part of the time. */
typedef uint16_t t_time_msec;

    /* Second part of the time. */
#if ((CENTI_TIME_MINUTE == CENTI_DISABLE) &&\
     (CENTI_TIME_HR == CENTI_DISABLE))
    typedef uint32_t t_time_sec;
#else
    typedef uint16_t t_time_sec;
#endif

/* Minute part of the time. */
#if (CENTI_TIME_MINUTE == CENTI_ENABLE)
    #if(CENTI_TIME_HR == CENTI_DISABLE)
        typedef uint32_t t_time_minute;
    #else
        typedef uint16_t t_time_minute;
    #endif
#endif

/* Hour part of the time. */
#if (CENTI_TIME_HR == CENTI_ENABLE)
    typedef uint32_t t_time_hr;
#endif

    
/* ************************************************************************************ */
/* * Enumerations                                                                     * */
/* ************************************************************************************ */
/* Enumeration with comparison types. */
typedef enum _enum_time_compare {
    TIME_COMPARE_EQUAL = 0,
    TIME_COMPARE_BIGGER,
    TIME_COMPARE_SMALLER
}et_TIME_COMPARE;


/* ************************************************************************************ */
/* * Structures                                                                       * */
/* ************************************************************************************ */
typedef struct _struct_time {
    /* Microseconds. */
    #if (CENTI_TIME_USEC == CENTI_ENABLE)
        t_time_usec usec;
    #endif
    /* Miliseconds. */
    t_time_msec msec;
    /* Seconds. */
    t_time_sec  sec;
    #if (CENTI_TIME_MINUTE == CENTI_ENABLE)
        t_time_minute minute;
    #endif
    /* Hours. */
    #if (CENTI_TIME_HR == CENTI_ENABLE)
        t_time_hr hr;
    #endif
} st_TIME;


#endif /* (defined(__CENTI_TIME_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_TIME_CENTI_TIME_TYPES_H__ */

/* -- End of file -- */
