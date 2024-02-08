/* 
 * Path:    Project/CeNTI_Library/lib/Utils/
 * File:    CeNTI_Warnings.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_WARNINGS_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_WARNINGS_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Tools_defines.h"


/* ************************************************************************************ */
/* * Warnings                                                                         * */
/* ************************************************************************************ */
#if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     ||\
     (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  )

    /* warning: (520) function "..." is never called */
    #pragma warning disable 520

    /* warning: (759) expression generates no code */
    #pragma warning disable 759

    /* warning: (1471) indirect function call via a NULL pointer ignored */
    #pragma warning disable 1471

    /* warning: (1481) call from non-reentrant function "..." might corrupt parameters */
    #pragma warning disable 1481

    /* warning: (1498) pointer (...) in expression may have no targets */
    #pragma warning disable 1498

    /* warning: (1510) non-reentrant function "..." appears in multiple 
     * call graphs and has been duplicated by the compiler */
    #pragma warning disable 1510

    /* warning: (2019) low-priority interrupt vector in table @ 0x8 is unassigned, 
     * will be programmed with a RESET instruction */
    #pragma warning disable 2019

    /* warning: (2053) function "..." is never called */
    #pragma warning disable 2053

#endif /* ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     ||\
           (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  ) */


#endif /* __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_WARNINGS_H__ */

/* -- End of file -- */
