/* 
 * Path:    Project/CeNTI_Library/lib/CRC/
 * File:    CeNTI_CRC_types.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 25, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_CRC_CENTI_CRC_TYPES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_CRC_CENTI_CRC_TYPES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_CRC_defines.h"
#if (defined(__CENTI_CRC_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include <stdbool.h>


/* ************************************************************************************ */
/* * CRC 8 bits                                                                       * */
/* ************************************************************************************ */
#define GENERATE_CRC_8_ENUM(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) ENUM,
#define GENERATE_CRC_8_INIT(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) INIT,
#define GENERATE_CRC_8_POLY(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) POLY, 
#define GENERATE_CRC_8_XOROUT(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) XOROUT,
#define GENERATE_CRC_8_REFIN(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) REFIN,
#define GENERATE_CRC_8_REFOUT(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) REFOUT,

/* Add '\' between lines */
/*           | Algorithm                | Init  | Poly  | XorOut| RefIn | RefOut| */ 
#define FOREACH_CRC_8BITS(CRC_8) 
//        CRC_8( CRC_8BITS_8              , 0xFF  , 0x31  , 0x00   , false , false )
//        CRC_8( CRC_8BITS_CDMA2000       , 0xFF  , 0x9B  , 0x00   , false , false )
//        CRC_8( CRC_8BITS_DARC           , 0x00  , 0x39  , 0x00   , true  , true  )
//        CRC_8( CRC_8BITS_DVB_S2         , 0x00  , 0xD5  , 0x00   , false , false )
//        CRC_8( CRC_8BITS_EBU            , 0xFF  , 0x1D  , 0x00   , true  , true  )
//        CRC_8( CRC_8BITS_I_CODE         , 0xFD  , 0x1D  , 0x00   , false , false )
//        CRC_8( CRC_8BITS_ITU            , 0x00  , 0x07  , 0x55   , false , false )
//        CRC_8( CRC_8BITS_MAXIM          , 0x00  , 0x31  , 0x00   , true  , true  )
//        CRC_8( CRC_8BITS_ROHC           , 0xFF  , 0x07  , 0x00   , true  , true  )
//        CRC_8( CRC_8BITS_WCDMA          , 0x00  , 0x9B  , 0x00   , true  , true  )

typedef enum _enum_crc_8_bits {
    FOREACH_CRC_8BITS(GENERATE_CRC_8_ENUM)
    CRC_8BITS_TOTAL
} et_CRC_8BITS;


/* ************************************************************************************ */
/* * CRC 16 bits                                                                      * */
/* ************************************************************************************ */
#define GENERATE_CRC_16_ENUM(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) ENUM,
#define GENERATE_CRC_16_INIT(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) INIT,
#define GENERATE_CRC_16_POLY(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) POLY, 
#define GENERATE_CRC_16_XOROUT(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) XOROUT,
#define GENERATE_CRC_16_REFIN(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) REFIN,
#define GENERATE_CRC_16_REFOUT(ENUM, INIT, POLY, XOROUT, REFIN, REFOUT) REFOUT,

/* Add '\' between lines */
/*            | Algorithm               | Init   | Poly   | XorOut | RefIn | RefOut |*/
#define FOREACH_CRC_16BITS(CRC_16)
//        CRC_16( CRC_16BITS_CCITT_FALSE  , 0xFFFF , 0x1021 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_ARC          , 0x0000 , 0x8005 , 0x0000 , true  , true   )
//        CRC_16( CRC_16BITS_AUG_CCITT    , 0x1D0F , 0x1021 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_BYPASS       , 0x0000 , 0x8005 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_CDMA2000     , 0xFFFF , 0xC867 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_DDS_110      , 0x800D , 0x8005 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_DECT_R       , 0x0000 , 0x0589 , 0x0001 , false , false  )
//        CRC_16( CRC_16BITS_DECT_X       , 0x0000 , 0x0589 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_DNP          , 0x0000 , 0x3D65 , 0xFFFF , true  , true   )
//        CRC_16( CRC_16BITS_EN_13757     , 0x0000 , 0x3D65 , 0xFFFF , false , false  )
//        CRC_16( CRC_16BITS_GENIBUS      , 0xFFFF , 0x1021 , 0xFFFF , false , false  )
//        CRC_16( CRC_16BITS_MAXIM        , 0x0000 , 0x8005 , 0xFFFF , true  , true   )
//        CRC_16( CRC_16BITS_MCRF4XX      , 0xFFFF , 0x1021 , 0x0000 , true  , true   )
//        CRC_16( CRC_16BITS_RIELLO       , 0xB2AA , 0x1021 , 0x0000 , true  , true   )
//        CRC_16( CRC_16BITS_T10_DIF      , 0x0000 , 0x8BB7 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_TELEDISK     , 0x0000 , 0xA097 , 0x0000 , false , false  )
//        CRC_16( CRC_16BITS_TMS37157     , 0x89EC , 0x1021 , 0x0000 , true  , true   )
//        CRC_16( CRC_16BITS_USB          , 0xFFFF , 0x8005 , 0xFFFF , true  , true   )
//        CRC_16( CRC_16BITS_A            , 0xC6C6 , 0x1021 , 0x0000 , true  , true   )
//        CRC_16( CRC_16BITS_KERMIT       , 0x0000 , 0x1021 , 0x0000 , true  , true   )
//        CRC_16( CRC_16BITS_MODBUS       , 0xFFFF , 0x8005 , 0x0000 , true  , true   )
//        CRC_16( CRC_16BITS_X_25         , 0xFFFF , 0x1021 , 0xFFFF , true  , true   )
//        CRC_16( CRC_16BITS_XMODEM       , 0x0000 , 0x1021 , 0x0000 , false , false  )

typedef enum _enum_crc_16_bits {
    FOREACH_CRC_16BITS(GENERATE_CRC_16_ENUM)
    CRC_16BITS_TOTAL
} et_CRC_16BITS;


#endif /* defined(__CENTI_CRC_IN_USE__) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_CRC_CENTI_CRC_TYPES_H__ */

/* -- End of file -- */
