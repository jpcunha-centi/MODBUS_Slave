/* 
 * Path:    Project/CeNTI_Library/lib/Defines/
 * File:    CeNTI_Time_defines.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_TIME_DEFINES_H__
#define __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_TIME_DEFINES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Lib_defines.h"


/* ************************************************************************************ */
/* * Time Defines                                                                     * */
/* ************************************************************************************ */
#if ((defined(CENTI_ENABLE_TIME))           &&\
     (CENTI_ENABLE_TIME == CENTI_ENABLE)    )

    /* ******************************************************************************** */
    /* * Enables                                                                      * */
    /* ******************************************************************************** */
    #define __CENTI_TIME_IN_USE__


    /* ******************************************************************************** */
    /* * Enables                                                                      * */
    /* ******************************************************************************** */
    /* Microseconds resolution. */
    #define CENTI_TIME_USEC     CENTI_DISABLE

    /* Minutes resolution. */
    #define CENTI_TIME_MINUTE   CENTI_DISABLE

    /* Hours resolution. */
    #define CENTI_TIME_HR       CENTI_DISABLE


#else

    #undef __CENTI_TIME_IN_USE__
    #undef CENTI_TIME_USEC
    #undef CENTI_TIME_MINUTE
    #undef CENTI_TIME_HR

#endif


#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_TIME_DEFINES_H__ */

/* -- End of file -- */
