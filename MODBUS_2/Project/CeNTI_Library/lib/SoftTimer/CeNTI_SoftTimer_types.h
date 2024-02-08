/* 
 * Path:    Project/CeNTI_Library/lib/SoftTimer/
 * File:    CeNTI_SoftTimer_types.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_SOFTTIMER_CeNTI_SOFTTIMER_TYPES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_SOFTTIMER_CeNTI_SOFTTIMER_TYPES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_SoftTimer_defines.h"
#if (defined(__CENTI_SOFTTIMER_IN_USE__))


/* ************************************************************************************ */
/* * Check dependencies                                                               * */
/* ************************************************************************************ */
#if (!(defined(__CENTI_TIME_IN_USE__)))
    #error Enable CENTI_ENABLE_TIME in Project/lib/Defines/CeNTI_lib_defines.h file!
#endif


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Includes time library. */
#include "../Time/CeNTI_Time.h"


/* ************************************************************************************ */
/* * Instances                                                                        * */
/* ************************************************************************************ */
/* -- Add SoftTimer instance here -- */
#define FOREACH_SOFTTIMER_INSTANCE(INST)\
        /*  | Instance enumeration name             | */ \
        INST( SOFTTIMER_INSTANCE_DELAY              )\
        INST (SOFTTIMER_INSTANCE_MODBUS_TIMEOUT)\

#define GENERATE_SOFTTIMER_INSTANCE_ENUM(ENUM) ENUM,


/* ************************************************************************************ */
/* * Enumerations                                                                     * */
/* ************************************************************************************ */
/* Instances. */
typedef enum _enum_softtimer_instance {
    FOREACH_SOFTTIMER_INSTANCE(GENERATE_SOFTTIMER_INSTANCE_ENUM)
    SOFTTIMER_INSTANCE_TOTAL,
}et_SOFTTIMER_INSTANCE;

/* Running state - Tells if the timer is running. */
typedef enum _enum_softtimer_running_state {
    /* Timer not running. */
    SOFTTIMER_RUNNING_STATE_STOPPED = 0,
    /* Timer running. */
    SOFTTIMER_RUNNING_STATE_RUNNING,
}et_SOFTTIMER_RUNNING_STATE;

/* Elapsed state - Tells if the timer time has passed. */
typedef enum _enum_softtimer_elapsed_state {
    /* Timer did not elapsed. */
    SOFTTIMER_ELAPSED_STATE_NOT_ELAPSED = 0,
    /* Timer did elapsed. */
    SOFTTIMER_ELAPSED_STATE_ELAPSED,
}et_SOFTTIMER_ELAPSED_STATE;


/* ************************************************************************************ */
/* * Structures                                                                       * */
/* ************************************************************************************ */
/* SoftTimer information. */
typedef struct _struct_softtimer_info {
    /* Current time during start/restart timer. */
    st_TIME                    st_start_time;
    /* Time period. */
    st_TIME                    st_delay_time;
    /* Stop time. */
    st_TIME                    st_stop_time;
    /* Running state. */
    et_SOFTTIMER_RUNNING_STATE et_running_state;
    /* Elapsed state. */
    et_SOFTTIMER_ELAPSED_STATE et_elapsed_state;
} st_SOFTTIMER_Info;


#endif /* (defined(__CENTI_SOFTTIMER_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_SOFTTIMER_CENTI_SOFTTIMER_TYPES_H__ */

/* -- End of file -- */
