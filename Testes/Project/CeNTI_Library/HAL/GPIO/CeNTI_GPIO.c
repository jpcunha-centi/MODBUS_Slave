/* 
 * Path:    Project/HAL/GPIO/
 * File:    CeNTI_GPIO.c
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_GPIO_defines.h"
#if (defined(__CENTI_GPIO__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_GPIO.h"

#if (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

    #include "sl_emlib_gpio_simple_init.h"
    #include "sl_emlib_gpio_init_max_cs_config.h"
    #include "sl_emlib_gpio_init_max_drdy_config.h"
    #include "em_gpio.h"
    #include "em_cmu.h"

#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

    #include <zephyr/drivers/gpio.h>

#endif


/* ************************************************************************************ */
/* * Constant Variables                                                               * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

    /* The devicetree node identifier for the "led0" alias. */
    #define LED0_NODE DT_ALIAS(led0)

    /*
    * A build error on this line means your board is unsupported.
    * See the sample documentation for information on how to fix this.
    */
    static const struct gpio_dt_spec ST_LED = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

#endif


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
#if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    /* ******************************************************************************** */
    /* * ATMEL Start                                                                  * */
    /* ******************************************************************************** */

    #error Functions not supported by the current CODE_CONFIGURATOR!

#elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))
    /* ******************************************************************************** */
    /* * Harmony                                                                      * */
    /* ******************************************************************************** */

    #error Functions not supported by the current CODE_CONFIGURATOR!

#elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    /* ******************************************************************************** */
    /* * MCC                                                                          * */
    /* ******************************************************************************** */

    void GPIO_LED__Initialize(void)
    {
        GPIO_LED__SetLow();
    }

    void GPIO_LED__SetLevel(t_LEVEL level)
    {
        if (level == LEVEL_HIGH)
        {
            GPIO_LED__SetHigh();
        }
        else
        {
            GPIO_LED__SetLow();
        }
    }

    void GPIO_LED__GetLevel(t_LEVEL * level)
    {
        *level = (GPIO_LED__GetValue() == 0) ? LEVEL_LOW : LEVEL_HIGH;
    }

    void GPIO_LED__ToggleLevel(void)
    {
        if (GPIO_LED__GetValue() == 0)
        {
            GPIO_LED__SetHigh();
        }
        else
        {
            GPIO_LED__SetLow();
        }
    }

    #error Functions not supported by the current CODE_CONFIGURATOR!
    
#elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))
    /* ******************************************************************************** */
    /* * Melody                                                                       * */
    /* ******************************************************************************** */

    void GPIO_LED__Initialize(void)
    {
        GPIO_LED__SetLow();
    }

    void GPIO_LED__SetLevel(t_LEVEL level)
    {
        if (level == LEVEL_HIGH)
        {
            GPIO_LED__SetHigh();
        }
        else
        {
            GPIO_LED__SetLow();
        }
    }

    void GPIO_LED__GetLevel(t_LEVEL * level)
    {
        *level = (GPIO_LED__GetValue() == 0) ? LEVEL_LOW : LEVEL_HIGH;
    }

    void GPIO_LED__ToggleLevel(void)
    {
        if (GPIO_LED__GetValue() == 0)
        {
            GPIO_LED__SetHigh();
        }
        else
        {
            GPIO_LED__SetLow();
        }
    }

#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))
    /* ******************************************************************************** */
    /* * CUBEMX                                                                       * */
    /* ******************************************************************************** */

    void GPIO__MODBUS_DE_SetLevel (t_LEVEL level)
     {
     	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, level);
     }

#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))
    /* ******************************************************************************** */
    /* * SLCP                                                                         * */
    /* ******************************************************************************** */
    /* GPIO_PinOutSet('port', 'pin')    - Set pin high;
     * GPIO_PinOutClear('port', 'pin')  - Set pin low;
     * GPIO_PinInGet('port', 'pin')     - Get pin level. */

    #error Functions not supported by the current CODE_CONFIGURATOR!

#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))
    /* ******************************************************************************** */
    /* * NRFX                                                                         * */
    /* ******************************************************************************** */

    et_RET GPIO_LED__Initialize(void)
    {
        et_RET  et_ret   = RET_UNEXPECTED;
        int     gpio_ret = 0;

        et_ret = (gpio_is_ready_dt(&ST_LED)) ? RET_OK : RET_FAIL;
        CENTI_CHECK_RET(et_ret);

        gpio_ret = gpio_pin_configure_dt(&ST_LED, GPIO_OUTPUT_ACTIVE);

        et_ret = (gpio_ret == 0)       ? RET_OK                :\
                 (gpio_ret == -EBUSY)  ? RET_BUSY              :\
                 (gpio_ret == -EINVAL) ? RET_INVALID_PARAMETER :\
                                         RET_FAIL;
        CENTI_CHECK_RET(et_ret);

        return RET_OK;
    }

    et_RET GPIO_LED__SetLevel(t_LEVEL level)
    {
        et_RET et_ret = RET_UNEXPECTED;

        et_ret = (gpio_pin_set_dt(&ST_LED, level) == 0) ? RET_OK : RET_FAIL;
        CENTI_CHECK_RET(et_ret);

        return RET_OK;
    }

    et_RET GPIO_LED__GetLevel(t_LEVEL *level)
    {
        et_RET et_ret = RET_UNEXPECTED;

        et_ret = (gpio_pin_get_dt(&ST_LED, level) == 0) ? RET_OK : RET_FAIL;
        CENTI_CHECK_RET(et_ret);

        return RET_OK;
    }

    et_RET GPIO_LED__ToggleLevel(void)
    {
        et_RET et_ret = RET_UNEXPECTED;

        et_ret = (gpio_pin_toggle_dt(&ST_LED) == 0) ? RET_OK : RET_FAIL;
        CENTI_CHECK_RET(et_ret);

        return RET_OK;
    }

#else

    #error Functions not supported by the current CODE_CONFIGURATOR!

#endif


#endif /* defined(__CENTI_GPIO__) */

/* -- End of file -- */
