/* 
 * Path:    Project/CeNTI_Library/lib/Defines/
 * File:    CeNTI_SoftTimer_defines.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_SOFTTIMER_DEFINES_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_SOFTTIMER_DEFINES_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Lib_defines.h"


/* ************************************************************************************ */
/* * SoftTimer Defines                                                                * */
/* ************************************************************************************ */
#if ((defined(CENTI_ENABLE_SOFTTIMER))          &&\
     (CENTI_ENABLE_SOFTTIMER == CENTI_ENABLE)   )


    /* ******************************************************************************** */
    /* * Safety                                                                       * */
    /* ******************************************************************************** */
    #if (CENTI_ENABLE_TIME == CENTI_DISABLE)
        #error Enable CENTI_ENABLE_TIME in Project/lib/Defines/CeNTI_lib_defines.h file!
    #endif
    #if (CENTI_ENABLE_INTERRUPTS == CENTI_DISABLE)
        #error Enable CENTI_ENABLE_INTERRUPTS in Project/lib/Defines/CeNTI_lib_defines.h file!
    #endif


    /* ******************************************************************************** */
    /* * Includes                                                                     * */
    /* ******************************************************************************** */
    #include "CeNTI_Time_defines.h"


    /* ******************************************************************************** */
    /* * Defines                                                                      * */
    /* ******************************************************************************** */
    #define __CENTI_SOFTTIMER_IN_USE__
    

    /* ******************************************************************************** */
    /* * Timer                                                                        * */
    /* ******************************************************************************** */
    /* ********** SoftTimer sources ********** */
    #define CENTI_SOFTTIMER_TIMER_NONE          (-1)
    #define CENTI_SOFTTIMER_TIMER_SYSTICK       (1)
    #define CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE   (2)
    #define CENTI_SOFTTIMER_TIMER_RTCC_PRECISE  (3)
    #define CENTI_SOFTTIMER_TIMER_HAL           (4)
    #define CENTI_SOFTTIMER_TIMER_KERNEL        (5)  /* Zephyr uses the nRF RTC. */
    #define CENTI_SOFTTIMER_TIMER_TMR0          (10)
    #define CENTI_SOFTTIMER_TIMER_TMR1          (11)
    #define CENTI_SOFTTIMER_TIMER_TMR2          (12)
    #define CENTI_SOFTTIMER_TIMER_TC0           (20)
    #define CENTI_SOFTTIMER_TIMER_TC1           (21)
    #define CENTI_SOFTTIMER_TIMER_TCA0          (30)

    /* ********** SoftTimer selection ********** */
    /* # ------ # Change Here # ------ # */
    #define CENTI_SOFTTIMER_TIMER   CENTI_SOFTTIMER_TIMER_HAL

    /* ********** Safety ********** */
    #if ((!defined(CENTI_SOFTTIMER_TIMER))                      ||\
         (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_NONE)  )
        #error Define CENTI_SOFTTIMER_TIMER in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!
    #endif


    /* ******************************************************************************** */
    /* * Debug                                                                        * */
    /* ******************************************************************************** */
    /* # ------ # Change Here # ------ # */
    #define CENTI_SOFTTIMER_DEBUG   CENTI_DISABLE

    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        /* Debug library. */
        #include "../Debug/CeNTI_Debug.h"
    #endif


    /* ******************************************************************************** */
    /* * Period                                                                       * */
    /* ******************************************************************************** */
    /* ********** Period types ********** */
    #define CENTI_SOFTTIMER_PERIOD_NONE         (-1)
    #define CENTI_SOFTTIMER_PERIOD_100_MICROSEC (1)
    #define CENTI_SOFTTIMER_PERIOD_1_MILISEC    (2)

    /* ********** Period selection ********** */
    /* # ------ # Change Here # ------ # */
    #define CENTI_SOFTTIMER_PERIOD  CENTI_SOFTTIMER_PERIOD_1_MILISEC

    /* ********** Safety ********** */
    #if ((!defined(CENTI_SOFTTIMER_PERIOD))                         ||\
         (CENTI_SOFTTIMER_PERIOD == CENTI_SOFTTIMER_PERIOD_NONE)    )
        #error Define CENTI_SOFTTIMER_PERIOD in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!
    #endif


    /* ******************************************************************************** */
    /* * Path                                                                         * */
    /* ******************************************************************************** */
    #if (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_SYSTICK)

        #if (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "config/default/peripheral/systick/plib_systick.h"

        #elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "em_cmu.h"

        #else

            #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!

        #endif

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE)

        #define CENTI_SOFTTIMER_TIMER_PATH \
            "app_timer.h"

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_PRECISE)

        #define CENTI_SOFTTIMER_TIMER_PATH \
            "sl_sleeptimer.h"

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_HAL)

	    #if (defined(__STM32L4_CUBEMX_ARM__))

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "stm32l4xx_hal.h"

        #elif (defined(__STM32F4_CUBEMX_ARM__))

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "stm32f4xx_hal.h"

        #else

            #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!
            
        #endif

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_KERNEL)

        #define CENTI_SOFTTIMER_TIMER_PATH \
            "zephyr/kernel.h"

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TC0)
        
        #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TC1)
        
        #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TCA0)

        #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR0)

        #if (defined(__CENTI_CODE_CONFIGURATOR_MELODY__)    )

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "../../../../mcc_generated_files/timer/tmr0.h"

        #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__)     )

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "../../../../mcc_generated_files/tmr0.h"
        
        #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__) )

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "driver_init.h"

        #else

            #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!

        #endif

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR1)

        #if (defined(__CENTI_CODE_CONFIGURATOR_MELODY__)    )

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "../../../../mcc_generated_files/timer/tmr1.h"

        #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__)     )

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "../../../../mcc_generated_files/tmr1.h"
        
        #else

            #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!

        #endif

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR2)

        #if (defined(__CENTI_CODE_CONFIGURATOR_MELODY__)    )

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "../../../../mcc_generated_files/timer/tmr2.h"

        #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__)     )

            #define CENTI_SOFTTIMER_TIMER_PATH \
                "../../../../mcc_generated_files/tmr2.h"
        
        #else

            #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!

        #endif

    #else

        #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file! 

    #endif

#else

    #undef CENTI_SOFTTIMER_TIMER
    #undef CENTI_SOFTTIMER_PERIOD
    #undef CENTI_SOFTTIMER_TIMER_PATH

#endif


#endif /* __PROJECT_CENTI_LIBRARY_LIB_DEFINES_CENTI_SOFTTIMER_DEFINES_H__ */

/* -- End of file -- */
