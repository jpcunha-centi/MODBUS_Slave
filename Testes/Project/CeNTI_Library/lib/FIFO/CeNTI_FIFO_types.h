/*
 * Path:    Project/CeNTI_Library/lib/FIFO/
 * File:    CeNTI_FIFO_types.h
 * Author:  CeNTI
 * 
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_FIFO_CENTI_FIFO_TYPES_H__
#define __PROJECT_CENTI_LIBRARY_LIB_FIFO_CENTI_FIFO_TYPES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_FIFO_defines.h"
#if (defined(__CENTI_FIFO_IN_USE__))


/* ************************************************************************************ */
/* * Enumerations                                                                     * */
/* ************************************************************************************ */
typedef enum _enum_fifo_value_type {
    FIFO_VALUE_TYPE_U8 = 0  ,
    FIFO_VALUE_TYPE_CHAR    ,
    FIFO_VALUE_TYPE_FLOAT   ,
}et_FIFO_VALUE_TYPE;


/* ************************************************************************************ */
/* * Instances                                                                        * */
/* ************************************************************************************ */
/* Add '\' between lines. */
/*          | Name          | Type                      | */
#define FOREACH_FIFO(FIFO) \
//        FIFO( FIFO_U8       , FIFO_VALUE_TYPE_U8        ) \
//        FIFO( FIFO_CHAR     , FIFO_VALUE_TYPE_CHAR      ) \
//        FIFO( FIFO_FLOAT    , FIFO_VALUE_TYPE_FLOAT     )

#define GENERATE_FIFO_ENUM(ENUM, TYPE) ENUM,
#define GENERATE_FIFO_TYPE(ENUM, TYPE) TYPE,

typedef enum _enum_fifo {
    FOREACH_FIFO(GENERATE_FIFO_ENUM)
    FIFO_TOTAL
}et_FIFO;


#endif /* defined(__CENTI_FIFO_IN_USE__) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_FIFO_CENTI_FIFO_TYPES_H__ */

/* -- End of file -- */
