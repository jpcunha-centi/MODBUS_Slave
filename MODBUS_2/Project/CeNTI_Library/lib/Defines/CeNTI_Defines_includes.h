/* 
 * Path:    Project/CeNTI_Library/lib/Defines/
 * File:    CeNTI_Defines_includes.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_DEFINES_INCLUDES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_DEFINES_INCLUDES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Allows to enable/disable some CeNTI libraries. */
#include "CeNTI_Lib_defines.h"

/* Gives information about the microcontroller, code configurator, and compiler. */
#include "CeNTI_Tools_defines.h"

/* Sets the debug output. */
#if (CENTI_ENABLE_DEBUG == CENTI_ENABLE)
    #include "CeNTI_Debug_defines.h"
#endif

/* Sets SoftTimer timer source, and the periodicity. */
#if (CENTI_ENABLE_SOFTTIMER == CENTI_ENABLE)
    #include "CeNTI_SoftTimer_defines.h"
#endif

/* Defines if microseconds and hours are enabled. */
#if (CENTI_ENABLE_TIME == CENTI_ENABLE)
    #include "CeNTI_Time_defines.h"
#endif

/* Defines CRC library behavior. */
#if (CENTI_ENABLE_CRC == CENTI_ENABLE)
    #include "CeNTI_CRC_defines.h"
#endif

/* Defines ArrayList library behavior. */
#if (CENTI_ENABLE_ARRAYLIST == CENTI_ENABLE)
    #include "CeNTI_ArrayList_defines.h"
#endif

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_DEFINES_INCLUDES_H__ */

/* -- End of file -- */
