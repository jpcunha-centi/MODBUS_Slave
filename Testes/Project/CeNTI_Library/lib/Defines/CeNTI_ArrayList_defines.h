/* 
 * Path:   Project/lib/Defines/
 * File:   CeNTI_ArrayList_defines.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_ARRAYLIST_DEFINES_H__
#define __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_ARRAYLIST_DEFINES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Lib_defines.h"


/* ************************************************************************************ */
/* * ArrayList Defines                                                                * */
/* ************************************************************************************ */
#if ((defined(CENTI_ENABLE_ARRAYLIST))        &&\
     (CENTI_ENABLE_ARRAYLIST == CENTI_ENABLE) )

    /* ******************************************************************************** */
    /* * Defines                                                                      * */
    /* ******************************************************************************** */
    #define __CENTI_ARRAYLIST_IN_USE__

#endif

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_ARRAYLIST_DEFINES_H__ */

/* -- End of file -- */
