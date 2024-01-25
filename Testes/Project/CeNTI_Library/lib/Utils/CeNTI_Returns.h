/* 
 * Path:    Project/CeNTI_Library/lib/Utils/
 * File:    CeNTI_Returns.h
 * Author:  CeNTI
 * 
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_RETURNS_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_RETURNS_H__


/* ************************************************************************************ */
/* * Returns                                                                          * */
/* ************************************************************************************ */
/* Types of functions returns. */
typedef enum _enum_returns {
    /* ********** Information ********** */
    RET_INITIALIZED         = 1     , /* Initialization complete successfully. */
    RET_CONNECTED           = 2     , /* Device is connected. */

    /* ********** No error ********** */
    RET_OK                  = 0     , /* Everything is fine. */

    /* ********** Generic errors ********** */
    RET_UNEXPECTED          = -1    , /* Usually this error cannot happen. This means that something unexpected happen. */
    RET_FAIL                = -2    , /* Generic error. Indicates that something not specific failed. */
    RET_INVALID_PARAMETER   = -3    , /* Received an invalid parameter value. */
    RET_INVALID_OPERATION   = -4    , /* Tried to execute an illegal operation. */
    RET_NULL_POINTER        = -5    , /* Null pointer. */
    RET_TIMEOUT             = -6    , /* Timeout. */
    RET_NOT_INITIALIZED     = -7    , /* Indication that a device was not initialized, or was wrongly initialized. */
    RET_DISCONNECTED        = -8    , /* Device is not connected or lost connection. */
    RET_EMPTY               = -9    , /* Usually used when a list or a vector is empty. */
    RET_FULL                = -10   , /* Usually used when a list or a vector is full. */
    RET_BUSY                = -11   , /* Something is busy. */
    RET_ASSERTION_FAILED    = -12   , /* Assertion failed. */

    /* ********** Communication errors ********** */
    RET_COM_CRC_WRONG       = -40   , /* CRC is not correct. */
    RET_COM_I2C_FAIL        = -50   , /* I2C communication failed. */
    RET_COM_I2C_NACK        = -51   , /* I2C communication return a nack. */
    RET_COM_SPI_FAIL        = -60   , /* SPI communication failed. */
    RET_COM_UART_FAIL       = -70   , /* UART communication failed. */
}et_RET;


#endif /* __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_RETURNS_H__ */

/* -- End of file -- */
