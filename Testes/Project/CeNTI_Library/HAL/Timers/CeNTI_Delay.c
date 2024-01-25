/* 
 * Path:   Project/HAL/Timers/
 * File:   CeNTI_Delay.c
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Timers_defines.h"
#if (DELAY_SOURCE != DELAY_SOURCE_NONE)


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Delay.h"

#if (DELAY_SOURCE == DELAY_SOURCE_DEFAULT_FUNCTION)

    #if (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

        #include <zephyr/kernel.h>

    #endif

#endif


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
void Delay__ms(uint16_t msec)
{
    #if (DELAY_SOURCE == DELAY_SOURCE_SOFTTIMER)

        SoftTimer__Delay_msec((t_time_msec)msec);

    #elif (DELAY_SOURCE == DELAY_SOURCE_DEFAULT_FUNCTION)

        #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

            for (uint16_t i=0: i<msec; i++)
            {
                delay_ms(1);
            }

        #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

            for (uint16_t i=0: i<msec; i++)
            {
                SYS_TIME_DelayMs(1);
            }

        #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

            for (uint16_t i=0: i<msec; i++)
            {
                __delay_ms(1);
            }

        #elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

            #warning Function not supported by the current CODE_CONFIGURATED!

        #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

            for (uint16_t i=0: i<msec; i++)
            {
                HAL_Delay(1);
            }

        #elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

            k_busy_wait(((uint32_t) msec) * 1000);

        #else

            #warning Function not supported by the current CODE_CONFIGURATED!

        #endif

    #else

            #warning Function not supported by the current CODE_CONFIGURATED!

    #endif
}


#endif /* (DELAY_SOURCE != DELAY_SOURCE_NONE) */

/* -- End of file -- */
