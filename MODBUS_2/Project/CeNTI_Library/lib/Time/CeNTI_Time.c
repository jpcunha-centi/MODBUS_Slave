/* 
 * Path:    Project/CeNTI_Library/lib/Time/
 * File:    CeNTI_Time.c
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Time_defines.h"
#if (defined(__CENTI_TIME_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Time.h"


/* ************************************************************************************ */
/* * Macro Functions                                                                  * */
/* ************************************************************************************ */
/* Get the difference value between two times, considering the first time is bigger than
 * the second time. */
#define GetDiff_big(val1, val2, carry) \
    ((val1 - val2) - carry)

/* Get the difference between two times, considering the first time is smaller than the
 * second time. */
#define GetDiff_small(val1, val2, limit, carry) \
    ((limit - (val2 - val1)) - carry)


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
#if (CENTI_TIME_USEC == CENTI_ENABLE)

    void Time__Add_usec(st_TIME *const st_time_ptr)
    {
        Time__AddN_usec(st_time_ptr, 1);
    }
    
#endif

void Time__Add_msec(st_TIME *const st_time_ptr)
{
    Time__AddN_msec(st_time_ptr, 1);
}

void Time__Add_sec(st_TIME *const st_time_ptr)
{
    Time__AddN_sec(st_time_ptr, 1);
}

#if (CENTI_TIME_MINUTE == CENTI_ENABLE)

    void Time__Add_minute(st_TIME *const st_time_ptr)
    {
        Time__AddN_minute(st_time_ptr, 1);
    }

#endif

#if (CENTI_TIME_HR == CENTI_ENABLE)

    void Time__Add_hr(st_TIME *const st_time_ptr)
    {
        Time__AddN_hr(st_time_ptr, 1);
    }
    
#endif

#if (CENTI_TIME_USEC == CENTI_ENABLE)
    
    void Time__AddN_usec(st_TIME *const st_time_ptr,\
                         t_time_usec    n_usec)
    {
        /* Check if the sum is smaller than the limit. */
        if ((st_time_ptr->usec + n_usec) < TIME_USEC_TO_MSEC)
        {
            /* Add the microseconds. */
            st_time_ptr->usec += n_usec;
        }
        else
        {
            /* Calculate the milliseconds overflows and add them to milliseconds. */
            Time__AddN_msec(st_time_ptr,\
                            ((st_time_ptr->usec + n_usec) / TIME_USEC_TO_MSEC));
            
            /* Set the rest of microseconds. */
            st_time_ptr->usec = ((st_time_ptr->usec + n_usec) % TIME_USEC_TO_MSEC);
        }
    }
    
#endif

void Time__AddN_msec(st_TIME *const st_time_ptr,\
                     t_time_msec    n_msec)
{
    /* Check if the sum is smaller than the limit. */
    if ((st_time_ptr->msec + n_msec) < TIME_MSEC_TO_SEC)
    {
        /* Add the milliseconds. */
        st_time_ptr->msec += n_msec;
    }
    else
    {
        /* Calculate the seconds overflows and add them to seconds. */
        Time__AddN_sec(st_time_ptr, ((st_time_ptr->msec + n_msec) / TIME_MSEC_TO_SEC));
        
        /* Set the rest of milliseconds. */
        st_time_ptr->msec = ((st_time_ptr->msec + n_msec) % TIME_MSEC_TO_SEC);
    }
}

void Time__AddN_sec(st_TIME *const st_time_ptr,\
                    t_time_sec     n_sec)
{
    #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

        /* Check if the sum is smaller than the limit. */
        if((st_time_ptr->sec + n_sec) < TIME_SEC_TO_MINUTE)
        {
            /* Add the seconds. */
            st_time_ptr->sec += n_sec;
        }
        else
        {
            /* Calculate the minutes overflows and add them to minutes. */
            Time__AddN_minute(st_time_ptr,\
                              ((st_time_ptr->sec + n_sec) / TIME_SEC_TO_MINUTE));
            
            /* Set the rest of seconds. */
            st_time_ptr->sec = ((st_time_ptr->sec + n_sec) % TIME_SEC_TO_MINUTE);
        }
    
    #elif (CENTI_TIME_HR == CENTI_ENABLE)

        /* Check if the sum is smaller than the limit. */
        if ((st_time_ptr->sec + n_sec) < TIME_SEC_TO_HOUR)
        {
            /* Add the seconds. */
            st_time_ptr->sec += n_sec;
        }
        else
        {
            /* Calculate the hours overflows and add them to hours. */
            Time__AddN_hr(st_time_ptr, ((st_time_ptr->sec + n_sec) / TIME_SEC_TO_HOUR));
            
            /* Set the rest of seconds. */
            st_time_ptr->sec = ((st_time_ptr->sec + n_sec) % TIME_SEC_TO_HOUR);
        }
        
    #else

        /* Add the seconds. */
        st_time_ptr->sec += n_sec;
        
    #endif
}

#if (CENTI_TIME_MINUTE == CENTI_ENABLE)

    void Time__AddN_minute(st_TIME *const st_time_ptr,\
                           t_time_minute  n_minute)
    {
        #if (CENTI_TIME_HR == CENTI_ENABLE)
            
            /* Check if the sum is smaller than the limit. */
            if ((st_time_ptr->minute + n_minute) < TIME_MINUTE_TO_HOUR)
            {
                /* Add the minutes. */
                st_time_ptr->minute += n_minute;
            }
            else
            {
                /* Calculate the minutes overflows and add them to minutes. */
                Time__AddN_minute(st_time_ptr,\
                        ((st_time_ptr->minute + n_minute) / TIME_MINUTE_TO_HOUR));

                /* Set the rest of minutes. */
                st_time_ptr->minute =\
                        ((st_time_ptr->minute + n_minute) % TIME_MINUTE_TO_HOUR);
            }
        
        #else

            /* Add the minute. */
            st_time_ptr->minute += n_minute;
            
        #endif
    }

#endif

#if (CENTI_TIME_HR == CENTI_ENABLE)

    void Time__AddN_hr(st_TIME *const st_time_ptr,\
                       t_time_hr      n_hr)
    {
        /* Add the hours. */
        st_time_ptr->hr += n_hr;
    }
    
#endif

et_TIME_COMPARE Time__Compare(st_TIME st_time_1,\
                              st_TIME st_time_2)
{
    /* ****** Hours ****** */
    #if (CENTI_TIME_HR == CENTI_ENABLE)

        if (st_time_1.hr > st_time_2.hr)
        {
            return TIME_COMPARE_BIGGER;
        }
        if (st_time_1.hr < st_time_2.hr)
        {
            return TIME_COMPARE_SMALLER;
        }
            
    #endif

    /* ****** Minutes ****** */
    #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

        if (st_time_1.minute > st_time_2.minute)
        {
            return TIME_COMPARE_BIGGER;
        }
        if (st_time_1.minute < st_time_2.minute)
        {
            return TIME_COMPARE_SMALLER;
        }
    
    #endif

    /* ****** Seconds ****** */
    if (st_time_1.sec > st_time_2.sec)
    {
        return TIME_COMPARE_BIGGER;
    }
    if (st_time_1.sec < st_time_2.sec)
    {
        return TIME_COMPARE_SMALLER;
    }
    
    /* ****** Milliseconds ****** */
    if (st_time_1.msec > st_time_2.msec)
    {
        return TIME_COMPARE_BIGGER;
    }
    if (st_time_1.msec < st_time_2.msec)
    {
        return TIME_COMPARE_SMALLER;
    }
    
    /* ****** Microseconds ****** */
    #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

        if (st_time_1.usec > st_time_2.usec)
        {
            return TIME_COMPARE_BIGGER;
        }
        if (st_time_1.usec < st_time_2.usec)
        {
            return TIME_COMPARE_SMALLER;
        }
    
    #endif
        
    return TIME_COMPARE_EQUAL;
}

st_TIME Time__Get_Remaining(st_TIME st_time_1, st_TIME st_time_2)
{
    st_TIME         st_remain_time   = {};
    et_TIME_COMPARE et_compare_times = TIME_COMPARE_EQUAL;
    uint8_t         carry_u8         = 0;
    
    /* Compare the 2 times. */
    et_compare_times = Time__Compare(st_time_1, st_time_2);
    
    if (et_compare_times == TIME_COMPARE_BIGGER)
    {
        /* ********** Microseconds ********** */
        #if (CENTI_TIME_USEC == CENTI_ENABLE)

            if (st_time_1.usec >= st_time_2.usec)
            {
                st_remain_time.usec = GetDiff_big(st_time_1.usec,\
                                                  st_time_2.usec,\
                                                  carry_u8);
                carry_u8 = 0;                
            }
            else
            {
                st_remain_time.usec = GetDiff_small(st_time_1.usec,\
                                                    st_time_2.usec,\
                                                    TIME_USEC_TO_MSEC,\
                                                    carry_u8);
                carry_u8 = 1;                
            }
            
        #endif

        /* ********** Milliseconds ********** */
        if (st_time_1.msec >= st_time_2.msec)
        {
            st_remain_time.msec = GetDiff_big(st_time_1.msec,\
                                              st_time_2.msec,\
                                              carry_u8);
            carry_u8 = 0;
            
        }
        else
        {
            st_remain_time.msec = GetDiff_small(st_time_1.msec,\
                                                st_time_2.msec,\
                                                TIME_MSEC_TO_SEC,\
                                                carry_u8);
            carry_u8 = 1;
        }
        
        /* ********** Seconds ********** */
        if (st_time_1.sec >= st_time_2.sec)
        {
            st_remain_time.sec = GetDiff_big(st_time_1.sec,\
                                             st_time_2.sec,\
                                             carry_u8);
            carry_u8 = 0;
        }
        #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

            else
            {
                st_remain_time.sec = GetDiff_small(st_time_1.sec,\
                                                   st_time_2.sec,\
                                                   TIME_SEC_TO_MINUTE,\
                                                   carry_u8);
                carry_u8 = 1;
            }
            
        #elif (CENTI_TIME_HR == CENTI_ENABLE)

            else
            {
                st_remain_time.sec = GetDiff_small(st_time_1.sec,\
                                                   st_time_2.sec,\
                                                   TIME_SEC_TO_HOUR,\
                                                   carry_u8);
                carry_u8 = 1;
            }
            
        #endif
        
        /* ********** Minutes ********** */
        #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

            if (st_time_1.minute >= st_time_2.minute)
            {
                st_remain_time.minute = GetDiff_big(st_time_1.minute,\
                                                    st_time_2.minute,\
                                                    carry_u8);
                carry_u8 = 0;
            }
            #if (CENTI_TIME_HR == CENTI_ENABLE)

                else
                {
                    st_remain_time.minute = GetDiff_small(st_time_1.minute,\
                                                          st_time_2.minute,\
                                                          TIME_MINUTE_TO_HOUR,\
                                                          carry_u8);
                    carry_u8 = 1;
                }
            
            #endif
            
        #endif            
        
        /* ********** Hours ********** */
        #if (CENTI_TIME_HR == CENTI_ENABLE)

            st_remain_time.hr = GetDiff_big(st_time_1.hr,\
                                            st_time_2.hr,\
                                            carry_u8);
            
        #endif
    }
    else if (et_compare_times == TIME_COMPARE_SMALLER)
    {
        /* ********** Microseconds ********** */
        #if (CENTI_TIME_USEC == CENTI_ENABLE)

            if (st_time_2.usec >= st_time_1.usec)
            {
                st_remain_time.usec = GetDiff_big(st_time_2.usec,\
                                                  st_time_1.usec,\
                                                  carry_u8);
                carry_u8 = 0;                
            }
            else
            {
                st_remain_time.usec = GetDiff_small(st_time_2.usec,\
                                                    st_time_1.usec,\
                                                    TIME_USEC_TO_MSEC,\
                                                    carry_u8);
                carry_u8 = 1;                
            }
            
        #endif

        /* ********** Milliseconds ********** */
        if (st_time_2.msec >= st_time_1.msec)
        {
            st_remain_time.msec = GetDiff_big(st_time_2.msec,\
                                              st_time_1.msec,\
                                              carry_u8);
            carry_u8 = 0;
            
        }
        else
        {
            st_remain_time.msec = GetDiff_small(st_time_2.msec,\
                                                st_time_1.msec,\
                                                TIME_MSEC_TO_SEC,\
                                                carry_u8);
            carry_u8 = 1;
        }
        
        /* ********** Seconds ********** */
        if (st_time_2.sec >= st_time_1.sec)
        {
            st_remain_time.sec = GetDiff_big(st_time_2.sec,\
                                             st_time_1.sec,\
                                             carry_u8);
            carry_u8 = 0;
        }
        #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

            else
            {
                st_remain_time.sec = GetDiff_small(st_time_2.sec,\
                                                   st_time_1.sec,\
                                                   TIME_SEC_TO_MINUTE,\
                                                   carry_u8);
                carry_u8 = 1;
            }
            
        #elif (CENTI_TIME_HR == CENTI_ENABLE)

            else
            {
                st_remain_time.sec = GetDiff_small(st_time_2.sec,\
                                                   st_time_1.sec,\
                                                   TIME_SEC_TO_HOUR,\
                                                   carry_u8);
                carry_u8 = 1;
            }
            
        #endif
        
        /* ********** Minutes ********** */
        #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

            if (st_time_2.minute >= st_time_1.minute)
            {
                st_remain_time.minute = GetDiff_big(st_time_2.minute,\
                                                    st_time_1.minute,\
                                                    carry_u8);
                carry_u8 = 0;
            }
            #if (CENTI_TIME_HR == CENTI_ENABLE)

                else
                {
                    st_remain_time.minute = GetDiff_small(st_time_2.minute,\
                                                          st_time_1.minute,\
                                                          TIME_MINUTE_TO_HOUR,\
                                                          carry_u8);
                    carry_u8 = 1;
                }
            
            #endif
            
        #endif            
        
        /* ********** Hours ********** */
        #if (CENTI_TIME_HR == CENTI_ENABLE)

            st_remain_time.hr = GetDiff_big(st_time_2.hr,\
                                            st_time_1.hr,\
                                            carry_u8);
            
        #endif
    }
    else
    {
        #if (CENTI_TIME_HR == CENTI_ENABLE)
            st_remain_time.hr = 0;
        #endif

        st_remain_time.sec  = 0;
        
        st_remain_time.msec = 0;
        
        #if (CENTI_TIME_MINUTE == CENTI_ENABLE)
        st_remain_time.minute = 0;
        #endif

        #if (CENTI_TIME_USEC == CENTI_ENABLE)
            st_remain_time.usec = 0;
        #endif
    }
    
    return st_remain_time;
}

st_TIME Time__Add_Times(st_TIME time_1, st_TIME time_2)
{
    st_TIME     total_time  = {};
    uint32_t    add_aux     = 0;
    uint8_t     carry       = 0;
    
    /* ********** Microseconds ********** */
    #if (CENTI_TIME_USEC == CENTI_ENABLE)

        add_aux = (time_1.usec + time_2.usec + carry);
        
        total_time.usec = (add_aux % TIME_USEC_TO_MSEC);
        carry           = (uint8_t)(add_aux / TIME_USEC_TO_MSEC);
    
    #endif

    /* ********** Milliseconds ********** */
    add_aux = (time_1.msec + time_2.msec + carry);
        
    total_time.msec = (add_aux % TIME_MSEC_TO_SEC);
    carry           = (uint8_t)(add_aux / TIME_MSEC_TO_SEC);
    
    /* ********** Seconds ********** */
    add_aux = (time_1.sec + time_2.sec + carry);
    
    #if (CENTI_TIME_MINUTE == CENTI_ENABLE)

        total_time.sec = (add_aux % TIME_SEC_TO_MINUTE);
        carry          = (uint8_t)(add_aux / TIME_SEC_TO_MINUTE);
    
    #elif (CENTI_TIME_HR == CENTI_ENABLE)

        total_time.sec = (add_aux % TIME_SEC_TO_HOUR);
        carry          = (uint8_t)(add_aux / TIME_SEC_TO_HOUR);
        
    #else

        total_time.sec = add_aux;
        
    #endif
    
    /* ********** Minutes ********** */
    #if (CENTI_TIME_MINUTE == CENTI_ENABLE)
        
        add_aux = (time_1.minute + time_2.minute + carry);
        
        #if (CENTI_TIME_HR == CENTI_ENABLE)

            total_time.minute = (add_aux % TIME_MINUTE_TO_HOUR);
            carry             = (uint8_t)(add_aux / TIME_MINUTE_TO_HOUR);
            
        #else
            
            total_time.minute = add_aux;
            
        #endif
        
    #endif

    /* ********** Hours ********** */
    #if (CENTI_TIME_HR == CENTI_ENABLE)

        total_time.hr = (time_1.hr + time_2.hr + carry);
        
    #endif
    
    return total_time;
}


#endif /* (defined(__CENTI_TIME_IN_USE__)) */

/* -- End of file -- */
