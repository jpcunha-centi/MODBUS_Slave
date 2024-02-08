/* 
 * Path:    Project/CeNTI_Library/lib/CRC/
 * File:    CeNTI_CRC.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_CRC_CRC_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_CRC_CRC_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_CRC_defines.h"
#if (defined(__CENTI_CRC_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_CRC_types.h"
#include "../Utils/CeNTI_Data_types.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Calculate a 8 bits CRC.
 * 
 * @param[in]   et_crc          CRC instance.
 * @param[in]   data_vec        Data vector.
 * @param[in]   data_vec_size   Data vector size.
 * 
 * @return      8 bits CRC value.
 */
uint8_t CENTI_CRC_8__Calculate(et_CRC_8BITS   et_crc,\
                               uint8_t *const data_vec,\
                               size_t         data_vec_size);

/**
 * @brief Calculate a 16 bits CRC.
 * 
 * @param[in]   et_crc          CRC instance.
 * @param[in]   data_vec        Data vector.
 * @param[in]   data_vec_size   Data vector size.
 * 
 * @return      16 bits CRC value.
 */
uint16_t CENTI_CRC_16__Calculate(et_CRC_16BITS  et_crc,\
                                 uint8_t *const data_u8_vec,\
                                 size_t         data_size);


#endif /* (defined(__CENTI_CRC_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_CRC_CENTI_CRC_H__ */

/* -- End of file -- */
