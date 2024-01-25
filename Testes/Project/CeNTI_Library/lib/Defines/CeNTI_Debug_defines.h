/* 
 * Path:    Project/CeNTI_Library/lib/Defines/
 * File:    CeNTI_Debug_defines.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_DEBUG_DEFINES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_DEBUG_DEFINES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Lib_defines.h"


/* ************************************************************************************ */
/* * Debug defines                                                                    * */
/* ************************************************************************************ */
#if ((defined(CENTI_ENABLE_DEBUG))          &&\
     (CENTI_ENABLE_DEBUG == CENTI_ENABLE)   )


    /* ******************************************************************************** */
    /* * Defines                                                                      * */
    /* ******************************************************************************** */
    #define __CENTI_DEBUG_IN_USE__


    /* ******************************************************************************** */
    /* * Debug Output                                                                 * */
    /* ******************************************************************************** */
    /* ********** Declaration of all the debug output types ********** */
    #define CENTI_DEBUG_OUTPUT_NONE               (-1)
    #define CENTI_DEBUG_OUTPUT_STDIO              (1)

    /* ********** Selection of debug output ********** */
    /* # ------ # Change Here # ------ # */
    #define CENTI_DEBUG_OUTPUT    CENTI_DEBUG_OUTPUT_STDIO

    /* ********** Safety debug declaration ********** */
    #if ((!defined(CENTI_DEBUG_OUTPUT))                     ||\
         (CENTI_DEBUG_OUTPUT == CENTI_DEBUG_OUTPUT_NONE)    )
        #error Define CENTI_DEBUG_OUTPUT in the Project/CeNTI/Defines/CeNTI_Debug_defines.h file!
    #endif

    
    /* ******************************************************************************** */
    /* * Messages types enabled                                                       * */
    /* ******************************************************************************** */
    /* ********** Declaration of all the messages types ************ */
    /* Singles. */
    #define CENTI_DEBUG_MSG_TYPE_NONE       (0b00000000)
    #define CENTI_DEBUG_MSG_TYPE_ERROR      (0b00000001)
    #define CENTI_DEBUG_MSG_TYPE_RETURN     (0b00000010)
    #define CENTI_DEBUG_MSG_TYPE_WARNING    (0b00000100)
    #define CENTI_DEBUG_MSG_TYPE_INFO       (0b00001000)
    #define CENTI_DEBUG_MSG_TYPE_VERBOSE    (0b00010000)
    /* Modes. */
    #define CENTI_DEBUG_MSG_TYPE_ESSENTIAL  (CENTI_DEBUG_MSG_TYPE_ERROR     |\
                                             CENTI_DEBUG_MSG_TYPE_RETURN    |\
                                             CENTI_DEBUG_MSG_TYPE_WARNING   )
    #define CENTI_DEBUG_MSG_TYPE_STANDARD   (CENTI_DEBUG_MSG_TYPE_ESSENTIAL |\
                                             CENTI_DEBUG_MSG_TYPE_INFO      )
    #define CENTI_DEBUG_MSG_TYPE_IN_DEPTH   (CENTI_DEBUG_MSG_TYPE_STANDARD  |\
                                             CENTI_DEBUG_MSG_TYPE_VERBOSE   )

    /* ******** Selection of the messages types ********** */
    /* # ------ # Change Here # ------ # */
    #define CENTI_DEBUG_MSG_TYPE    CENTI_DEBUG_MSG_TYPE_IN_DEPTH

    /* ********** Safety debug declaration ********** */
    #if (!defined(CENTI_DEBUG_MSG_TYPE))
        #error Define CENTI_DEBUG_MSG_TYPE in the Project/CeNTI/Defines/CeNTI_Debug_defines.h file!
    #endif


    /* ******************************************************************************** */
    /* * Paths                                                                        * */
    /* ******************************************************************************** */
    #if (CENTI_DEBUG_OUTPUT == CENTI_DEBUG_OUTPUT_STDIO)

        #define CENTI_DEBUG_OUTPUT_PATH "stdio.h"

    #else

        #error Define CENTI_DEBUG_OUTPUT_PATH in the Project/CeNTI/Defines/CeNTI_Debug_defines.h file!

    #endif

#else

    #undef __CENTI_DEBUG_IN_USE__
    #undef CENTI_DEBUG_OUTPUT
    #undef CENTI_DEBUG_MSG_TYPE
    #undef CENTI_DEBUG_OUTPUT_PATH

#endif


#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_DEBUG_DEFINES_H__ */

/* -- End of file -- */
