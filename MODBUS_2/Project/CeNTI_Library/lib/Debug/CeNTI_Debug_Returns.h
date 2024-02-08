/* 
 * Path:    Project/CeNTI_Library/lib/Debug/
 * File:    CeNTI_Debug_Returns.h
 * Author:  CeNTI
 * 
 * Created on January 18, 2024
 * Modified on January 25, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_RETURNS_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_RETURNS_H__


/* ************************************************************************************ */
/* * Returns                                                                          * */
/* ************************************************************************************ */
#define FOREACH_RET(RET)\
        /* | Return type                    | Message               | */    \
        /* | ******** Status and conditions ******                  */      \
        RET( RET_UNEXPECTED                 , "Unexpected"          )       \
        RET( RET_FAIL                       , "Fail"                )       \
        RET( RET_EMPTY                      , "Empty"               )       \
        RET( RET_FULL                       , "Full"                )       \
        RET( RET_BUSY                       , "Busy"                )       \
        RET( RET_NOT_OK                     , "Not OK"              )       \
        RET( RET_ASSERT_FAILED              , "Assert failed"       )       \
        /* | ******** Parameter and state issues ********           */      \
        RET( RET_INVALID_PARAMETER          , "Invalid parameter"   )       \
        RET( RET_INVALID_OPERATION          , "Invalid operation"   )       \
        RET( RET_INVALID_STATE              , "Invalid state"       )       \
        RET( RET_NULL_POINTER               , "Null pointer"        )       \
        RET( RET_NOT_INITIALIZED            , "Not initialized"     )       \
        /* | ******** Connection and availability ********          */      \
        RET( RET_TIMEOUT                    , "Timeout"             )       \
        RET( RET_NOT_CONNECTED              , "Not connected"       )       \
        RET( RET_NOT_FOUND                  , "Not found"           )       \
        RET( RET_NOT_READY                  , "Not ready"           )       \
        RET( RET_CONNECTION_LOST            , "Connection lost"     )       \
        RET( RET_SERVICE_UNAVAILABLE        , "Service unavailable" )       \
        /* | ******** Communication error returns ********          */      \
        RET( RET_COM_CRC_WRONG              , "Comm CRC wrong"      )       \
        RET( RET_COM_NACK                   , "Comm NACK"           )       \
        RET( RET_COM_BUSY                   , "Comm busy"           )       \
        RET( RET_COM_ERROR                  , "Comm error"          )       \
        RET( RET_COM_TIMEOUT                , "Comm timeout"        )       \
        RET( RET_COM_I2C_FAIL               , "Comm I2C fail"       )       \
        RET( RET_COM_I2C_NACK               , "Comm I2C NACK"       )       \
        RET( RET_COM_SPI_FAIL               , "Comm SPI fail"       )       \
        RET( RET_COM_UART_FAIL              , "Comm UART fail"      )       \
        /* | ******** Neutral ********                              */      \
        RET( RET_OK                         , "OK"                  )       \
        /* | ******** Success ********                              */      \
        RET( RET_SMALLER                    , "Smaller"             )       \
        RET( RET_EQUAL                      , "Equal"               )       \
        RET( RET_BIGGER                     , "Bigger"              )       \
        /* | ******** Positive returns ********                     */      \
        RET( RET_READY                      , "Ready"               )       \
        RET( RET_FOUND                      , "Found"               )       \
        RET( RET_CONNECTED                  , "Connected"           )       \
        RET( RET_INITIALIZED                , "Initialized"         )       \
        RET( RET_SUCCESS                    , "Success"             )       

#define GENERATE_RET_ENUM(RET, MSG) RET,

/* Enumeration of returns. */
typedef enum _enum_RETurns {
    FOREACH_RET(GENERATE_RET_ENUM)
    RET_TOTAL
}et_RET;

#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEBUG_CENTI_DEBUG_RETURNS_H__ */

/* -- End of file -- */
