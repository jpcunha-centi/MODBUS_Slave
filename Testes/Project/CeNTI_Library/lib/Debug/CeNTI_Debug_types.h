/* 
 * Path:    Project/CeNTI_Library/lib/Debug/
 * File:    CeNTI_Debug_types.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_TYPES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_TYPES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Debug_defines.h"
#if (defined(__CENTI_DEBUG_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include <stdio.h>
#include <stdint.h>

/* Debug messages. */
#include "CeNTI_Debug_messages.h"

/* Include returns type. */
#include "../Utils/CeNTI_Returns.h"

#if defined(__CENTI_CODE_CONFIGURATOR_NRFX__)
    #include <zephyr/sys/printk.h>
#endif


/* ************************************************************************************ */
/* * Output interface                                                                 * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    #ifdef __GNUC__
        #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
    #else
        #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
    #endif
#endif


/* ************************************************************************************ */
/* * Select Functions used to output the debug                                        * */
/* ************************************************************************************ */
/* Redirect output function. */
#if (CENTI_DEBUG_OUTPUT == CENTI_DEBUG_OUTPUT_STDIO)
    #if defined(__CENTI_CODE_CONFIGURATOR_NRFX__)
        #define CENTI_DEBUG__Output(...)     printk(__VA_ARGS__)
        /* Print the file and line. */
        #define CENTI_DEBUG__PrintFileLine(...)  printk("\"%s\" l. %d - ", __FILE__, __LINE__)
    #else
        #define CENTI_DEBUG__Output(...)     printf(__VA_ARGS__)
        /* Print the file and line. */
        #define CENTI_DEBUG__PrintFileLine(...)  printf("\"%s\" l. %d - ", __FILE__, __LINE__)
    #endif
#else
    #define CENTI_DEBUG__Output(...)
    /* Print the file and line. */
    #define CENTI_DEBUG__PrintFileLine(...) 
#endif


/* ************************************************************************************ */
/* * Global Functions                                                                 * */
/* ************************************************************************************ */
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_ERROR)

    #define _debug__error(...) \
            CENTI_DEBUG__PrintFileLine(); \
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_ERROR); \
            CENTI_DEBUG__Output(__VA_ARGS__);\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_NEW_LINE);

#else

    #define _debug__error(...)

#endif


#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_RETURN)

    void CeNTI_Debug__Return(et_RET et_ret);
    
    #define _debug__return(et_ret)\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_RETURN);\
            CeNTI_Debug__Return(et_ret);\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_NEW_LINE);

#else
    
    #define _debug__return(...)

#endif

    
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_WARNING)
    
    #define _debug__warning(...)\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_WARNING);\
            CENTI_DEBUG__Output(__VA_ARGS__);\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_NEW_LINE);

#else
    
    #define _debug__warning(...)

#endif

    
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_INFO)
    
    #define _debug__info(...)\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_INFO);\
            CENTI_DEBUG__Output(__VA_ARGS__);\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_NEW_LINE);

#else

    #define _debug__info(...)

#endif

    
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_VERBOSE)
    
    #define _debug__verbose(...)\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_VERBOSE);\
            CENTI_DEBUG__Output(__VA_ARGS__);\
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_NEW_LINE);

#else
    
    #define _debug__verbose(...)

#endif


#endif /* (defined(__CENTI_DEBUG_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_TYPES_H__ */

/* -- End of file -- */
