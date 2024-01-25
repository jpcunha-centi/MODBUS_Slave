/* 
 * Path:   Project/HAL/COM/SPI/Master/
 * File:   CeNTI_SPI_6_Master.c
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_SPI_6_MASTER__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_SPI_6_Master.h"
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    #include "driver_init.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))
    #include "../../../../../../config/ATSAME54_XPlained/peripheral/sercom/spi_master/plib_sercom6_spi_master.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    #include "../../../../../../mcc_generated_files/spi6_master.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
    #include "../../../../../../mcc_generated_files/spi/spi6.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    #include "spi.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))
    #include "sl_spidrv_instances.h"
    #include "sl_spidrv_centi_spi_6_config.h"
#else
    #error SPI_6_Master does not support the CODE_CONFIGURATOR selected!
#endif


/* ************************************************************************************ */
/* * Defines                                                                         * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
	#define SPI6_MASTER_TIMEOUT_TICK		(HAL_MAX_DELAY)
#endif


/* ************************************************************************************ */
/* * Global variables                                                                 * */
/* ************************************************************************************ */
/* Indication if initialization procedure was successful. */
static bool g_initialized = false;

/* IO structure. */
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    static struct io_descriptor * g_st_io_ptr;
#endif


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET SPI_6_Master__Initialize(void)
{
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        et_RET   et_ret  = RET_UNEXPECTED;
        uint32_t spi_ret = 0;

        /* Initialize SPI6. */
        SPI_6_init();

        /* Get SPI6 io descriptor. */
        spi_ret |= spi_m_sync_get_io_descriptor(&SPI_6, g_st_io_ptr);

        /* Enable SPI6. */
        spi_ret |= spi_m_sync_enable(&SPI_6);

        /* Check errors. */
        et_ret (spi_ret) ? RET_COM_SPI_FAIL : RET_OK;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        et_RET et_ret = RET_UNEXPECTED;

        /* Initialize SPI6. */
        SERCOM6_SPI_Initialize();

        /* Check errors. */
        et_ret = (SERCOM_SPI_ERROR_NONE == SERCOM6_SPI_ErrorGet()) ? RET_OK : \
                                                                     RET_COM_SPI_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        /* Inititalize SPI6. */
        SPI6_Initialize();

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        /* Initialize SPI6. */
        SPI6_Initialize();
        
        SPI6_Open(SPI6_DEFAULT);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        /* Initialize SPI6. */
        MX_SPI6_Init();
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        et_RET  et_ret = RET_UNEXPECTED;
        Ecode_t ecode  = ECODE_EMDRV_SPIDRV_OK;

        SPIDRV_Init_t sl_spidrv_init_centi_spi_6 = {
            .port = SL_SPIDRV_CENTI_SPI_0_PERIPHERAL,
            #if defined(_USART_ROUTELOC6_MASK)
                .portLocationTx  = SL_SPIDRV_CENTI_SPI_6_TX_LOC,
                .portLocationRx  = SL_SPIDRV_CENTI_SPI_6_RX_LOC,
                .portLocationClk = SL_SPIDRV_CENTI_SPI_6_CLK_LOC,
                #if defined(SL_SPIDRV_CENTI_SPI_6_CS_LOC)
                    .portLocationCs = SL_SPIDRV_CENTI_SPI_6_CS_LOC,
                #endif
            #elif defined(_GPIO_USART_ROUTEEN_MASK)
                .portTx  = SL_SPIDRV_CENTI_SPI_6_TX_PORT,
                .portRx  = SL_SPIDRV_CENTI_SPI_6_RX_PORT,
                .portClk = SL_SPIDRV_CENTI_SPI_6_CLK_PORT,
                #if defined(SL_SPIDRV_CENTI_SPI_6_CS_PORT)
                    .portCs = SL_SPIDRV_CENTI_SPI_6_CS_PORT,
                #endif
                .pinTx  = SL_SPIDRV_CENTI_SPI_6_TX_PIN,
                .pinRx  = SL_SPIDRV_CENTI_SPI_6_RX_PIN,
                .pinClk = SL_SPIDRV_CENTI_SPI_6_CLK_PIN,
                #if defined(SL_SPIDRV_CENTI_SPI_6_CS_PIN)
                    .pinCs = SL_SPIDRV_CENTI_SPI_6_CS_PIN,
                #endif
            #else
                .portLocation = SL_SPIDRV_CENTI_SPI_6_ROUTE_LOC,
            #endif
            .bitRate        = SL_SPIDRV_CENTI_SPI_6_BITRATE,
            .frameLength    = SL_SPIDRV_CENTI_SPI_6_FRAME_LENGTH,
            .dummyTxValue   = 0,
            .type           = SL_SPIDRV_CENTI_SPI_6_TYPE,
            .bitOrder       = SL_SPIDRV_CENTI_SPI_6_BIT_ORDER,
            .clockMode      = SL_SPIDRV_CENTI_SPI_6_CLOCK_MODE,
            .csControl      = SL_SPIDRV_CENTI_SPI_6_CS_CONTROL,
            .slaveStartMode = SL_SPIDRV_CENTI_SPI_6_SLAVE_START_MODE,
        };

        ecode = SPIDRV_Init(sl_spidrv_centi_spi_6_handle, &sl_spidrv_init_centi_spi_6);

        et_ret = (ecode == ECODE_EMDRV_SPIDRV_OK)             ? RET_OK                : \
                 (ecode == ECODE_EMDRV_DMADRV_PARAM_ERROR)    ? RET_INVALID_PARAMETER : \
                 (ecode == ECODE_EMDRV_SPIDRV_ILLEGAL_HANDLE) ? RET_NULL_POINTER      : \
                                                                RET_COM_SPI_FAIL;

        CENTI_CHECK_RET(et_ret);

    #else

        #error Function not supported by the current CODE_CONFIGURATOR!

    #endif

    g_initialized = true;

    return RET_OK;
}

et_RET SPI_6_Master__Write(uint8_t * tx_vec,\
                           size_t    tx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);

    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        /* Write function. */
        io_write(g_st_io_ptr, &(tx_vec[0]), tx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        et_RET et_ret = RET_UNEXPECTED;

        /* Write function. */
        SERCOM6_SPI_Write((uint16_t)i2c_address, &(tx_vec[0]), (uint32_t)tx_vec_size);

        /* Wait while transmission is not complete. */
        while(SERCOM6_SPI_IsBusy()) {}

        /* Check errors. */
        et_ret = (SERCOM_SPI_ERROR_NONE == SERCOM6_SPI_ErrorGet()) ? RET_OK : \
                                                                     RET_COM_SPI_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        /* Write function. */
        SPI6_WriteBlock(&(tx_vec[0]), tx_vc_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        /* Write function. */
        SPI6_BufferWrite(&(tx_vec[0]), tx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        et_RET            et_ret     = RET_UNEXPECTED;
        HAL_StatusTypeDef hal_status = HAL_OK;

        /* Write function. */
        hal_status = HAL_SPI_Transmit(&hspi6,\
                                      &(tx_vec[0]),\
                                      (uint16_t)tx_vec_size,\
                                      (uint32_t)SPI6_MASTER_TIMEOUT_TICK);

        /* Check errors. */
        et_ret = (hal_status == HAL_OK)      ? RET_OK           : \
                 (hal_status == HAL_ERROR)   ? RET_COM_SPI_FAIL : \
                 (hal_status == HAL_TIMEOUT) ? RET_TIMEOUT      : \
                 (hal_status == HAL_BUSY)    ? RET_BUSY         : \
                                               RET_COM_SPI_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        Ecode_t ecode  = SL_STATUS_OK;
        et_RET  et_ret = RET_UNEXPECTED;

        ecode = SPIDRV_MTransmitB(sl_spidrv_centi_spi_6_handle,
                                  (void *) &(tx_vec[0]),
                                  tx_vec_size);

        et_ret =  (ecode == ECODE_EMDRV_SPIDRV_OK)             ? RET_OK                : \
                  (ecode == ECODE_EMDRV_SPIDRV_BUSY)           ? RET_BUSY              : \
                  (ecode == ECODE_EMDRV_SPIDRV_PARAM_ERROR)    ? RET_INVALID_PARAMETER : \
                  (ecode == ECODE_EMDRV_SPIDRV_ILLEGAL_HANDLE) ? RET_NULL_POINTER      : \
                  (ecode == ECODE_EMDRV_SPIDRV_ABORTED)        ? RET_TIMEOUT           : \
                                                                 RET_COM_SPI_FAIL;

        CENTI_CHECK_RET(et_ret);

    #else
    
        #error Function not supported by the current CODE_CONFIGURATOR!

    #endif
    
    return RET_OK;
}

et_RET SPI_6_Master__Read(uint8_t * rx_vec,\
                          size_t    rx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);

    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        /* Read function. */
        io_read(g_st_io_ptr, &(rx_vec[0]), rx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        bool spi_ret = false;
        
        /* Read function. */
        SERCOM6_SPI_Read((void *)&(rx_vec[0]), rx_vec_size);

        /* Wait while exchange is not complete. */
        while (SERCOM6_SPI_IsBusy()) {}

        /* Check errors. */
        et_ret = (SERCOM_SPI_ERROR_NONE == SERCOM6_SPI_ErrorGet()) ? RET_OK : \
                                                                     RET_COM_SPI_FAIL;
        CENTI_CHECK_RET(et_ret);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        /* Read function. */
        SPI6_ReadBlock(&(rx_vec[0]), rx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        /* Read function. */
        SPI6_BufferRead(&(rx_vec[0]), rx_vec_size);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        et_RET            et_ret     = RET_UNEXPECTED;
        HAL_StatusTypeDef hal_status = HAL_OK;

        /* Read function. */
        hal_status = HAL_SPI_Receive(&hspi6,\
                                     &(rx_vec[0]),\
                                     (uint16_t)rx_vec_size,\
                                     (uint32_t)SPI6_MASTER_TIMEOUT_TICK);

        /* Check errors. */
        et_ret = (hal_status == HAL_OK)      ? RET_OK           : \
                 (hal_status == HAL_ERROR)   ? RET_COM_SPI_FAIL : \
                 (hal_status == HAL_TIMEOUT) ? RET_TIMEOUT      : \
                 (hal_status == HAL_BUSY)    ? RET_BUSY         : \
                                               RET_COM_SPI_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        Ecode_t ecode  = SL_STATUS_OK;
        et_RET  et_ret = RET_UNEXPECTED;

        ecode = SPIDRV_MReceiveB(sl_spidrv_centi_spi_6_handle,
                                 (void *) &(rx_vec[0]),
                                 rx_vec_size);

        et_ret =  (ecode == ECODE_EMDRV_SPIDRV_OK)             ? RET_OK                : \
                  (ecode == ECODE_EMDRV_SPIDRV_BUSY)           ? RET_BUSY              : \
                  (ecode == ECODE_EMDRV_SPIDRV_PARAM_ERROR)    ? RET_INVALID_PARAMETER : \
                  (ecode == ECODE_EMDRV_SPIDRV_ILLEGAL_HANDLE) ? RET_NULL_POINTER      : \
                  (ecode == ECODE_EMDRV_SPIDRV_ABORTED)        ? RET_TIMEOUT           : \
                                                                 RET_COM_SPI_FAIL;

        CENTI_CHECK_RET(et_ret);

    #else

        #error Function not supported by the current CODE_CONFIGURATOR!

    #endif
    
    return RET_OK;
}

et_RET SPI_6_Master__Exchange(uint8_t * tx_vec,\
                              size_t    tx_vec_size,\
                              uint8_t * rx_vec,\
                              size_t    rx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);

    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        #error Function not supported by the current CODE_CONFIGURATOR!

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        et_RET et_ret  = RET_UNEXPECTED;
        bool   spi_ret = false;
        
        /* Exchange function. */
        SERCOM6_SPI_WriteRead((void *)&(tx_vec[0]), tx_vec_size,\
                              (void *)&(rx_vec[0]), rx_vec_size);

        /* Wait while exchange is not complete. */
        while (SERCOM6_SPI_IsBusy()) {}

        /* Check errors. */
        et_ret = (SERCOM_SPI_ERROR_NONE == SERCOM6_SPI_ErrorGet()) ? RET_OK : \
                                                                     RET_COM_SPI_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        #error Function not supported by the current CODE_CONFIGURATOR!

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        #warning Function not supported by the current CODE_CONFIGURATOR!

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        et_RET            et_ret        = RET_UNEXPECTED;
        HAL_StatusTypeDef hal_status    = HAL_OK;
        uint16_t          exchange_size = 0;

        /* Wait for SPI to be ready. */
        while (HAL_SPI_GetState(&hspi6) != HAL_SPI_STATE_READY) {}

        /* Set the right exchange size. */
        exchange_size = (uint16_t)((tx_vec_size < rx_vec_size) ? tx_vec_size \
                                                               : rx_vec_size);

        /* Exchange function. */
        hal_status = HAL_SPI_TransmitReceive(&hspi6,\
                                             &(tx_vec[0]),\
                                             &(rx_vec[0]),\
                                             exchange_size,\
                                             (uint32_t)SPI6_MASTER_TIMEOUT_TICK);

        /* Check errors. */
        et_ret = (hal_status == HAL_OK)      ? RET_OK           : \
                 (hal_status == HAL_ERROR)   ? RET_COM_SPI_FAIL : \
                 (hal_status == HAL_TIMEOUT) ? RET_TIMEOUT      : \
                 (hal_status == HAL_BUSY)    ? RET_BUSY         : \
                                               RET_COM_SPI_FAIL;
        CENTI_CHECK_RET(et_ret);

        /* Wait for SPI t ocomplete. */
        while (HAL_SPI_GetState(&hspi6) == HAL_SPI_STATE_BUSY) {}

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        Ecode_t ecode         = SL_STATUS_OK;
        et_RET  et_ret        = RET_UNEXPECTED;
        int     exchange_size = 0;

        /* Set the right exchange size. */
        exchange_size = (int)((tx_vec_size < rx_vec_size) ? tx_vec_size \
                                                          : rx_vec_size);

        ecode = SPIDRV_MTransferB(sl_spidrv_centi_spi_6_handle,
                                  (void *) &tx_vec[0],
                                  (void *) &(rx_vec[0]),
                                  exchange_size);

        et_ret =  (ecode == ECODE_EMDRV_SPIDRV_OK)             ? RET_OK                : \
                  (ecode == ECODE_EMDRV_SPIDRV_BUSY)           ? RET_BUSY              : \
                  (ecode == ECODE_EMDRV_SPIDRV_PARAM_ERROR)    ? RET_INVALID_PARAMETER : \
                  (ecode == ECODE_EMDRV_SPIDRV_ILLEGAL_HANDLE) ? RET_NULL_POINTER      : \
                  (ecode == ECODE_EMDRV_SPIDRV_ABORTED)        ? RET_TIMEOUT           : \
                                                                 RET_COM_SPI_FAIL;

        CENTI_CHECK_RET(et_ret);

    #else

        #error Function not supported by the current CODE_CONFIGURATOR!

    #endif
    
    return RET_OK;
}


#endif /* (defined(__CENTI_SPI_6_MASTER__)) */

/* -- End of file -- */
