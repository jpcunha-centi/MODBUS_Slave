/* 
 * Path:    Project/CeNTI_Library/lib/Debug/
 * File:    CeNTI_Debug_messages.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_MESSAGES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_MESSAGES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Debug_defines.h"
#if (defined(__CENTI_DEBUG_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Include returns. */
#include "../Utils/CeNTI_Returns.h"


/* ************************************************************************************ */
/* * Default Messages                                                                 * */
/* ************************************************************************************ */
#define CENTI_DEBUG_MSG_RETURN          "[Return]: "
#define CENTI_DEBUG_MSG_WARNING         "[Warn]: "
#define CENTI_DEBUG_MSG_ERROR           "[Error]: "
#define CENTI_DEBUG_MSG_INFO            "[Info]: "
#define CENTI_DEBUG_MSG_VERBOSE         "[Verbose]: "
#define CENTI_DEBUG_MSG_NEW_LINE        "\n"
#define CENTI_DEBUG_MSG_NOT_AVAILABLE   "\"Not Available\" "


/* ************************************************************************************ */
/* * Return Messages                                                                  * */
/* ************************************************************************************ */
#define FOREACH_MSG_RET(MSG_RET) \
        /*     | Name                                   | Return                | Message               |*/ \
        MSG_RET( CENTI_DEBUG_MSG_RET_INITIALIZED        , RET_INITIALIZED       , "Initialized"         )\
        MSG_RET( CENTI_DEBUG_MSG_RET_CONNECTED          , RET_CONNECTED         , "Connected"           )\
        MSG_RET( CENTI_DEBUG_MSG_RET_OK                 , RET_OK                , "Ok"                  )\
        MSG_RET( CENTI_DEBUG_MSG_RET_UNEXPECTED         , RET_UNEXPECTED        , "Unexpected"          )\
        MSG_RET( CENTI_DEBUG_MSG_RET_FAIL               , RET_FAIL              , "Failed"              )\
        MSG_RET( CENTI_DEBUG_MSG_RET_INVALID_PARAMETER  , RET_INVALID_PARAMETER , "Invalid parameter"   )\
        MSG_RET( CENTI_DEBUG_MSG_RET_INVALID_OPERATION  , RET_INVALID_OPERATION , "Invalid operation"   )\
        MSG_RET( CENTI_DEBUG_MSG_RET_NULL_POINTER       , RET_NULL_POINTER      , "Null pointer"        )\
        MSG_RET( CENTI_DEBUG_MSG_RET_TIMEOUT            , RET_TIMEOUT           , "Timeout"             )\
        MSG_RET( CENTI_DEBUG_MSG_RET_NOT_INITIALIZED    , RET_NOT_INITIALIZED   , "Not initialized"     )\
        MSG_RET( CENTI_DEBUG_MSG_RET_DISCONNECTED       , RET_DISCONNECTED      , "Disconnected"        )\
        MSG_RET( CENTI_DEBUG_MSG_RET_EMPTY              , RET_EMPTY             , "Empty"               )\
        MSG_RET( CENTI_DEBUG_MSG_RET_FULL               , RET_FULL              , "Full"                )\
        MSG_RET( CENTI_DEBUG_MSG_RET_BUSY               , RET_BUSY              , "Busy"                )\
        MSG_RET( CENTI_DEBUG_MSG_RET_ASSERTION_FAILED   , RET_ASSERTION_FAILED  , "Assertion failed"    )\
        MSG_RET( CENTI_DEBUG_MSG_RET_COM_CRC_WRONG      , RET_COM_CRC_WRONG     , "Wrong CRC"           )\
        MSG_RET( CENTI_DEBUG_MSG_RET_COM_I2C_FAIL       , RET_COM_I2C_FAIL      , "I2C failed"          )\
        MSG_RET( CENTI_DEBUG_MSG_RET_COM_I2C_NACK       , RET_COM_I2C_NACK      , "I2C nack"            )\
        MSG_RET( CENTI_DEBUG_MSG_RET_COM_SPI_FAIL       , RET_COM_SPI_FAIL      , "SPI failed"          )\
        MSG_RET( CENTI_DEBUG_MSG_RET_COM_UART_FAIL      , RET_COM_UART_FAIL     , "UART failed"         )

#define GENERATE_MSG_RET_ENUM(ENUM, RET, MSG) ENUM,
#define GENERATE_MSG_RET_RET(ENUM, RET, MSG) RET,
#define GENERATE_MSG_RET_MSG(ENUM, RET, MSG) MSG,

typedef enum _enum_msg_ret {
    FOREACH_MSG_RET(GENERATE_MSG_RET_ENUM)
    CENTI_DEBUG_MSG_RET_TOTAL
}et_CENTI_DEBUG_MSG_RET;


#endif /* defined(__CENTI_DEBUG_IN_USE__) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_MESSAGES_H__ */

/* -- End of file -- */
