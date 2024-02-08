/* 
 * Path:    Project/CeNTI_Library/lib/Debug/
 * File:    CeNTI_Debug_messages.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 25, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_MESSAGES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_MESSAGES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Debug_defines.h"
#if (defined(__CENTI_DEBUG_IN_USE__))


/* ************************************************************************************ */
/* * Default Messages                                                                 * */
/* ************************************************************************************ */
#define CENTI_DEBUG_MSG_RETURN          "[ret] "
#define CENTI_DEBUG_MSG_WARNING         "[wrn] "
#define CENTI_DEBUG_MSG_ERROR           "[err] "
#define CENTI_DEBUG_MSG_INFO            "[inf] "
#define CENTI_DEBUG_MSG_VERBOSE         "[vrb] "
#define CENTI_DEBUG_MSG_NEW_LINE        "\n"
#define CENTI_DEBUG_MSG_TAB             "\t"
#define CENTI_DEBUG_MSG_NOT_AVAILABLE   "\"Not Available\" "


#endif /* defined(__CENTI_DEBUG_IN_USE__) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_MESSAGES_H__ */

/* -- End of file -- */
