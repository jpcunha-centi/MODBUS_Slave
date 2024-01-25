/*
 * Path:    Project/CeNTI_Library/lib/Defines/
 * File:    CeNTI_FIFO_defines.h
 * Author:  CeNTI
 * 
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_FIFO_DEFINES_H__
#define __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_FIFO_DEFINES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Lib_defines.h"


/* ************************************************************************************ */
/* * FIFO Defines                                                                     * */
/* ************************************************************************************ */
#if ((defined(CENTI_ENABLE_FIFO))           && \
     (CENTI_ENABLE_FIFO == CENTI_ENABLE)    )

    /* ******************************************************************************** */
    /* * Defines                                                                      * */
    /* ******************************************************************************** */
    #define __CENTI_FIFO_IN_USE__
    
#endif

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_FIFO_DEFINES_H__ */

/* -- End of file -- */
