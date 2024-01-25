/* 
 * Path:   Project/HAL/COM/UART/RingBuffer/
 * File:   CeNTI_UART_1_RingBuffer.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_HAL_COM_UART_RINGBUFFER_CENTI_UART_1_RINGBUFFER_H__
#define	__PROJECT_CENTI_LIBRARY_HAL_COM_UART_RINGBUFFER_CENTI_UART_1_RINGBUFFER_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_UART_1_RINGBUFFER__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "../../../../lib/CeNTI_lib_includes.h"


/* ************************************************************************************ */
/* * Typedefs                                                                         * */
/* ************************************************************************************ */
typedef void (*t_UART_RingBuffer__Cb) (void);


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Initializes UART1 Ring buffer.
 * 
 * @param   None.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET UART_1_RingBuffer__Initialize(void);

/**
 * @brief Write data.
 * 
 * @param[in]   tx_vec          Vector of data to be transmitted.
 * @param[in]   tx_vec_size     Vector's size.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET UART_1_RingBuffer__Write(uint8_t * tx_vec,\
                                size_t    tx_vec_size);

/**
 * @brief Read data.
 * 
 * @param[out]  rx_vec          Vector of data received.
 * @param[in]   rx_vec_size     Amount of data that will be received.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
et_RET UART_1_RingBuffer__Read(uint8_t * rx_vec,\
                               size_t    rx_vec_size);

/**
 * @brief Sets the callback function to be called when new data is transmitted.
 * 
 * @param[in]   cb_func         Callback function.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET UART_1_RingBuffer__SetTxCB(t_UART_RingBuffer__Cb cb_func);

/** 
 * @brief Sets the callback function to be called when new data is received.
 * 
 * @param[in]   cb_func         Callback function.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET UART_1_RingBuffer__SetRxCB(t_UART_RingBuffer__Cb cb_func);

/**
 * @brief Gets an indication if any data has been received. Also clears the flag
 *          internally.
 * 
 * @param   None.
 * 
 * @return Indication if data has been received.
 * @retval  FLAG_ON     New data has been received.
 * @retval  FLAG_OFF    No new data has been received.
 */
t_FLAG UART_1_RingBuffer__GetTxFlag(void);

/**
 * @brief Gets an indication if any data has been transmitted. Also clears the flag
 *          internally.
 * 
 * @param   None.
 * 
 * @return Indication if data has been transmitted.
 * @retval  FLAG_ON     New data has been transmitted.
 * @retval  FLAG_OFF    No new data has been transmitted.
 */
t_FLAG UART_1_RingBuffer__GetRxFlag(void);

/**
 * @brief Indicates the amount of data received is left to be read.
 *
 * @param   None.
 *
 * @return Amount of data received left to be read.
 */
size_t UART_1_RingBuffer__GetTxRemainSize(void);

/**
 * @brief Indicates the amount of data received is left to be read.
 * 
 * @param   None.
 * 
 * @return Amount of data received left to be read.
 */
size_t UART_1_RingBuffer__GetRxRemainSize(void);

/**
 * @brief Sets the FIFO indexes to the initial position and clears TX flag.
 *
 * @param   None.
 *
 * @return 	None.
 */
void UART_1_RingBuffer__ClearTxFIFO(void);

/**
 * @brief Sets the FIFO indexes to the initial position and clears RX flag.
 *
 * @param   None.
 *
 * @return 	None.
 */
void UART_1_RingBuffer__ClearRxFIFO(void);


#endif /* (defined(__CENTI_UART_1_RINGBUFFER__)) */

#endif /* __PROJECT_CENTI_LIBRARY_HAL_COM_UART_RINGBUFFER_CENTI_UART_1_RINGBUFFER_H__ */

/* -- End of file -- */
