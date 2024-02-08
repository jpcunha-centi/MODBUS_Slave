/* 
 * Path:    Project/CeNTI_Library/lib/Debug/
 * File:    CeNTI_Debug_STDIO.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 23, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_STDIO_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_STDIO_H__


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
#include "CeNTI_Debug_Returns.h"

#if defined(__CENTI_CODE_CONFIGURATOR_NRFX__)
    #include <zephyr/sys/printk.h>
#endif


/* ************************************************************************************ */
/* * Undefines                                                                        * */
/* ************************************************************************************ */
#undef _debug__error
#undef _debug__info
#undef _debug__return
#undef _debug__verbose
#undef _debug__warning


/* ************************************************************************************ */
/* * Debug messages                                                                   * */
/* ************************************************************************************ */
#if ((defined(__CENTI_DEBUG_IN_USE__))                  && \
     (CENTI_DEBUG_OUTPUT == CENTI_DEBUG_OUTPUT_STDIO)   )

    #define GENERATE_RET_MSG(RET, MSG) MSG,
    static const char * RET_MSG_VEC[RET_TOTAL] = { FOREACH_RET(GENERATE_RET_MSG) };

#endif

/* ************************************************************************************ */
/* * Select Functions used to output the debug                                        * */
/* ************************************************************************************ */
/* Redirect output function. */
#if defined(__CENTI_CODE_CONFIGURATOR_NRFX__)
    #define CENTI_DEBUG__Output(init_msg, fmt, ...) \
            printk("%s "fmt"\n", init_msg, ##__VA_ARGS__)
    /* Print the file and line. */
    #define CENTI_DEBUG__PrintFileLine(init_msg, fmt, ...) \
            printk("%s [%s:%d] %s: "fmt"\n", init_msg, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define CENTI_DEBUG__Output(init_msg, fmt, ...) \
            printf("%s "fmt"\n", init_msg, ##__VA_ARGS__)
    /* Print the file and line. */
    #define CENTI_DEBUG__PrintFileLine(init_msg, fmt, ...) \
            printf("%s [%s:%d] %s: "fmt"\n", init_msg, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#endif


/* ************************************************************************************ */
/* * Global Functions                                                                 * */
/* ************************************************************************************ */
/* ********** Error Debug ********** */
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_ERROR)

    #define _debug__error(...) \
            CENTI_DEBUG__PrintFileLine(CENTI_DEBUG_MSG_ERROR, __VA_ARGS__)

#else

    #define _debug__error(...)

#endif

/* ********** Return Debug ********** */
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_RETURN)

    #define _debug__return(et_ret) \
            CENTI_DEBUG__PrintFileLine(CENTI_DEBUG_MSG_RETURN, "%s", RET_MSG_VEC[et_ret]);

#else
    
    #define _debug__return(...)

#endif

/* ********** Warning Debug ********** */
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_WARNING)
    
    #define _debug__warning(...) \
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_WARNING, __VA_ARGS__)

#else
    
    #define _debug__warning(...)

#endif

/* ********** Info Debug ********** */
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_INFO)
    
    #define _debug__info(...) \
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_INFO, __VA_ARGS__)

#else

    #define _debug__info(...)

#endif

/* ********** Verbose Debug **********/
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_VERBOSE)
    
    #define _debug__verbose(...) \
            CENTI_DEBUG__Output(CENTI_DEBUG_MSG_VERBOSE, __VA_ARGS__)

#else
    
    #define _debug__verbose(...)

#endif


#endif /* (defined(__CENTI_DEBUG_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_STDIO_H__ */

/* -- End of file -- */
