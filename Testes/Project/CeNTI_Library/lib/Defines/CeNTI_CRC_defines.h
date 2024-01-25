/* 
 * Path:   Project/lib/Defines/
 * File:   CeNTI_CRC.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_CRC_DEFINES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_CRC_DEFINES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Lib_defines.h"


/* ************************************************************************************ */
/* * CRC Defines                                                                      * */
/* ************************************************************************************ */
#if ((defined(CENTI_ENABLE_CRC))        &&\
     (CENTI_ENABLE_CRC == CENTI_ENABLE) )

    /* ******************************************************************************** */
    /* * Defines                                                                      * */
    /* ******************************************************************************** */
    #define __CENTI_CRC_IN_USE__

#endif

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_CRC_DEFINES_H__ */

/* -- End of file -- */
