/* 
 * Path:    Project/CeNTI_Library/lib/Debug/
 * File:    CeNTI_Debug.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Debug_defines.h"
#if (defined(__CENTI_DEBUG_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Debug_types.h"


/* ************************************************************************************ */
/* * Global Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Function used to debug an error.
 * 
 * @param[in]   ...
 * 
 * @return      None.
 */
#define CENTI_DEBUG__Error(...)\
        _debug__error(__VA_ARGS__)

/**
 * @brief Function used to debug a return type.
 * 
 * @param[in]   'et_ret': Return type.
 * 
 * @return      None.
 */
#define CENTI_DEBUG__Return(et_ret)\
        _debug__return(et_ret);

/**
 * @brief Function used to debug a warning.
 * 
 * @param   ...
 * 
 * @return  None.
 */
#define CENTI_DEBUG__Warning(...)\
        _debug__warning(__VA_ARGS__)

/**
 * @brief Function used to debug some information.
 * 
 * @param   ...
 * 
 * @return  None.
 */
#define CENTI_DEBUG__Info(...)\
        _debug__info(__VA_ARGS__)

/**
 * @brief Function used to debug some detailed information.
 * 
 * @param   ...
 * 
 * @return  None.
 */
#define CENTI_DEBUG__Verbose(...)\
        _debug__verbose(__VA_ARGS__)


#else /* (defined(__CENTI_DEBUG_IN_USE__)) */

    #define CENTI_DEBUG__Error(...)
    #define CENTI_DEBUG__Return(...)
    #define CENTI_DEBUG__Warning(...)
    #define CENTI_DEBUG__Info(...)
    #define CENTI_DEBUG__Verbose(...)

#endif /* (defined(__CENTI_DEBUG_IN_USE__)) */


#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_H__ */

/* -- End of file -- */
