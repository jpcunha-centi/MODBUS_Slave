/* 
 * Path:   Project/HAL/COM/UART/RingBuffer/
 * File:   CeNTI_UART_7_RingBuffer.c
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_UART_7_RINGBUFFER__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_UART_7_RingBuffer.h"
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    #error UART_7_RingBuffer does not support the CODE_CONFIGURATOR selected!
#elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))
    #include "../../../../../../config/default/peripheral/sercom/usart/plib_sercom7_usart.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    #include "../../../../../../mcc_generated_files/uart7.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
    #include "../../../../../../mcc_generated_files/uart/uart7.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    #include "usart.h"
    #if (defined(__STM32L4_CUBEMX_ARM__))
        #include "stm32l4xx_hal_uart.h"
    #else
        #error Not defined!
#endif
#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))
    #include "sl_uartdrv_instances.h"
    #include "sl_uartdrv_usart_centi_uart_7_config.h"

    /* If CTS and RTS not defined, define a default value to avoid errors */
    #ifndef SL_UARTDRV_USART_CENTI_UART_7_CTS_PORT
        #define SL_UARTDRV_USART_CENTI_UART_7_CTS_PORT  gpioPortA
        #define SL_UARTDRV_USART_CENTI_UART_7_CTS_PIN   0
        #if defined(_USART_ROUTELOC7_MASK)
            #define SL_UARTDRV_USART_CENTI_UART_7_CTS_LOC   0
        #endif
    #endif

    #ifndef SL_UARTDRV_USART_CENTI_UART_7_RTS_PORT
        #define SL_UARTDRV_USART_CENTI_UART_7_RTS_PORT  gpioPortA
        #define SL_UARTDRV_USART_CENTI_UART_7_RTS_PIN   0
        #if defined(_USART_ROUTELOC7_MASK)
            #define SL_UARTDRV_USART_CENTI_UART_7_RTS_LOC   0
        #endif
    #endif
    /* Define RX and TX buffer queues */
    DEFINE_BUF_QUEUE(SL_UARTDRV_USART_CENTI_UART_7_RX_BUFFER_SIZE,\
                     sl_uartdrv_usart_centi_uart_7_rx_buffer);
    DEFINE_BUF_QUEUE(SL_UARTDRV_USART_CENTI_UART_7_TX_BUFFER_SIZE,\
                     sl_uartdrv_usart_centi_uart_7_tx_buffer);

#else
    #error UART_7_RingBuffer does not support the CODE_CONFIGURATOR selected!
#endif


/* ************************************************************************************ */
/* * Defines                                                                         * */
/* ************************************************************************************ */
#if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     ||\
     (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  ||\
     (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))	)

    #define RX_BUFFER_SIZE  (100)
    #define TX_BUFFER_SIZE  (100)

#endif

#if (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    #define UART7_TIMEOUT_TICK  (HAL_MAX_DELAY)
#endif


/* ************************************************************************************ */
/* * Global variables                                                                 * */
/* ************************************************************************************ */
/* Indication if initialization procedure was successful. */
static bool g_initialized = false;

/* Flags that indicates data transmission/reception. */
static t_FLAG f_RX = false;
static t_FLAG f_TX = false;

#if (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    static uint8_t g_rx_byte = 0;
#endif

/* FIFO variables. */
#if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     ||\
     (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  ||\
     (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))	)

    /* FIFO vector. */
    static uint8_t g_rx_vec[RX_BUFFER_SIZE] = {};
    static uint8_t g_tx_vec[TX_BUFFER_SIZE] = {};
    /* Write FIFO index. */
    static size_t g_rx_set_idx = 0;
    static size_t g_tx_set_idx = 0;
    /* Read FIFO index. */
    static size_t g_rx_get_idx = 0;
    static size_t g_tx_get_idx = 0;

#else
    
    static size_t g_rx_total = 0;
    
#endif


/* ************************************************************************************ */
/* * Macros                                                                           * */
/* ************************************************************************************ */
#if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     ||\
     (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  ||\
     (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))	)
    
    /* Increment FIFO index. */
    #define RX_SET_IDX_INC() \
        { g_rx_set_idx = ((g_rx_set_idx+1) >= RX_BUFFER_SIZE) ? 0 : (g_rx_set_idx+1); }
    #define RX_GET_IDX_INC() \
        { g_rx_get_idx = ((g_rx_get_idx+1) >= RX_BUFFER_SIZE) ? 0 : (g_rx_get_idx+1); }
    #define TX_SET_IDX_INC() \
        { g_tx_set_idx = ((g_tx_set_idx+1) >= TX_BUFFER_SIZE) ? 0 : (g_tx_set_idx+1); }
    #define TX_GET_IDX_INC() \
        { g_tx_get_idx = ((g_tx_get_idx+1) >= TX_BUFFER_SIZE) ? 0 : (g_tx_get_idx+1); }
    

    /* Add value to FIFO. */
    #define RX_FIFO_Add(new_value) \
        { \
            g_rx_vec[g_rx_set_idx] = new_value; \
            RX_SET_IDX_INC(); \
        }
    #define TX_FIFO_Add(new_value) \
        { \
            g_tx_vec[g_tx_set_idx] = new_value; \
            TX_SET_IDX_INC(); \
        }
    
    /* Get value from FIFO. */
    #define RX_FIFO_Get(new_value) \
        { \
            new_value = g_rx_vec[g_rx_get_idx]; \
            RX_GET_IDX_INC(); \
        }
    #define TX_FIFO_Get(new_value) \
        { \
            new_value = g_tx_vec[g_tx_get_idx]; \
            TX_GET_IDX_INC(); \
        }

#endif


/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */
/* Pointer to a outside function that will be called when a Rx interrupt occur. */
static t_UART_RingBuffer__Cb UART_7_CB__Rx;
/* Pointer to a outside function that will be called when a Tx interrupt occur. */
static t_UART_RingBuffer__Cb UART_7_CB__Tx;

#if (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

    /*
    * @brief Function called when an interruption occur because of received data from
    *           UART.
    * 
    * @param[in] event ...
    * @param[in] context ...
    * 
    * @return None.
    */
    static void UART_7_ISR__Rx(SERCOM_USART_EVENT event, uintptr_t context);

    /*
    * @brief Function called when an interruption occur because of transmitted data from
    *          UART.
    * 
    * @param[in] event ...
    * @param[in] context ...
    * 
    * @return None.
    */
    static void UART_7_ISR__Tx(SERCOM_USART_EVENT event, uintptr_t context);

#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))
    
    /*
    * @brief Function called when an interruption occur because of transmitted data from
    *          UART.
    * 
    * @param[in] event ...
    * @param[in] context ...
    * 
    * @return None.
    */
   static void UART_7_ISR__Tx(struct UARTDRV_HandleData *   handle,
                              Ecode_t                       transferStatus,
                              uint8_t *                     data,
                              UARTDRV_Count_t               transferCount);

    /*
    * @brief Function called when an interruption occur because of received data from
    *           UART.
    * 
    * @param[in] event ...
    * @param[in] context ...
    * 
    * @return None.
    */
   static void UART_7_ISR__Rx(struct UARTDRV_HandleData *   handle,
                              Ecode_t                       transferStatus,
                              uint8_t *                     data,
                              UARTDRV_Count_t               transferCount);

#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

    /* Nothing. */

#else

    /**
     * @brief Function called when an interruption occur because of received data from
     *          UART.
     * 
     * @param None.
     * 
     * @return None.
     */
    static void UART_7_ISR__Rx(void);

    /**
     * @brief Function called when an interruption occur because of transmitted data from
     *          UART.
     * 
     * @param None.
     * 
     * @return None.
     */
    static void UART_7_ISR__Tx(void);

#endif


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET UART_7_RingBuffer__Initialize(void)
{    
    /* Clear flags. */
    f_TX = FLAG_OFF;
    f_RX = FLAG_OFF;

    /* Clear callbacks. */
    UART_7_CB__Tx = NULL;
    UART_7_CB__Rx = NULL;
    
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        #warning Function not supported by the current CODE_CONFIGURATOR selected!

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        /* Initialize UART7. */
        SERCOM7_USART_Initialize();
        
        /* Set Tx callback function. */
        SERCOM7_USART_WriteCallbackRegister(\
                (SERCOM_USART_RING_BUFFER_CALLBACK)UART_7_ISR__Tx, 0);  
        
        /* Set Rx callback function. */
        SERCOM7_USART_ReadCallbackRegister(\
                (SERCOM_USART_RING_BUFFER_CALLBACK)UART_7_ISR__Rx, 0);
        
        g_rx_total = 0;
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
        g_rx_set_idx = 0;
        g_rx_get_idx = 0;
        g_tx_set_idx = 0;
        g_tx_get_idx = 0;
        
        UART7_Initialize();
        
        UART7_SetRxInterruptHandler(UART_7_ISR__Rx);
        UART7_SetTxInterruptHandler(UART_7_ISR__Tx);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
    
        g_rx_set_idx = 0;
        g_rx_get_idx = 0;
        g_tx_set_idx = 0;
        g_tx_get_idx = 0;
        
        UART7_Initialize();
        
        UART7_Enable();
        UART7_ReceiveEnable();
        UART7_ReceiveInterruptEnable();
        UART7_TransmitEnable();
        UART7_TransmitInterruptEnable();
        
        UART7_RxCompleteCallbackRegister(UART_7_ISR__Rx);
        UART7_TxCompleteCallbackRegister(UART_7_ISR__Tx);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        MX_USART7_UART_Init();

        HAL_NVIC_SetPriority(USART7_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART7_IRQn);

        HAL_UART_Receive_IT(&huart7, &g_rx_byte, 1);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        /* Create uartdrv initialization structs */
        UARTDRV_InitUart_t sl_uartdrv_usart_init_centi_uart_7 = {
            .port     = SL_UARTDRV_USART_CENTI_UART_7_PERIPHERAL,
            .baudRate = SL_UARTDRV_USART_CENTI_UART_7_BAUDRATE,
            #if defined(_USART_ROUTELOC0_MASK)
                .portLocationTx = SL_UARTDRV_USART_CENTI_UART_7_TX_LOC,
                .portLocationRx = SL_UARTDRV_USART_CENTI_UART_7_RX_LOC,
            #elif defined(_USART_ROUTE_MASK)
                .portLocation = SL_UARTDRV_USART_CENTI_UART_7_ROUTE_LOC,
            #elif defined(_GPIO_USART_ROUTEEN_MASK)
                .txPort  = SL_UARTDRV_USART_CENTI_UART_7_TX_PORT,
                .rxPort  = SL_UARTDRV_USART_CENTI_UART_7_RX_PORT,
                .txPin   = SL_UARTDRV_USART_CENTI_UART_7_TX_PIN,
                .rxPin   = SL_UARTDRV_USART_CENTI_UART_7_RX_PIN,
                .uartNum = SL_UARTDRV_USART_CENTI_UART_7_PERIPHERAL_NO,
            #endif
            .stopBits     = SL_UARTDRV_USART_CENTI_UART_7_STOP_BITS,
            .parity       = SL_UARTDRV_USART_CENTI_UART_7_PARITY,
            .oversampling = SL_UARTDRV_USART_CENTI_UART_7_OVERSAMPLING,
            #if defined(USART_CTRL_MVDIS)
                .mvdis = SL_UARTDRV_USART_CENTI_UART_7_MVDIS,
            #endif
            .fcType  = SL_UARTDRV_USART_CENTI_UART_7_FLOW_CONTROL_TYPE,
            .ctsPort = SL_UARTDRV_USART_CENTI_UART_7_CTS_PORT,
            .rtsPort = SL_UARTDRV_USART_CENTI_UART_7_RTS_PORT,
            .ctsPin  = SL_UARTDRV_USART_CENTI_UART_7_CTS_PIN,
            .rtsPin  = SL_UARTDRV_USART_CENTI_UART_7_RTS_PIN,
            .rxQueue = (UARTDRV_Buffer_FifoQueue_t *)&sl_uartdrv_usart_centi_uart_7_rx_buffer,
            .txQueue = (UARTDRV_Buffer_FifoQueue_t *)&sl_uartdrv_usart_centi_uart_7_tx_buffer,
            #if defined(_USART_ROUTELOC7_MASK)
                .portLocationCts = SL_UARTDRV_USART_CENTI_UART_7_CTS_LOC,
                .portLocationRts = SL_UARTDRV_USART_CENTI_UART_7_RTS_LOC,
            #endif
        };

        Ecode_t ecode   = ECODE_EMDRV_UARTDRV_OK;
        et_RET  et_ret  = RET_UNEXPECTED;

        ecode = UARTDRV_InitUart(sl_uartdrv_usart_centi_uart_7_handle,\
                                 &sl_uartdrv_usart_init_centi_uart_7);

        et_ret = (ecode == ECODE_EMDRV_UARTDRV_OK)             ? RET_OK                : \
                 (ecode == ECODE_EMDRV_UARTDRV_PARAM_ERROR)    ? RET_INVALID_PARAMETER : \
                 (ecode == ECODE_EMDRV_UARTDRV_ILLEGAL_HANDLE) ? RET_NULL_POINTER      : \
                                                                 RET_COM_UART_FAIL;

        CENTI_CHECK_RET(et_ret);
        
        g_rx_total = 0;

    #else
    
        #warning Function not supported by the current CODE_CONFIGURATOR selected!

    #endif
    
    g_initialized = true;
    
    return RET_OK;
} 

et_RET UART_7_RingBuffer__Write(uint8_t * tx_vec,\
                                size_t    tx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);

    #if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     ||\
         (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  ||\
         (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))	)

        /* Check if new data is not bigger than the FIFO size. */
        if (TX_BUFFER_SIZE < tx_vec_size)
        {
            CENTI_CHECK_RET(RET_INVALID_PARAMETER);
        }

    #endif
    
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    
        #warning Function not supported by the current CODE_CONFIGURATOR selected!

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

       SERCOM7_USART_Write(&(tx_vec[0]), tx_vec_size);

    #elif ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))   || \
           (defined(__CENTI_CODE_CONFIGURATOR_MELODY__)))
    
        for (uint8_t n_data=0; n_data<tx_vec_size; n_data++)
        {
           TX_FIFO_Add(tx_vec[n_data]);
        }
        
        /* Send first byte. */
        UART_7_ISR__Tx();

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        for (uint8_t n_data=0; n_data<tx_vec_size; n_data++)
        {
            TX_FIFO_Add(tx_vec[n_data]);
        }

        /* Send first byte. */
        HAL_UART_TxCpltCallback(&huart7);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        Ecode_t ecode  = ECODE_EMDRV_UARTDRV_OK;
        et_RET  et_ret = RET_UNEXPECTED;

        ecode = UARTDRV_Transmit(sl_uartdrv_usart_centi_uart_7_handle,\
                                 &(tx_vec[0]),\
                                 tx_vec_size,\
                                 UART_7_ISR__Tx);

        et_ret = (ecode == ECODE_EMDRV_UARTDRV_OK)             ? RET_OK                : \
                 (ecode == ECODE_EMDRV_UARTDRV_PARAM_ERROR)    ? RET_INVALID_PARAMETER : \
                 (ecode == ECODE_EMDRV_UARTDRV_ILLEGAL_HANDLE) ? RET_NULL_POINTER      : \
                                                                 RET_COM_UART_FAIL;

        CENTI_CHECK_RET(et_ret);

    #else
    
        #warning Function not supported by the current CODE_CONFIGURATOR selected!

    #endif

    return RET_OK;
}

et_RET UART_7_RingBuffer__Read(uint8_t * rx_vec,\
                               size_t    rx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    /* Check if pointer is not NULL. */
    CENTI_CHECK_PTR(rx_vec);

    #if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     ||\
         (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  ||\
         (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))	)

        /* Check vector size. */
        if ((rx_vec_size > UART_7_RingBuffer__GetRxRemainSize()) || \
            (rx_vec_size <= 0))
        {
            CENTI_CHECK_RET(RET_INVALID_PARAMETER);
        }

    #endif

    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    
        #warning Function not supported by the current CODE_CONFIGURATOR selected!

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        SERCOM7_USART_Read(&(rx_vec[0]), rx_vec_size);
    
        g_rx_total -= rx_vec_size;
        
    #elif ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))   || \
           (defined(__CENTI_CODE_CONFIGURATOR_MELODY__)))
    
        for (uint8_t n_data=0; n_data<rx_vec_size; n_data++)
        {
            RX_FIFO_Get(rx_vec[n_data]);
        }
        
        f_RX = FLAG_OFF;
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        for (uint8_t n_data=0; n_data<rx_vec_size; n_data++)
        {
            RX_FIFO_Get(rx_vec[n_data]);
        }

        f_RX = FLAG_OFF;

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        Ecode_t ecode  = ECODE_EMDRV_UARTDRV_OK;
        et_RET  et_ret = RET_UNEXPECTED;

        ecode = UARTDRV_Receive(sl_uartdrv_usart_centi_uart_7_handle,\
                                &(rx_vec[0]),\
                                rx_vec_size,\
                                UART_7_ISR__Rx);
        
        g_rx_total -= rx_vec_size;
        
        et_ret = (ecode == ECODE_EMDRV_UARTDRV_OK)             ? RET_OK                : \
                 (ecode == ECODE_EMDRV_UARTDRV_PARAM_ERROR)    ? RET_INVALID_PARAMETER : \
                 (ecode == ECODE_EMDRV_UARTDRV_ILLEGAL_HANDLE) ? RET_NULL_POINTER      : \
                                                                 RET_COM_UART_FAIL;

        CENTI_CHECK_RET(et_ret);

    #else
    
        #warning Function not supported by the current CODE_CONFIGURATOR selected!

    #endif

    return RET_OK;
}

et_RET UART_7_RingBuffer__SetTxCB(t_UART_RingBuffer__Cb cb_func)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);

    UART_7_CB__Tx = cb_func;

    return RET_OK;
}

et_RET UART_7_RingBuffer__SetRxCB(t_UART_RingBuffer__Cb cb_func)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);

    UART_7_CB__Rx = cb_func;

    return RET_OK;
}

t_FLAG UART_7_RingBuffer__GetTxFlag(void)
{
    t_FLAG f_aux_tx = FLAG_OFF;
    
    f_aux_tx = f_TX;
    f_TX     = FLAG_OFF;
    
    return f_aux_tx;
}

t_FLAG UART_7_RingBuffer__GetRxFlag(void)
{
    t_FLAG f_aux_rx = FLAG_OFF;
    
    f_aux_rx = f_RX;
    f_RX     = FLAG_OFF;
    
    return f_aux_rx;
}

size_t UART_7_RingBuffer__GetRxRemainSize(void)
{
    #if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     || \
         (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  || \
         (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))  )

        return (g_rx_get_idx <= g_rx_set_idx) ? \
               (g_rx_set_idx - g_rx_get_idx)  : \
               ((RX_BUFFER_SIZE - g_rx_get_idx) + g_rx_set_idx);
    
    #else
        
        return g_rx_total;
        
    #endif
}

size_t UART_7_RingBuffer__GetTxRemainSize(void)
{
    #if ((defined(__CENTI_CODE_CONFIGURATOR_MCC__))     || \
         (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))  || \
         (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))  )

        return (g_tx_get_idx <= g_tx_set_idx) ? \
               (g_tx_set_idx - g_tx_get_idx)  : \
               ((TX_BUFFER_SIZE - g_tx_get_idx) + g_tx_set_idx);
        
    #else
        
        return 0;
        
    #endif
}

void UART_1_RingBuffer__ClearRxFIFO(void)
{
    g_rx_set_idx = 0;
    g_rx_get_idx = 0;
    f_RX         = FLAG_OFF;
}

void UART_1_RingBuffer__ClearTxFIFO(void)
{
    g_tx_set_idx = 0;
    g_tx_get_idx = 0;
    f_TX         = FLAG_OFF;
}


/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

    static void UART_7_ISR__Rx(SERCOM_USART_EVENT event, uintptr_t context)

#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

   static void UART_7_ISR__Rx(struct UARTDRV_HandleData *   handle,
                              Ecode_t                       transferStatus,
                              uint8_t *                     data,
                              UARTDRV_Count_t               transferCount)

#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)

#else

    static void UART_7_ISR__Rx(void)

#endif
{
    #if (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        (void) handle;
        (void) data;
        if (transferStatus == ECODE_EMDRV_UARTDRV_OK)
        {
            g_rx_total += transferCount;
        }
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        /* Call default ISR manager. */
        UART7_Receive_ISR();
        /* Add data to FIFO. */
        RX_FIFO_Add(UART7_Read());
        /* Flag. */
        f_RX = FLAG_ON;
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
        
        /* Add data to FIFO. */
        RX_FIFO_Add(UART7_Read());
        /* Flag. */
        f_RX = FLAG_ON;
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        /* Add data to FIFO. */
        RX_FIFO_Add(g_rx_byte);

        HAL_UART_Receive_IT(&huart7, &g_rx_byte, 1);

        /* Flag. */
        f_RX = FLAG_ON;

    #else

        f_RX = FLAG_ON;

    #endif

    if (UART_7_CB__Rx != NULL)
    {
        UART_7_CB__Rx();
    }
}

#if (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

    static void UART_7_ISR__Tx(SERCOM_USART_EVENT event, uintptr_t context)
    
#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

    static void UART_7_ISR__Tx(struct UARTDRV_HandleData *   handle,
                               Ecode_t                       transferStatus,
                               uint8_t *                     data,
                               UARTDRV_Count_t               transferCount)

#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

    void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)

#else

    static void UART_7_ISR__Tx(void)

#endif
{
    #if (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        (void) handle;
        (void) transferStatus;
        (void) data;
        (void) transferCount;

        f_TX = FLAG_ON;

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        uint8_t tx_data = 0;
        
        /* Call default ISR manager. */
        UART7_Transmit_ISR();
        
        while (UART_7_RingBuffer__GetTxRemainSize() > 0)
        {
            TX_FIFO_Get(tx_data);
            UART7_Write(tx_data);
        }
        
        f_TX = FLAG_ON;
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
        
        uint8_t tx_data = 0;
        
        while (UART_7_RingBuffer__GetTxRemainSize() > 0)
        {
            TX_FIFO_Get(tx_data);
            UART7_Write(tx_data);
        }
        
        f_TX = FLAG_ON;
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        uint8_t tx_byte = 0;

        while (UART_7_RingBuffer__GetTxRemainSize() > 0)
        {
            TX_FIFO_Get(tx_byte);
            HAL_UART_Transmit(&huart7, &tx_byte, 1, UART7_TIMEOUT_TICK);
        }
        /* Flag. */
        f_RX = FLAG_ON;

    #else

        f_TX = FLAG_ON;

    #endif

    if (UART_7_CB__Tx != NULL)
    {
        UART_7_CB__Tx();
    }
}


#endif /* (defined(__CENTI_UART_7_RINGBUFFER__)) */

/* -- End of file -- */
