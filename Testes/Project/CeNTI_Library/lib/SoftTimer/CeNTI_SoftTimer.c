/* 
 * Path:    Project/CeNTI_Library/lib/SoftTimer/
 * File:    CeNTI_SoftTimer.c
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_SoftTimer_defines.h"
#if (defined(__CENTI_SOFTTIMER_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#if (defined(CENTI_SOFTTIMER_TIMER_PATH))
    #include CENTI_SOFTTIMER_TIMER_PATH
#else 
    #error Define CENTI_SOFTTIMER_TIMER_PATH in the Project/CeNTI/Defines/CeNTI_SoftTimer_defines.h file!
#endif

/* Utilities library. */
#include "../Utils/CeNTI_Utils.h"

/* SoftTimer library. */
#include "CeNTI_SoftTimer.h"


/* ************************************************************************************ */
/* * Global Declarations                                                              * */
/* ************************************************************************************ */
/* SoftTimers array. */
static st_SOFTTIMER_Info g_st_softtimers_vec[SOFTTIMER_INSTANCE_TOTAL] = {};

/* SoftTimer counter. */
static st_TIME g_st_time_counter = {};

/* Indication of initialization procedure was successful. */
static bool g_initialized = false;

/* Timer instance for SLCP projects. */
#if (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

    #if (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE)

        static app_timer_t slcp_softtimer;

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_PRECISE)

        static sl_sleeptimer_timer_handle_t slcp_softtimer;

    #endif

/* Internal tick used on CUBEMX projects for HAL libraries. */
#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

    extern __IO uint32_t uwTick;

#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

    #if (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_KERNEL)

        struct k_timer st_nrfx_timer;

    #endif

#endif


/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */
/**
 * @brief Interrupt function callback. Called every time a overflow happens.
 * 
 * @param       None.
 * 
 * @returns     None.
 */
#if ((CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR0) 	&&\
     (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))         )

    static void SoftTimer_ISR__TimerInterrupt(const struct timer_task *const timer_task);

#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

    #if (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE)

        static void SoftTimer_ISR__TimerInterrupt(app_timer_t * timer, void * data);

    #elif (CENTI_SOFTTIMER_TIMER == CNETI_SOFTTIMER_TIMER_RTCC_PRECISE)

        static void SoftTimer_ISR__TimerInterrupt(sl_sleeptimer_timer_handle_t * timer,\
                                                  void * data);
        
    #endif 

#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

    static void SoftTimer_ISR__TimerInterrupt(struct k_timer* timer_id);

#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

    /* Do nothing. */
    
#else

    static void SoftTimer_ISR__TimerInterrupt(void);

#endif

/**
 * @brief Private function used to check if a SoftTimer has passed its running time.
 *          This will update running state and elapsed state in the instance structure.
 * 
 * @param[in]   et_softtimer    SoftTimer instance.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK          Everything worked fine.
 * @retval      Other           See et_RET.
 */
static et_RET SoftTimer_PRIV__CheckTimer(et_SOFTTIMER_INSTANCE et_softtimer);


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET SoftTimer__Initialize(void)
{
    et_RET et_ret = RET_UNEXPECTED;
    
    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        CENTI_DEBUG__Info("SoftTimer initialization started!");
    #endif

    #if (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_SYSTICK)
    
        /* Initialize SYSTICK timer. */
        SYSTICK_TimerInitialize();
        /* Set callback function. */
        SYSTICK_TimerCallbackSet((SYSTICK_CALLBACK)SoftTimer_ISR__TimerInterrupt,\
                                 (uintptr_t)NULL);
        /* Start timer. */
        SYSTICK_TimerStart();
        /* Return ok. */
        et_ret = RET_OK;
        
    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE)

        sl_status_t sc = app_timer_start(&slcp_softtimer,\
                                         1 /* 1 ms. */,\
                                         SoftTimer_ISR__TimerInterrupt,\
                                         NULL /* No callback data. */,\
                                         true /* Is periodic. */);
        
        et_ret = (sc == SL_STATUS_OK)           ? RET_OK            : \
                 (sc == SL_STATUS_NULL_POINTER) ? RET_NULL_POINTER  : \
                                                  RET_FAIL          ;
    
    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_PRECISE)

        sl_status_t sc = sl_sleeptimer_start_periodic_timer_ms(&slcp_softtimer,\
                                                               1 /* 1 ms. */,\
                                                               SoftTimer_ISR__TimerInterrupt,\
                                                               NULL /* No callback data. */,\
                                                               0 /* Highest priority. */,\
                                                               0 /* No flags. */);

        et_ret = (sc == SL_STATUS_OK)           ? RET_OK            : \
                 (sc == SL_STATUS_NULL_POINTER) ? RET_NULL_POINTER  : \
                                                  RET_FAIL          ;

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_HAL)

        HAL_InitTick(TICK_INT_PRIORITY);

        et_ret = RET_OK;
    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_KERNEL)

        k_timer_init(&st_nrfx_timer, SoftTimer_ISR__TimerInterrupt, NULL);

        /* start periodic timer that expires once every ms*/
        k_timer_start(&st_nrfx_timer, K_MSEC(1), K_MSEC(1));

        et_ret = RET_OK;

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TC0)

        #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
    
            static struct timer_task st_softtimer;
            
            /* Configurate instance. */
            st_softtimer.interval = 1;
            st_softtimer.cb       = (timer_cb_t)SoftTimer_ISR__TimerInterrupt;
            st_softtimer.mode     = TIMER_TASK_REPEAT;
            
            /* Set callback function. */
            timer_add_task(&TIMER_0, &st_softtimer);
            /* Start timer. */
            timer_start(&TIMER_0);
            /* Return ok. */
            et_ret = RET_OK;
    
        #else
        
            /* Initialize timer. */
            TC0_TimerInitialize();
            /* Set callback function. */
            TC0_TimerCallbackRegister((TC_TIMER_CALLBACK)SoftTimer_ISR__TimerInterrupt,\
                                      (uintptr_t)NULL);
            /* Start timer. */
            TC0_TimerStart();
            /* Return ok. */
            et_ret = RET_OK;
            
        #endif
        
    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TC1)

        #if (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))
        
            static struct timer_task st_softtimer;
            
            /* Configurate instance. */
            st_softtimer.interval = 1;
            st_softtimer.cb       = (timer_cb_t)SoftTimer_ISR__TimerInterrupt;
            st_softtimer.mode     = TIMER_TASK_REPEAT;
            
            /* Set callback function. */
            timer_add_task(&TIMER_0, &st_softtimer);
            /* Start timer. */
            timer_start(&TIMER_0);
            /* Return ok. */
            et_ret = RET_OK;
            
        #else
        
            /* Initialize timer. */
            TC1_TimerInitialize();
            /* Set callback function. */
            TC1_TimerCallbackRegister((TC_TIMER_CALLBACK)SoftTimer_ISR__TimerInterrupt,\
                                      (uintptr_t)NULL);
            /* Start timer. */
            TC1_TimerStart();
            /* Return ok. */
            et_ret = RET_OK;
            
        #endif

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR0)
    
        #if (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

            /* Initialize timer. */
            Timer0_Initialize();
            /* Set callback function. */
            Timer0_OverflowCallbackRegister(SoftTimer_ISR__TimerInterrupt);
            /* Start timer. */
            Timer0_Start();
            /* Return ok. */
            et_ret = RET_OK;
            
        #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
            /* Initialize timer. */
            TMR0_Initialize();
            /* Set callback function. */
            TMR0_SetInterruptHandler(SoftTimer_ISR__TimerInterrupt);
            /* Start timer. */
            TMR0_StartTimer();
            /* Return ok. */
            et_ret = RET_OK;
            
        #else
            
            static struct timer_task st_softtimer;
        
            /* Configurate instance. */
            st_softtimer.interval = 1;
            st_softtimer.cb       = SoftTimer_ISR__TimerInterrupt;
            st_softtimer.mode     = TIMER_TASK_REPEAT;

            /* Set callback function. */
            timer_add_task(&TIMER_0, &st_softtimer);
            /* Start timer. */
            timer_start(&TIMER_0);
            /* Return ok. */
            et_ret = RET_OK;
            
        #endif
        
    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR1)
    
        #if (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

            /* Initialize timer. */
            Timer1_Initialize();
            /* Set callback function. */
            Timer1_OverflowCallbackRegister(SoftTimer_ISR__TimerInterrupt);
            /* Start timer. */
            Timer1_Start();
            /* Return ok. */
            et_ret = RET_OK;
            
        #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
            /* Initialize timer. */
            TMR1_Initialize();
            /* Set callback function. */
            TMR1_SetInterruptHandler(SoftTimer_ISR__TimerInterrupt);
            /* Start timer. */
            TMR1_StartTimer();
            /* Return ok. */
            et_ret = RET_OK;
            
        #else
            
            static struct timer_task st_softtimer;
        
            /* Configurate instance. */
            st_softtimer.interval = 1;
            st_softtimer.cb       = SoftTimer_ISR__TimerInterrupt;
            st_softtimer.mode     = TIMER_TASK_REPEAT;

            /* Set callback function. */
            timer_add_task(&TIMER_1, &st_softtimer);
            /* Start timer. */
            timer_start(&TIMER_1);
            /* Return ok. */
            et_ret = RET_OK;
            
        #endif

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR2)
    
        #if (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

            /* Initialize timer. */
            Timer2_Initialize();
            /* Set callback function. */
            Timer2_OverflowCallbackRegister(SoftTimer_ISR__TimerInterrupt);
            /* Start timer. */
            Timer2_Start();
            /* Return ok. */
            et_ret = RET_OK;
            
        #elif (defined(__CENTI_CODE_CONFIGURATOR_MCC__))
    
            /* Initialize timer. */
            TMR2_Initialize();
            /* Set callback function. */
            TMR2_SetInterruptHandler(SoftTimer_ISR__TimerInterrupt);
            /* Start timer. */
            TMR2_StartTimer();
            /* Return ok. */
            et_ret = RET_OK;
            
        #else
            
            static struct timer_task st_softtimer;
        
            /* Configurate instance. */
            st_softtimer.interval = 1;
            st_softtimer.cb       = SoftTimer_ISR__TimerInterrupt;
            st_softtimer.mode     = TIMER_TASK_REPEAT;

            /* Set callback function. */
            timer_add_task(&TIMER_2, &st_softtimer);
            /* Start timer. */
            timer_start(&TIMER_2);
            /* Return ok. */
            et_ret = RET_OK;
            
        #endif

    #elif (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TCA0)
    
        /* Initialize timer. */
        TIMER_0_init();
        
        /* Configurate timer. */
        TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
        TCA0.SINGLE.CTRLB   = TCA_SINGLE_WGMODE_NORMAL_gc;
        TCA0.SINGLE.EVCTRL  &= ~(TCA_SINGLE_CNTEI_bm);
        TCA0.SINGLE.PER     = 0x4E20;
        TCA0.SINGLE.CTRLA   = TCA_SINGLE_CLKSEL_DIV1_gc |\
                              TCA_SINGLE_ENABLE_bm;
        
        /* Return ok. */
        et_ret = RET_OK;
        
    #else
    
        et_ret = RET_FAIL;
        #error Define CENTI_SOFTTIMER_TIMER in the Project/CeNTI/Defines/SoftTimer_defines.h file!
        
    #endif

    /* Check if return is not RET_OK. */
    CENTI_CHECK_RET(et_ret);

    /* Indicate that initialization is complete. */
    g_initialized = true;
    
    /* Stop all the SoftTimers. */
    for (uint8_t idx=0; idx<SOFTTIMER_INSTANCE_TOTAL; idx++)
    {
        /* Stop timer. */
        et_ret = SoftTimer__Stop(idx);
        CENTI_CHECK_RET(et_ret);
    }
    
    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        CENTI_DEBUG__Info("SoftTimer initialization complete!");
    #endif
    
    return RET_OK;
}

et_RET SoftTimer__Delay_msec(t_time_msec delay_msec)
{
    et_RET  et_ret        = RET_UNEXPECTED;
    st_TIME st_delay_time = {};
    
    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        CENTI_DEBUG__Info("SoftTimer - Delay of %u msec", delay_msec);
    #endif
    
    st_delay_time.sec  = 0;
    st_delay_time.msec = delay_msec;
    
    /* Start timer. */
    et_ret = SoftTimer__Start(SOFTTIMER_INSTANCE_DELAY, st_delay_time);
    CENTI_CHECK_RET(et_ret);
    
    /* Wait. */
    while (SOFTTIMER_ELAPSED_STATE_NOT_ELAPSED ==\
            SoftTimer__Get_ElapsedState(SOFTTIMER_INSTANCE_DELAY))
    {
        /* Stay here while delay time has not passed. */
    }

    /* Stop timer. */
    et_ret = SoftTimer__Stop(SOFTTIMER_INSTANCE_DELAY);
    CENTI_CHECK_RET(et_ret);
    
    return RET_OK;
}

et_RET SoftTimer__Delay_sec(t_time_sec delay_sec)
{
    et_RET  et_ret        = RET_UNEXPECTED;
    st_TIME st_delay_time = {};
    
    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        CENTI_DEBUG__Info("SoftTimer - Delay of %u sec", delay_sec);
    #endif
        
    st_delay_time.sec  = delay_sec;
    st_delay_time.msec = 0;
    
    /* Start timer. */
    et_ret = SoftTimer__Start(SOFTTIMER_INSTANCE_DELAY, st_delay_time);
    CENTI_CHECK_RET(et_ret);
    
    /* Wait. */
    while (SOFTTIMER_ELAPSED_STATE_NOT_ELAPSED ==\
            SoftTimer__Get_ElapsedState(SOFTTIMER_INSTANCE_DELAY))
    {
        /* Stay here while delay time has not passed. */
    }

    /* Stop timer. */
    et_ret = SoftTimer__Stop(SOFTTIMER_INSTANCE_DELAY);
    CENTI_CHECK_RET(et_ret);
    
    return RET_OK;
}

et_RET SoftTimer__Start(et_SOFTTIMER_INSTANCE et_softtimer,\
                        st_TIME               st_timer_time)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    
    /* Initialize all the timer variables.
     * If timer is already initialized, it will reset all values and do a restart. */
    /* Set running state to running. */
    g_st_softtimers_vec[et_softtimer].et_running_state =\
            SOFTTIMER_RUNNING_STATE_RUNNING;
    /* Clear elapsed state. */
    g_st_softtimers_vec[et_softtimer].et_elapsed_state =\
            SOFTTIMER_ELAPSED_STATE_NOT_ELAPSED;
    /* Set the timer value. */
    g_st_softtimers_vec[et_softtimer].st_delay_time =\
            st_timer_time;
    /* Update start timer value. */
    g_st_softtimers_vec[et_softtimer].st_start_time =\
            g_st_time_counter;
    /* Add start time and timer value to find the stop time. */
    g_st_softtimers_vec[et_softtimer].st_stop_time =\
            Time__Add_Times(g_st_time_counter, st_timer_time);
     
    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        if (et_softtimer != SOFTTIMER_INSTANCE_DELAY)
        {
            CENTI_DEBUG__Info("SoftTimer - Start timer");
            CENTI_DEBUG__Info("SoftTimer ID: %d", et_softtimer);
            CENTI_DEBUG__Info("Actual time: %d", g_st_time_counter.sec);
            CENTI_DEBUG__Info("Stop time: %d", g_st_softtimers_vec[et_softtimer].st_stop_time.sec);
        }
    #endif
    
    return RET_OK;
}

et_RET SoftTimer__Stop(et_SOFTTIMER_INSTANCE et_softtimer)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    
    /* Clear running state. */
    g_st_softtimers_vec[et_softtimer].et_running_state =\
            SOFTTIMER_RUNNING_STATE_STOPPED;
    /* Clear elapsed state. */
    g_st_softtimers_vec[et_softtimer].et_elapsed_state =\
            SOFTTIMER_ELAPSED_STATE_NOT_ELAPSED;
    
    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        if (et_softtimer != SOFTTIMER_INSTANCE_DELAY)
        {
            CENTI_DEBUG__Info("SoftTimer - Stop timer");
            CENTI_DEBUG__Info("SoftTimer ID: %d", et_softtimer);
        }
    #endif
    
    return RET_OK;
}

et_RET SoftTimer__Restart(et_SOFTTIMER_INSTANCE et_softtimer)
{
    /* Check if initialization was successfully complete. */
    CENTI_CHECK_INIT(g_initialized);
    
    /* Update start time. */
    g_st_softtimers_vec[et_softtimer].st_start_time =\
            g_st_time_counter;
    /* Change running state to running. */
    g_st_softtimers_vec[et_softtimer].et_running_state =\
            SOFTTIMER_RUNNING_STATE_RUNNING;
    /* Clear elapsed state. */
    g_st_softtimers_vec[et_softtimer].et_elapsed_state =\
            SOFTTIMER_ELAPSED_STATE_NOT_ELAPSED;
    /* Add start time and timer value to find the stop time. */
    g_st_softtimers_vec[et_softtimer].st_stop_time =\
            Time__Add_Times(g_st_time_counter,\
                            g_st_softtimers_vec[et_softtimer].st_delay_time);
    
    #if (CENTI_SOFTTIMER_DEBUG == CENTI_ENABLE)
        if (et_softtimer != SOFTTIMER_INSTANCE_DELAY)
        {
            CENTI_DEBUG__Info("SoftTimer - Restart timer");
            CENTI_DEBUG__Info("SoftTimer ID: %d", et_softtimer);
            CENTI_DEBUG__Info("Actual time: %d sec", g_st_time_counter.sec);
            CENTI_DEBUG__Info("Stop time: %d sec", g_st_softtimers_vec[et_softtimer].st_stop_time.sec);
        }
    #endif
    
    return RET_OK;
}

et_SOFTTIMER_RUNNING_STATE SoftTimer__Get_RunningState(\
        et_SOFTTIMER_INSTANCE et_softtimer)
{
    /* Update timer state. */
    SoftTimer_PRIV__CheckTimer(et_softtimer);
    
    /* Return state. */
    return g_st_softtimers_vec[et_softtimer].et_running_state;
}

et_SOFTTIMER_ELAPSED_STATE SoftTimer__Get_ElapsedState(\
        et_SOFTTIMER_INSTANCE et_softtimer)
{
    /* Update timer state. */
    SoftTimer_PRIV__CheckTimer(et_softtimer);
    
    /* Return state. */
    return g_st_softtimers_vec[et_softtimer].et_elapsed_state;
}

/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */
#if (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TCA0)
     
    ISR(TCA0_OVF_vect)
    {
        /* Call callback function. */
        SoftTimer_ISR__TimerInterrupt();
        /* Clear flag. */
        TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
    }
     
#endif

#if ((CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_TMR0) &&\
     (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__)))

    static void SoftTimer_ISR__TimerInterrupt(const struct timer_task *const timer_task)

#elif (defined(__CENTI_CODE_CONFIGURATOR_SLCP__))

    #if (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE)

        static void SoftTimer_ISR__TimerInterrupt(app_timer_t * timer, void * data)

    #elif (CENTI_SOFTTIMER_TIMER == CNETI_SOFTTIMER_TIMER_RTCC_PRECISE)

        static void SoftTimer_ISR__TimerInterrupt(sl_sleeptimer_timer_handle_t * timer,\
                                                  void * data)
        
    #endif 

#elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

    void HAL_IncTick(void)

#elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

    static void SoftTimer_ISR__TimerInterrupt(struct k_timer* timer_id)

#else

    static void SoftTimer_ISR__TimerInterrupt(void)

#endif
{
    #if (CENTI_SOFTTIMER_PERIOD == CENTI_SOFTTIMER_PERIOD_100_MICROSEC)

        #if ((defined(__CENTI_CODE_CONFIGURATOR_SLCP__)) && \
             ((CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE) || \
              (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_PRECISE)))

            (void)data;

            if (timer == &slcp_softtimer)
            {
                /* Increment 100 microseconds. */
                Time__AddN_usec(&g_st_time_counter, 100);
            }
        
        #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

            uwTick += HAL_TICK_FREQ_DEFAULT;
            Time__AddN_usec(&g_st_time_counter, 100);

        #else

            /* Increment 100 microseconds. */
            Time__AddN_usec(&g_st_time_counter, 100);

        #endif

    #elif (CENTI_SOFTTIMER_PERIOD == CENTI_SOFTTIMER_PERIOD_1_MILISEC)

        #if ((defined(__CENTI_CODE_CONFIGURATOR_SLCP__)) && \
             ((CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_SIMPLE) || \
              (CENTI_SOFTTIMER_TIMER == CENTI_SOFTTIMER_TIMER_RTCC_PRECISE)))

            (void)data;

            if (timer == &slcp_softtimer)
            {
                /* Increment 1 milliseconds. */
                Time__Add_msec(&g_st_time_counter);
            }

        #elif (defined(__CENTI_CODE_CONFIGURATOR_CUBEMX__))

            uwTick += HAL_TICK_FREQ_DEFAULT;
            Time__Add_msec(&g_st_time_counter);

        #elif (defined(__CENTI_CODE_CONFIGURATOR_NRFX__))

            if (timer_id == &st_nrfx_timer)
            {
                Time__Add_msec(&g_st_time_counter);
            }

        #else

            /* Increment 1 milliseconds. */
            Time__Add_msec(&g_st_time_counter);

        #endif

    #endif
}

static et_RET SoftTimer_PRIV__CheckTimer(et_SOFTTIMER_INSTANCE et_softtimer)
{
    et_TIME_COMPARE et_compare = TIME_COMPARE_EQUAL;
    
    if (SOFTTIMER_RUNNING_STATE_RUNNING ==\
            g_st_softtimers_vec[et_softtimer].et_running_state)
    {
        /* Compare stop time with the current time. */
        et_compare = Time__Compare(g_st_time_counter,\
                                   g_st_softtimers_vec[et_softtimer].st_stop_time);
    
        /* Check if current time as passed the stop time. */
        if ((et_compare == TIME_COMPARE_EQUAL) ||\
            (et_compare == TIME_COMPARE_BIGGER))
        {
            /* Set elapsed state to elapsed. */
            g_st_softtimers_vec[et_softtimer].et_elapsed_state =\
                    SOFTTIMER_ELAPSED_STATE_ELAPSED;
            /* Set running state to stopped. */
            g_st_softtimers_vec[et_softtimer].et_running_state =\
                    SOFTTIMER_RUNNING_STATE_STOPPED;
        }
    }
    
    return RET_OK;
}


#endif /* (defined(__CENTI_SOFTTIMER_IN_USE__)) */

/* -- End of file -- */
