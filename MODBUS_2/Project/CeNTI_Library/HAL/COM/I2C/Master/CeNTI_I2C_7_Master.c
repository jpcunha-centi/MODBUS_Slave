/* 
 * Path:   Project/HAL/COM/I2C/Master
 * File:   CeNTI_I2C_7_Master.c
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../../../Defines/CeNTI_COM_defines.h"
#if (defined(__CENTI_I2C_7_MASTER__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_I2C_7_Master.h"
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    #include "driver_init.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))
    #include "../../../../../../config/default/peripheral/sercom/i2c_master/plib_sercom7_i2c_master.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    #include "../../../../../../mcc_generated_files/i2c7_master.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
    #include "../../../../../../mcc_generated_files/i2c_host/i2c7.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    #include "i2c.h"
#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))
    #include "sl_i2cspm_instances.h"
    #if (defined(SL_I2CSPM_CENTI_I2C_7_PRESENT))
        #include "sl_i2cspm_centi_i2c_7_config.h"
        #if (SL_I2CSPM_CENTI_I2C_7_PERIPHERAL_NO != 0)
            #error centi_i2c_7 instance is not using I2C7 peripheral!
        #else
            #if SL_I2CSPM_CENTI_I2C_7_SPEED_MODE == 0
                #define SL_I2CSPM_CENTI_I2C_7_HLR i2cClockHLRStandard
                #define SL_I2CSPM_CENTI_I2C_7_MAX_FREQ I2C_FREQ_STANDARD_MAX
            #elif SL_I2CSPM_CENTI_I2C_7_SPEED_MODE == 1
                #define SL_I2CSPM_CENTI_I2C_7_HLR i2cClockHLRAsymetric
                #define SL_I2CSPM_CENTI_I2C_7_MAX_FREQ I2C_FREQ_FAST_MAX
            #elif SL_I2CSPM_CENTI_I2C_7_SPEED_MODE == 2
                #define SL_I2CSPM_CENTI_I2C_7_HLR i2cClockHLRFast
                #define SL_I2CSPM_CENTI_I2C_7_MAX_FREQ I2C_FREQ_FASTPLUS_MAX
            #endif
        #endif
    #else
      #error Rename your I2C instance to centi_i2c_7!
    #endif
#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))
    #include <zephyr/drivers/i2c.h>
#else
    #error I2C_7_Master does not support the CODE_CONFIGURATOR selected!
#endif


/* ************************************************************************************ */
/* * Checks                                                                           * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
    #if (CENTI_ENABLE_INTERRUPTS == CENTI_DISABLE)
        #error I2C_7_Master needs to be configured with interrupts enabled!
    #endif
#endif


/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

	#define I2C7_MASTER_TIMEOUT_TICK		(1000)

#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

    #define I2C7_NODE DT_NODELABEL(centi_i2c_7)

#endif 


/* ************************************************************************************ */
/* * Structures                                                                       * */
/* ************************************************************************************ */
/* Structure with a data vector and its size. */
#if (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

    typedef struct _struct_i2c_buffer {
        uint8_t * data_vec;
        size_t    data_vec_size;
    } st_I2C_buffer;        

#endif


/* ************************************************************************************ */
/* * Global variables                                                                 * */
/* ************************************************************************************ */
/* Indication if initialization procedure was successful. */
static bool g_initialized = false;

/* IO structure. */
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

    static struct io_descriptor * g_st_io_ptr;
    
#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

    static const struct i2c_dt_spec ST_DT_SPEC_I2C7 = I2C_DT_SPEC_GET(I2C7_NODE)

#endif


/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

    /*
     * @brief Function used to handle an I2C nack.
     * 
     * @param[out] ret_ptr Error value.
     * 
     * @return i2c7_operations_t.
     */
    static i2c7_operations_t I2C_7_Master_ISR__Nack(void *ret_ptr);

    /*
     * @brief Function used during a WriteRead process. After the write process, this
     *          function is used to charge the read variables and prepare I2C to perform
     *          a read process.
     * 
     * @param[in] ptr   Pointer to a st_I2C_buffer structure with all the variables
     *                  needed to perform a read.
     * 
     * @return i2c7_operation_t.
     */
    static i2c7_operations_t I2C_7_Master_Handler__WriteRead(void * ptr);

    /*
     * @brief Function used during a DoubleWrite process. After the first write process,
     *          this function is used to charge the next write variables and prepare I2C
     *          to perform a write process again.
     * 
     * @param[in] ptr   Pointer to a st_I2C_buffer structure with all the variables
     *                  needed to perform a write again.
     * 
     * @return i2c7_operation_t.
     */
    static i2c7_operations_t I2C_7_Master_Handler__DoubleWrite(void * ptr);

#endif


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET I2C_7_Master__Initialize(void)
{
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        et_RET   et_ret  = RET_UNEXPECTED;
        uint32_t i2c_ret = 0;

        /* Initialize I2C7. */
        I2C_7_init();

        /* Get I2C7 io descriptor. */
        i2c_ret |= i2c_m_sync_get_io_descriptor(&I2C_7, g_st_io_ptr);
        /* Enable I2C7. */
        i2c_ret |= i2c_m_sync_enable(&I2C_7);

        et_ret = (i2c_ret) ? RET_COM_I2C_FAIL : RET_OK;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        et_RET et_ret = RET_UNEXPECTED;
        
        /* Initialize I2C7. */
        SERCOM7_I2C_Initialize();
        
        et_ret = (SERCOM_I2C_ERROR_NONE == SERCOM7_I2C_ErrorGet()) ? RET_OK : \
                                                                     RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        /* Initialize I2C7. */
        I2C7_Initialize();

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        et_RET           et_ret  = RET_UNEXPECTED;
        i2c_host_error_t i2c_ret = I2C_ERROR_NONE;
        
        /* Initialize I2C7. */
        I2C7_Initialize();
        /* Check errors. */
        i2c_ret = I2C7_ErrorGet();
        et_ret  = (i2c_ret == I2C_ERROR_ADDR_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_DATA_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_BUS_COLLISION)  ? RET_BUSY          : \
                  (i2c_ret == I2C_ERROR_NONE)           ? RET_OK            : \
                                                          RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);

        while (I2C7_IsBusy()) {}
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        /* Initialize I2C7. */
        MX_I2C1_Init();

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        I2CSPM_Init_TypeDef init_centi_i2c_7 =
        {
          .port         = SL_I2CSPM_CENTI_I2C_7_PERIPHERAL,
          .sclPort      = SL_I2CSPM_CENTI_I2C_7_SCL_PORT,
          .sclPin       = SL_I2CSPM_CENTI_I2C_7_SCL_PIN,
          .sdaPort      = SL_I2CSPM_CENTI_I2C_7_SDA_PORT,
          .sdaPin       = SL_I2CSPM_CENTI_I2C_7_SDA_PIN,
          .i2cRefFreq   = SL_I2CSPM_CENTI_I2C_7_REFERENCE_CLOCK,
          .i2cMaxFreq   = SL_I2CSPM_CENTI_I2C_7_MAX_FREQ,
          .i2cClhr      = SL_I2CSPM_CENTI_I2C_7_HLR
        };

        I2CSPM_Init(&init_centi_i2c_7);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

        et_RET et_ret      = RET_UNEXPECTED;
        bool   i2c_dev_rdy = false;

        i2c_dev_rdy = device_is_ready(ST_DT_SPEC_I2C7.bus);

        et_ret = (i2c_dev_rdy) ? RET_OK : RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);

    #else

        #error Function not supported by the current CODE_CONFIGURATOR!

    #endif
    
    g_initialized = true;

    return RET_INITIALIZED;
}

et_RET I2C_7_Master__Write(uint8_t   i2c_address,\
                           uint8_t * tx_vec,\
                           size_t    tx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    
        /* Set slave address. */
        i2c_m_sync_set_slaveaddr(&I2C_7, i2c_address, I2C_M_SEVEN);
        /* Write function. */
        io_write(g_st_io_ptr, &(tx_vec[0]), tx_vec_size);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        et_RET et_ret = RET_UNEXPECTED;

        /* Write function. */
        SERCOM7_I2C_Write((uint16_t)i2c_address, &(tx_vec[0]), (uint32_t)tx_vec_size);
        /* Wait while transmission is not complete. */
        while (SERCOM7_I2C_IsBusy()) {}
        
        et_ret = (SERCOM_I2C_ERROR_NONE == SERCOM7_I2C_ErrorGet()) ? RET_OK \
                                                                   : RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
        et_RET et_ret = RET_UNEXPECTED;

        /* Indicate that everything is ok. */
        et_ret = RET_OK;
        
        /* Wait here until I2C 7 is open. */
        while (!I2C7_Open(i2c_address)) {}
        
        /* Set callback function for an address nack. */
        I2C7_SetAddressNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for a data nack. */
        I2C7_SetDataNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for when data transmission is complete. */
        I2C7_SetDataCompleteCallback(NULL, NULL);
        /* Set buffer with data and size. */
        I2C7_SetBuffer(&(tx_vec[0]), tx_vec_size);
        /* Write function. */
        I2C7_MasterWrite();
        
        /* Wait here until I2C 7 is not closed. */
        while (I2C7_BUSY == I2C7_Close()) {}
        
        CENTI_CHECK_RET(et_ret);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        et_RET           et_ret  = RET_UNEXPECTED;
        i2c_host_error_t i2c_ret = I2C_ERROR_NONE;
        
        /* Write function. */
        I2C7_Write((uint16_t)i2c_address, &(tx_vec[0]), tx_vec_size);
        /* Check errors. */
        i2c_ret = I2C7_ErrorGet();
        et_ret  = (i2c_ret == I2C_ERROR_ADDR_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_DATA_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_BUS_COLLISION)  ? RET_BUSY          : \
                  (i2c_ret == I2C_ERROR_NONE)           ? RET_OK            : \
                                                          RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);
        /* Wait while transmission is not complete. */
        while (I2C7_IsBusy()) {}
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        et_RET            et_ret     = RET_UNEXPECTED;
        HAL_StatusTypeDef hal_status = HAL_OK;

        /* Write function. */
        hal_status = HAL_I2C_Master_Transmit(&hi2c7,\
                                             (uint16_t)(i2c_address<<1),\
                                             &(tx_vec[0]),\
                                             tx_vec_size,\
                                             I2C7_MASTER_TIMEOUT_TICK);
        /* Check errors. */
        et_ret = (hal_status == HAL_OK)      ? RET_OK           : \
                 (hal_status == HAL_ERROR)   ? RET_COM_I2C_FAIL : \
                 (hal_status == HAL_TIMEOUT) ? RET_TIMEOUT      : \
                 (hal_status == HAL_BUSY)    ? RET_BUSY         : \
                                               RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        et_RET                      et_ret       = RET_UNEXPECTED;
        I2C_TransferSeq_TypeDef     transfer_seq;
        I2C_TransferReturn_TypeDef  transfer_ret;

        transfer_seq.addr = ( ( (uint16_t) (i2c_address << 1) ) );
        transfer_seq.flags = I2C_FLAG_WRITE;

        transfer_seq.buf[0].data = &(tx_vec[0]);
        transfer_seq.buf[0].len = (uint16_t) tx_vec_size;

        /* No data returned */
        transfer_seq.buf[1].data = NULL;
        transfer_seq.buf[1].len = 0;

        transfer_ret = I2CSPM_Transfer(SL_I2CSPM_CENTI_I2C_7_PERIPHERAL, &transfer_seq);

        et_ret =  (transfer_ret == i2cTransferDone) ? RET_OK             : \
                  (transfer_ret == i2cTransferNack) ? RET_COM_I2C_NACK   : \
                                                      RET_COM_I2C_FAIL;

        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

        et_RET et_ret  = RET_UNEXPECTED;
        int    i2c_ret = 0;

        if (i2c_address == ST_DT_SPEC_I2C7.addr)
        {
            i2c_ret = i2c_write_dt(&ST_DT_SPEC_I2C7,\
                                   &(tx_vec[0]), (uint32_t)tx_vec_size);
            et_ret = (i2c_ret == 0) ? RET_OK : RET_COM_I2C_FAIL;
            CENTI_CHECK_RET(et_ret);
        }

    #else
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #endif /* (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__)) */
    
    return RET_OK;
}

et_RET I2C_7_Master__Read(uint8_t   i2c_address,\
                          uint8_t * rx_vec,\
                          size_t    rx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    
        /* Set slave address. */
        i2c_m_sync_set_slaveaddr(&I2C_7, i2c_address, I2C_M_SEVEN);
        /* Read function. */
        io_read(g_st_io_ptr, &(rx_vec[0]), rx_vec_size);
                                
    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        et_RET et_ret = RET_UNEXPECTED;

        /* Read function. */
        SERCOM7_I2C_Read((uint16_t)i2c_address, &(rx_vec[0]), (uint32_t)rx_vec_size);
        /* Wait while reception is not complete. */
        while (SERCOM7_I2C_IsBusy()) {}
        
        et_ret = (SERCOM_I2C_ERROR_NONE == SERCOM7_I2C_ErrorGet()) ? RET_OK : \
                                                                     RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
        et_RET et_ret = RET_UNEXPECTED;

        /* Indicate that everything is ok. */
        et_ret = RET_OK;
        
        /* Wait here until I2C 7 is open. */
        while (!I2C7_Open(i2c_address)) {}
        
        /* Set callback function for an address nack. */
        I2C7_SetAddressNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for a data nack. */
        I2C7_SetDataNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for when data reception is complete. */
        I2C7_SetDataCompleteCallback(NULL, NULL);
        /* Set buffer with data and size. */
        I2C7_SetBuffer(&(rx_vec[0]), rx_vec_size);
        /* Read function. */
        I2C7_MasterRead();
        
        /* Wait here until I2C 7 is not closed. */
        while (I2C7_BUSY == I2C7_Close()) {}
        
        CENTI_CHECK_RET(et_ret);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        et_RET           et_ret  = RET_UNEXPECTED;
        i2c_host_error_t i2c_ret = I2C_ERROR_NONE;
        
        /* Read function. */
        I2C7_Read((uint16_t)i2c_address, &(rx_vec[0]), rx_vec_size);
        /* Check errors. */
        i2c_ret = I2C7_ErrorGet();
        et_ret  = (i2c_ret == I2C_ERROR_ADDR_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_DATA_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_BUS_COLLISION)  ? RET_BUSY          : \
                  (i2c_ret == I2C_ERROR_NONE)           ? RET_OK            : \
                                                          RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);
        /* Wait while reception is not complete. */
        while (I2C7_IsBusy()) {}

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

        et_RET            et_ret     = RET_UNEXPECTED;
        HAL_StatusTypeDef hal_status = HAL_OK;

        /* Read function. */
        hal_status = HAL_I2C_Master_Receive(&hi2c7,\
                                            (uint16_t)(i2c_address<<1),\
                                            &(rx_vec[0]),\
                                            rx_vec_size,\
                                            I2C7_MASTER_TIMEOUT_TICK);
        /* Check errors. */
        et_ret = (hal_status == HAL_OK)      ? RET_OK           : \
                 (hal_status == HAL_ERROR)   ? RET_COM_I2C_FAIL : \
                 (hal_status == HAL_TIMEOUT) ? RET_TIMEOUT      : \
                 (hal_status == HAL_BUSY)    ? RET_BUSY         : \
                                               RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);
         
    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        et_RET                     et_ret       = RET_UNEXPECTED;
        I2C_TransferSeq_TypeDef    transfer_seq;
        I2C_TransferReturn_TypeDef transfer_ret;

        transfer_seq.addr = ( ( (uint16_t) (i2c_address << 1) ) );
        transfer_seq.flags = I2C_FLAG_READ;

        transfer_seq.buf[0].data = &(rx_vec[0]);
        transfer_seq.buf[0].len  = (uint16_t) rx_vec_size;

        /* No data to return */
        transfer_seq.buf[1].data = NULL;
        transfer_seq.buf[1].len  = 0;

        transfer_ret = I2CSPM_Transfer(SL_I2CSPM_CENTI_I2C_7_PERIPHERAL, &transfer_seq);

        et_ret =  (transfer_ret == i2cTransferDone) ? RET_OK            : \
                  (transfer_ret == i2cTransferNack) ? RET_COM_I2C_NACK  : \
                                                      RET_COM_I2C_FAIL;

        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

        et_RET et_ret  = RET_UNEXPECTED;
        int    i2c_ret = 0;

        if (i2c_address == ST_DT_SPEC_I2C7.addr)
        {
            i2c_ret = i2c_read_dt(&ST_DT_SPEC_I2C7,\
                                  &(rx_vec[0]), (uint32_t)rx_vec_size);
            et_ret = (i2c_ret == 0) ? RET_OK : RET_COM_I2C_FAIL;
            CENTI_CHECK_RET(et_ret);
        }

    #else
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #endif /* (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__)) */
    
    return RET_OK;
}

et_RET I2C_7_Master__WriteRead(uint8_t   i2c_address,\
                               uint8_t * tx_vec,\
                               size_t    tx_vec_size,\
                               uint8_t * rx_vec,\
                               size_t    rx_vec_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    
    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

        et_RET et_ret = RET_UNEXPECTED;

        /* Write/Read function. */
        SERCOM7_I2C_WriteRead((uint16_t)i2c_address,\
                              &(tx_vec[0]), (uint32_t)tx_vec_size,\
                              &(rx_vec[0]), (uint32_t)rx_vec_size);
        /* Wait while transmission/reception is not complete. */
        while (SERCOM7_I2C_IsBusy()) {}
        
        et_ret = (SERCOM_I2C_ERROR_NONE == SERCOM7_I2C_ErrorGet()) ? RET_OK : \
                                                                     RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
        et_RET        et_ret        = RET_UNEXPECTED;
        st_I2C_buffer st_i2c_buffer = {};
        
        /* Load st_i2c_buffer with a vector to receive data. */
        st_i2c_buffer.data_vec      = rx_vec;
        st_i2c_buffer.data_vec_size = rx_vec_size;
        
        /* Indicate that everything is ok. */
        et_ret = RET_OK;
        
        /* Wait here until I2C 7 is open. */
        while (!I2C7_Open(i2c_address)) {}
        
        /* Set callback function for an address nack. */
        I2C7_SetAddressNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for a data nack. */
        I2C7_SetDataNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for when data transmission is complete. */
        I2C7_SetDataCompleteCallback(I2C_7_Master_Handler__WriteRead, &st_i2c_buffer);
        /* Set buffer with data and size. */
        I2C7_SetBuffer(&(tx_vec[0]), tx_vec_size);
        /* Write function. */
        I2C7_MasterWrite();
        
        /* Wait here until I2C 7 is not closed. */
        while (I2C7_BUSY == I2C7_Close()) {}

        CENTI_CHECK_RET(et_ret);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        et_RET           et_ret  = RET_UNEXPECTED;
        i2c_host_error_t i2c_ret = I2C_ERROR_NONE;
        
        /* Write/Read function. */
        I2C7_WriteRead((uint16_t)i2c_address,\
                       &(tx_vec[0]), tx_vec_size,\
                       &(rx_vec[0]), rx_vec_size);
        /* Check errors. */
        i2c_ret = I2C7_ErrorGet();
        et_ret  = (i2c_ret == I2C_ERROR_ADDR_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_DATA_NACK)      ? RET_COM_I2C_NACK  : \
                  (i2c_ret == I2C_ERROR_BUS_COLLISION)  ? RET_BUSY          : \
                  (i2c_ret == I2C_ERROR_NONE)           ? RET_OK            : \
                                                          RET_COM_I2C_FAIL;
        CENTI_CHECK_RET(et_ret);
        /* Wait while reception is not complete. */
        while (I2C7_IsBusy()) {}

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        et_RET                     et_ret       = RET_UNEXPECTED;
        I2C_TransferSeq_TypeDef    transfer_seq;
        I2C_TransferReturn_TypeDef transfer_ret;

        transfer_seq.addr  = ( ( (uint16_t) (i2c_address << 1) ) );
        transfer_seq.flags = I2C_FLAG_WRITE_READ;

        transfer_seq.buf[0].data = &(tx_vec[0]);
        transfer_seq.buf[0].len  = (uint16_t) tx_vec_size;

        transfer_seq.buf[1].data = &(rx_vec[0]);
        transfer_seq.buf[1].len  = (uint16_t) rx_vec_size;

        transfer_ret = I2CSPM_Transfer(SL_I2CSPM_CENTI_I2C_7_PERIPHERAL, &transfer_seq);

        et_ret =  (transfer_ret == i2cTransferDone) ? RET_OK            : \
                  (transfer_ret == i2cTransferNack) ? RET_COM_I2C_NACK  : \
                                                      RET_COM_I2C_FAIL;

        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

        et_RET et_ret  = RET_UNEXPECTED;
        int    i2c_ret = 0;

        if (i2c_address == ST_DT_SPEC_I2C7.addr)
        {
            i2c_ret = i2c_write_read_dt(&ST_DT_SPEC_I2C7,\
                                        &(tx_vec[0]), (uint32_t)tx_vec_size,\
                                        &(rx_vec[0]), (uint32_t)rx_vec_size);
            et_ret = (i2c_ret == 0) ? RET_OK : RET_COM_I2C_FAIL;
            CENTI_CHECK_RET(et_ret);
        }

    #else
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #endif /* (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__)) */
    
    return RET_OK;
}

et_RET I2C_7_Master__DoubleWrite(uint8_t   i2c_address,\
                                 uint8_t * tx_vec_1,\
                                 size_t    tx_vec_1_size,\
                                 uint8_t * tx_vec_2,\
                                 size_t    tx_vec_2_size)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);

    #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
        et_RET        et_ret        = RET_UNEXPECTED;
        st_I2C_buffer st_i2c_buffer = {};
        
        /* Load st_i2c_buffer with a vector to receive data. */
        st_i2c_buffer.data_vec      = tx_vec_2;
        st_i2c_buffer.data_vec_size = tx_vec_2_size;
        
        /* Indicate that everything is ok. */
        et_ret = RET_OK;
        
        /* Wait here until I2C 7 is open. */
        while (!I2C7_Open(i2c_address)) {}
        
        /* Set callback function for an address nack. */
        I2C7_SetAddressNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for a data nack. */
        I2C7_SetDataNackCallback(I2C_7_Master_ISR__Nack, &et_ret);
        /* Set callback function for when data transmission is complete. */
        I2C7_SetDataCompleteCallback(I2C_7_Master_Handler__DoubleWrite, &st_i2c_buffer);
        /* Set buffer with data and size. */
        I2C7_SetBuffer(&(tx_vec_1[0]), tx_vec_1_size);
        /* Write function. */
        I2C7_MasterWrite();
        
        /* Wait here until I2C 7 is not closed. */
        while (I2C7_BUSY == I2C7_Close()) {}
        
        CENTI_CHECK_RET(et_ret);
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

        #warning Function not supported by the current CODE_CONFIGURATOR!

    #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

        et_RET                     et_ret       = RET_UNEXPECTED;
        I2C_TransferSeq_TypeDef    transfer_seq;
        I2C_TransferReturn_TypeDef transfer_ret;

        transfer_seq.addr  = ( ( (uint16_t) (i2c_address << 1) ) );
        transfer_seq.flags = I2C_FLAG_WRITE_WRITE;

        transfer_seq.buf[0].data = &(tx_vec_1[0]);
        transfer_seq.buf[0].len  = (uint16_t) tx_vec_1_size;

        transfer_seq.buf[1].data = &(tx_vec_2[0]);
        transfer_seq.buf[1].len  = (uint16_t) tx_vec_2_size;

        transfer_ret = I2CSPM_Transfer(SL_I2CSPM_CENTI_I2C_7_PERIPHERAL, &transfer_seq);

        et_ret =  (transfer_ret == i2cTransferDone) ? RET_OK            : \
                  (transfer_ret == i2cTransferNack) ? RET_COM_I2C_NACK  : \
                                                      RET_COM_I2C_FAIL;

        CENTI_CHECK_RET(et_ret);

    #elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

        #warning Function not supported by the current CODE_CONFIGURATOR!

    #else
    
        #warning Function not supported by the current CODE_CONFIGURATOR!
        
    #endif

    return RET_OK;
}


/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

    static i2c7_operations_t I2C_7_Master_ISR__Nack(void *ret_ptr)
    {
        et_RET * et_ret_ptr = ((et_RET *)ret_ptr);

        *et_ret_ptr = RET_COM_I2C_FAIL;

        return I2C7_STOP;
    }

    static i2c7_operations_t I2C_7_Master_Handler__WriteRead(void * ptr)
    {
        I2C7_SetBuffer(((st_I2C_buffer *)ptr)->data_vec,\
                       ((st_I2C_buffer *)ptr)->data_vec_size);

        I2C7_SetDataCompleteCallback(NULL, NULL);

        return I2C7_RESTART_READ;
    }

    static i2c7_operations_t I2C_7_Master_Handler__DoubleWrite(void * ptr)
    {
        I2C7_SetBuffer(((st_I2C_buffer *)ptr)->data_vec,\
                       ((st_I2C_buffer *)ptr)->data_vec_size);

        I2C7_SetDataCompleteCallback(NULL, NULL);

        return I2C7_RESTART_WRITE;
    }

#endif


#endif /* (defined(__CENTI_I2C_7_MASTER__)) */

/* -- End of file -- */
