/* 
 * Path:   Project/HAL/COM/SPI/Master/
 * File:   CeNTI_SPI_5_Master.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_COM_SPI_MASTER_CENTI_SPI_5_MASTER_H__
#define	__PROJECT_CENTI_LIBRARY_HAL_COM_SPI_MASTER_CENTI_SPI_5_MASTER_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_SPI_5_MASTER__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "../../../../lib/CeNTI_lib_includes.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/*
 * @brief Initializes SPI5 master.
 * 
 * @param   None.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET SPI_5_Master__Initialize(void);

/* 
 * @brief Write data.
 * 
 * @param[in]   tx_vec          Vector of data to be transmitted.
 * @param[in]   tc_vec_size     Amount of data to be transmitted.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET SPI_5_Master__Write(uint8_t * tx_vec,\
                           size_t    tx_vec_size);

/*
 * @brief Read data.
 * 
 * @param[out]  rx_vec          Vector where received data will be stored.
 * @param[in]   rx_vec_size     Amount of data to be read.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET SPI_5_Master__Read(uint8_t * rx_vec,\
                          size_t    rx_vec_size);

/*
 * @brief Exchange data.
 * 
 * @param[in]   tx_vec          Vector of data to be transmitted.
 * @param[in]   tx_vec_size     Amount of data to be transmitted.
 * @param[out]  rx_vec          Vector where received data will be stored.
 * @param[in]   rx_vec_size     Amount of data to be read.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET SPI_5_Master__Exchange(uint8_t * tx_vec,\
                              size_t    tx_vec_size,\
                              uint8_t * rx_vec,\
                              size_t    rx_vec_size);


#endif /* (defined(__CENTI_SPI_5_MASTER__)) */

#endif /* __PROJECT_CENTI_LIBRARY_HAL_COM_SPI_MASTER_CENTI_SPI_5_MASTER_H__ */

/* -- End of file -- */
