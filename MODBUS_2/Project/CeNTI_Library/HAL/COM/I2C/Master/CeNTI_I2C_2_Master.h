/* 
 * Path:   Project/HAL/COM/I2C/Master/
 * File:   CeNTI_I2C_2_Master.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_COM_I2C_MASTER_CENTI_I2C_2_MASTER_H__
#define	__PROJECT_CENTI_LIBRARY_HAL_COM_I2C_MASTER_CENTI_I2C_2_MASTER_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_I2C_2_MASTER__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "../../../../lib/CeNTI_lib_includes.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Initializes I2C2.
 * 
 * @param   None.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET I2C_2_Master__Initialize(void);

/**
 * @brief Writes data.
 * 
 * @param[in]   i2c_address     Device address.
 * @param[in]   tx_vec          Vector with data to be transmitted.
 * @param[in]   tx_vec_size     Amount off data to be transmitted.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET I2C_2_Master__Write(uint8_t   i2c_address,\
                           uint8_t * tx_vec,\
                           size_t    tx_vec_size);

/**
 * @brief Reads data.
 * 
 * @param[in]   i2c_address     Device address.
 * @param[out]  rx_vec          Vector where received data will be stored.
 * @param[in]   rx_vec_size     Amount of data to be read.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET I2C_2_Master__Read(uint8_t   i2c_address,\
                          uint8_t * rx_vec,\
                          size_t    rx_vec_size);

/**
 * @brief Writes data and then reads data.
 * 
 * @param[in]   i2c_address     Device address.
 * @param[in]   tx_vec          Vector with data to be transmitted.
 * @param[in]   tx_vec_size     Amount of data to be transmitted.
 * @param[out]  rx_vec          Vector where received data will be stored.
 * @param[in]   rx_vec_size     Amount of data to be read.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET I2C_2_Master__WriteRead(uint8_t   i2c_address,\
                               uint8_t * tx_vec,\
                               size_t    tx_vec_size,\
                               uint8_t * rx_vec,\
                               size_t    rx_vec_size);

/**
 * @brief Performs a double write without closing the communication in between.
 * 
 * @param[in]   i2c_address     Device address.
 * @param[in]   tx_vec_1        First data to be transmitted.
 * @param[in]   tx_vec_1_size   First data size.
 * @param[in]   tx_vec_2        Last data to be transmitted.
 * @param[in]   tx_vec_2_size   Last data size.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET I2C_2_Master__DoubleWrite(uint8_t   i2c_address,\
                                 uint8_t * tx_vec_1,\
                                 size_t    tx_vec_1_size,\
                                 uint8_t * tx_vec_2,\
                                 size_t    tx_vec_2_size);


#endif /* (defined(__CENTI_I2C_2_MASTER__)) */

#endif	/* __PROJECT_CENTI_LIBRARY_HAL_COM_I2C_MASTER_CENTI_I2C_2_MASTER_H__ */

/* -- End of file -- */
