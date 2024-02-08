/* 
 * Path:   Project/HAL/COM/UART/ASync/
 * File:   CeNTI_UART_3_ASync.c
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_UART_3_ASYNC__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_UART_3_ASync.h"
#include "../../../../lib/Utils/CeNTI_Data_types.h"
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    #include "driver_init.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))
    #include "../../../../../../config/default/peripheral/sercom/usart/plib_sercom3_usart.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    #include "../../../../../../mcc_generated_files/uart3.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
    #include "../../../../../../mcc_generated_files/uart/uart3.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    #include "usart.h"
#else
    #error UART_3_ASync does not support the CODE_CONFIGURATOR selected!
#endif


/* ************************************************************************************ */
/* * Defines                                                                         * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
	#define UART3_ASYNC_TIMEOUT_TICK		(HAL_MAX_DELAY)
#endif


/* ************************************************************************************ */
/* * Global Declarations                                                              * */
/* ************************************************************************************ */
/* Indication of initialization procedure was successful. */
static bool g_initialized = false;
/* IO structure. */
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    static struct io_descriptor * g_st_io_ptr;
#endif


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET UART_3_ASync__Initialize(void)
{
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        et_RET   et_ret   = RET_UNEXPECTED;
        uint32_t uart_ret = 0;

        /* Initialize UART3. */
        USART3_Initialize();

        /* Get UART3 io descriptor. */
        uart_ret |= usart_async_get_io_descriptor(&USART_3, g_st_io_ptr);

        /* Enable UART3. */
        uart_ret |= usart_async_enable(&USART_3);

        /* Check errors. */
        et_ret = (uart_ret) ? RET_FAIL : RET_OK;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        /* Initialize UART3. */
        SERCOM3_USART_Initialize();

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        /* Initialize UART3. */
        UART3_Initialize();
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        /* Initialize UART3. */
        UART3_Initialize();
        
        UART3_Enable();

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        /* Initialize UART3. */
        MX_USART3_UART_Init();

    #else

        #warning Function not supported by the current CODE_CONFIGURATOR! 

    #endif

    g_initialized = true;

    return RET_OK;
}

et_RET UART_3_ASync__Write(uint8_t * tx_vec,\
                           size_t    tx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    /* Check if pointer is not NULL. */
    CENTI_CHECK_PTR(tx_vec);

    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        /* Write function. */
        io_write(g_st_io_ptr, &(tx_vec[0]), tx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        /* Write function. */
        SERCOM3_USART_Write((uint8_t *)&(tx_vec[0]), tx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        for (size_t i=0; i<tx_vec_size; i++)
        {
            /* Write function. */
            UART3_Write(tx_vec[i]);
        }

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        for (size_t i=0; i<tx_vec_size; i++)
        {
            /* Write function. */
            UART3_Write(tx_vec[i]);
        }

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        et_RET            et_ret     = RET_UNEXPECTED;
        HAL_StatusTypeDef hal_status = HAL_OK;

        /* Write function. */
        hal_status = HAL_UART_Transmit(&huart3,\
                                       &(tx_vec[0]),\
                                       (uint16_t)tx_vec_size,\
                                       (uint32_t)UART3_ASYNC_TIMEOUT_TICK);

        /* Check errors. */
        et_ret = (hal_status == HAL_OK)      ? RET_OK      : \
                 (hal_status == HAL_ERROR)   ? RET_FAIL    : \
                 (hal_status == HAL_TIMEOUT) ? RET_TIMEOUT : \
                 (hal_status == HAL_BUSY)    ? RET_BUSY    : \
                 RET_FAIL;
        CENTI_CHECK_RET(et_ret);

    #else

        #warning Function not supported by the current CODE_CONFIGURATOR!

    #endif

    return RET_OK;
}

et_RET UART_3_ASync__Read(uint8_t * rx_vec,\
                          size_t    rx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    /* Check if pointer is not NULL. */
    CENTI_CHECK_PTR(rx_vec);
    /* Check vector size. */
    if (rx_vec_size <= 0)
    {
        CENTI_CHECK_RET(RET_INVALID_PARAMETER);
    }
        
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        /* Read function. */
        io_read(g_st_io_ptr, &(rx_vec[0]), rx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        /* Read function. */
        SERCOM3_USART_Read((uint8_t *)&(rx_vec[0]), rx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        for (size_t i=0; i<rx_vec_size; i++)
        {
            /* Read function. */
            rx_vec[i] = UART3_Read();
        }

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        for (size_t i=0; i<rx_vec_size; i++)
        {
            /* Read function. */
            rx_vec[i] = UART3_Read();
        }

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        et_RET            et_ret     = RET_UNEXPECTED;
        HAL_StatusTypeDef hal_status = HAL_OK;

        /* Read function. */
        hal_status = HAL_UART_Receive(&huart3,\
                                      &(rx_vec[0]),\
                                      (uint16_t)rx_vec_size,\
                                      (uint32_t)UART3_ASYNC_TIMEOUT_TICK);

        /* Check errors. */
        et_ret = (hal_status == HAL_OK)      ? RET_OK      : \
                 (hal_status == HAL_ERROR)   ? RET_FAIL    : \
                 (hal_status == HAL_TIMEOUT) ? RET_TIMEOUT : \
                 (hal_status == HAL_BUSY)    ? RET_BUSY    : \
                 RET_FAIL;
        CENTI_CHECK_RET(et_ret);

    #else

        #warning Function not supported by the current CODE_CONFIGURATOR!

    #endif

    return RET_OK;
}


#endif /* (defined(__CENTI_UART_3_ASYNC__)) */

/* -- End of file -- */
