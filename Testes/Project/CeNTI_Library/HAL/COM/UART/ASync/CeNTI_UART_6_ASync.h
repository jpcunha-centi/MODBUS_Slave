/* 
 * Path:   Project/HAL/COM/UART/ASync/
 * File:   CeNTI_UART_6_ASync.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_COM_UART_ASYNC_CENTI_UART_6_ASYNC_H__
#define	__PROJECT_CENTI_LIBRARY_HAL_COM_UART_ASYNC_CENTI_UART_6_ASYNC_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_UART_6_ASYNC__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "../../../../lib/CeNTI_lib_includes.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Initialize UART peripheral.
 * 
 * @param   None.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET UART_6_ASync__Initialize(void);

/**
 * @brief Write data.
 * 
 * @param[in]   tx_vec          Tx vector.
 * @param[in]   tx_vec_size     Tx vector size.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET UART_6_ASync__Write(uint8_t * tx_vec,\
                           size_t    tx_vec_size);

/**
 * @brief Read data.
 * 
 * @param[out]  rx_vec          Rx vector.
 * @param[in]   rx_vec_size     Rx vector size.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET UART_6_ASync__Read(uint8_t * rx_vec,\
                          size_t    rx_vec_size);


#endif /* (defined(__CENTI_UART_6_ASYNC__)) */

#endif /* __PROJECT_CENTI_LIBRARY_HAL_COM_UART_ASYNC_CENTI_UART_6_ASYNC_H__ */

/* -- End of file -- */
