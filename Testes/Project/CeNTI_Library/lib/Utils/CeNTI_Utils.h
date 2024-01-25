/* 
 * Path:    Project/CeNTI_Library/lib/Utils/
 * File:    CeNTI_Utils.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_UTILS_H__
#define __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_UTILS_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Include data types. */
#include "CeNTI_Data_types.h"

/* Include returns. */
#include "CeNTI_Returns.h"

/* Include Debug library. */
#include "../Debug/CeNTI_Debug.h"


/* ************************************************************************************ */
/* * Checks                                                                           * */
/* ************************************************************************************ */
/* Macro used to check a return variable and if there is an error, debug the error and
 * return the error. */
#define CENTI_CHECK_RET(et_ret) { \
        if ((et_ret) < RET_OK) { \
            CENTI_DEBUG__Return(et_ret);\
            return (et_ret); \
        } \
    }

/* Macro used to check if a initialization is complete and if not, debug a warning
 * message and return a not initialized error. */
#define CENTI_CHECK_INIT(initialized) { \
        if (!(initialized)) { \
            CENTI_DEBUG__Return(RET_NOT_INITIALIZED); \
            return RET_NOT_INITIALIZED; \
        } \
    }

/* Macro used to check if a pointer is not null. If so, debug a warning message and
 * return a null pointer error. */
#define CENTI_CHECK_PTR(ptr) { \
        if ((ptr) == NULL) { \
            CENTI_DEBUG__Return(RET_NULL_POINTER); \
            return RET_NULL_POINTER; \
        } \
    }

/* Macro used to check a return variable and if there is an error, debug the error and
 * return void. */
#define CENTI_CHECK_RET_VOID(et_ret) { \
        if ((et_ret) < RET_OK) { \
            CENTI_DEBUG__Return(et_ret);\
            return; \
        } \
    }


/* ************************************************************************************ */
/* * Bit Macros                                                                       * */
/* ************************************************************************************ */
/* Macro used to set a bit mask. */
#define CENTI_BITMASK_SET(REG, BIT) ( (REG) |= (BIT) )
/* Macro used to clear a bit mask. */
#define CENTI_BITMASK_CLR(REG, BIT) ( (REG) &= ~(BIT) )
/* Macro used to toggle a bit mask. */
#define CENTI_BITMASK_TGL(REG, BIT) ( (REG) ^= (BIT) )
/* Macro used to get a bit mask. */
#define CENTI_BITMASK_GET(REG, BIT) ( (REG) & (BIT) )
/* Macro used to shift a value left. */
#define CENTI_BITSHIFT_LEFT(REG, SHIFT) ( (REG) <<= (SHIFT) )
/* Macro used to shift a value right. */
#define CENTI_BITSHIFT_RIGHT(REG, SHIFT) ( (REG) >>= (SHIFT) )
/* Macro used to check if a bit is set. */
#define CENTI_IS_BIT_SET(REG, BIT) ( ((REG) & (BIT)) != 0 )
/* Macro used to check if a bit is cleared. */
#define CENTI_IS_BIT_CLR(REG, BIT) ( ((REG) & (BIT)) == 0 )


/* ************************************************************************************ */
/* * Vector Macros                                                                    * */
/* ************************************************************************************ */
/* Macro used to get the vector size. */
#define CENTI_GET_VEC_SIZE (sizeof(CENTI_VEC) / sizeof(CENTI_VEC[0]))
/* Macro used to clear a vector. */
#define CENTI_CLEAR_VEC(vec) { \
        memset((vec), 0, sizeof(CENTI_VEC)); \
    }


/* ************************************************************************************ */
/* * Other Macros                                                                     * */
/* ************************************************************************************ */
/* Macro used to check if a condition is true. */
#define CENTI_ASSERT(cond) { \
        if (!(cond)) { \
            CENTI_DEBUG__Return(RET_ASSERTION_FAILED); \
            return RET_ASSERTION_FAILED; \
        } \
    }
/* Macro used to ignore unused parameters. */
#define CENTI_UNUSED_PARAM(x) (void)(x)


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Converts 2 unsigned 8 bits values into 1 unsigned 16 bits value.
 * 
 * @param[in]   msb     Most significant 8 bits value.
 * @param[in]   lsb     Least significant 8 bits values.
 * 
 * @return One unsigned variable with 16 bits.
 */
static inline uint16_t CENTI__2uint8_into_1uint16(uint8_t msb, uint8_t lsb)
    { return (((((uint16_t)msb)<<8)&0xFF00) | ((uint16_t)(lsb&0x00FF))); }

/** 
 * @brief Converts a 8 bits ADC value into a voltage value.
 * 
 * @param[in]   vdd         ADC reference voltage.
 * @param[in]   raw_value   ADC 8 bits raw value.
 * 
 * @return Correspondent voltage value to the raw ADC value.
 */
static inline float CENTI__ADC8b_into_Voltage(float vdd, uint8_t raw_value)
    { return (float)((vdd/(255.0))*((float)raw_value)); }

/**
 * @brief Converts a 12 bits ADC value into a voltage value.
 * 
 * @param[in]   vdd         ADC reference voltage.
 * @param[in]   raw_value   ADC 12 bits raw value.
 * 
 * @return Correspondent voltage value to the raw ADC value.
 */
static inline float CENTI__ADC12b_into_Voltage(float vdd, uint16_t raw_value)
    { return (float)((vdd/(4095.0))*((float)raw_value)); }


#endif /* __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_UTILS_H__ */

/* -- End of file -- */
