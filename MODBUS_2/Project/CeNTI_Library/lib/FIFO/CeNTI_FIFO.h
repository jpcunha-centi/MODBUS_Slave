/* 
 * Path:    Project/CeNTI_Library/lib/FIFO/
 * File:    CeNTI_FIFO.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_FIFO_CENTI_FIFO_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_FIFO_CENTI_FIFO_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_FIFO_defines.h"
#if (defined(__CENTI_FIFO_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_FIFO_types.h"
#include "../Utils/CeNTI_Returns.h"


/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */
/**
 * @brief Initialize FIFO with pointer and size.
 * 
 * @param[in]   et_fifo     FIFO instance.
 * @param[in]   vec_ptr     FIFO first position reference.
 * @param[in]   vec_size    FIFO size.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK      Everything worked fine.
 * @retval      Other       See et_RET.
 */
et_RET FIFO__Initialize(et_FIFO et_fifo,\
                        void *  vec_ptr,\
                        size_t  vec_size);

/**
 * @brief Set value into FIFO.
 * 
 * @param[in]   et_fifo     FIFO instance.
 * @param[in]   value_ptr   New value to store in the FIFO.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK      Everything worked fine.
 * @retval      Other       See et_RET.
 */
et_RET FIFO__Set(et_FIFO et_fifo,\
                 void *  value_ptr);

/**
 * @brief Get value from FIFO.
 * 
 * @param[in]   et_fifo     FIFO instance.
 * @param[out]  value_ptr   New value from the FIFO.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK      Everything worked fine.
 * @retval      Other       See et_RET.
 */
et_RET FIFO__Get(et_FIFO et_fifo,\
                 void *  value_ptr);

/**
 * @brief Get amount of bytes unread.
 * 
 * @param[in]   et_fifo     FIFO instance.
 * 
 * @return      size_t      Amount of bytes unread.
 */
size_t FIFO__GetRemain(et_FIFO et_fifo);


#endif /* defined(__CENTI_FIFO_IN_USE__) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_FIFO_CENTI_FIFO_H__ */

/* -- End of file -- */
