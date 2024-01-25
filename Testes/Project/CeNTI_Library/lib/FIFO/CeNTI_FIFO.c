/*
 * Path:    Project/CeNTI_Library/lib/FIFO/
 * File:    CeNTI_FIFO.c
 * Author:  CeNTI
 * 
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_FIFO_defines.h"
#if (defined(__CENTI_FIFO_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_FIFO.h"
#include "../Utils/CeNTI_Data_types.h"
#include "../Utils/CeNTI_Utils.h"


/* ************************************************************************************ */
/* * Constants                                                                        * */
/* ************************************************************************************ */
/* Vector with the type of each FIFO. */
const et_FIFO_VALUE_TYPE ET_FIFO_VALUE_TYPE[FIFO_TOTAL] = \
    { FOREACH_FIFO(GENERATE_FIFO_TYPE) };


/* ************************************************************************************ */
/* * Global Variables                                                                 * */
/* ************************************************************************************ */
/* Indication of initialization procedure was successful. */
static bool g_initialized_vec[FIFO_TOTAL] = {};

/* Vector with a pointer to the first position on each FIFO. */
static void * g_ptr_vec[FIFO_TOTAL] = {};

/* Vector with the size for each FIFO. */
static size_t g_size_vec[FIFO_TOTAL] = {};

/* Vector with the head index on each FIFO. (index for set function) */
static size_t g_head_idx_vec[FIFO_TOTAL] = {};

/* Vector with the tail index on each FIFO. (index for get function) */
static size_t g_tail_idx_vec[FIFO_TOTAL] = {};

/* Vector with the amount of unread bytes on each FIFO. */
static size_t g_total_vec[FIFO_TOTAL] = {};


/* ************************************************************************************ */
/* * Macros                                                                           * */
/* ************************************************************************************ */
static inline void FIFO__Inc_idx(et_FIFO et_fifo, size_t * idx_ptr)
    { *idx_ptr = (*idx_ptr >= (g_size_vec[et_fifo]-1)) ? 0 : *idx_ptr+1; }


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET FIFO__Initialize(et_FIFO et_fifo,\
                        void *  vec_ptr,\
                        size_t  vec_size)
{
    /* Check if pointer is not NULL. */
    CENTI_CHECK_PTR(vec_ptr);

    /* Check vector size. */
    if (vec_size <= 1)
    {
        CENTI_CHECK_RET(RET_INVALID_PARAMETER);
    }

    /* Initialize variables. */
    g_ptr_vec[et_fifo]      = vec_ptr;
    g_size_vec[et_fifo]     = vec_size;
    g_head_idx_vec[et_fifo] = 0;
    g_tail_idx_vec[et_fifo] = 0;
    g_total_vec[et_fifo]    = 0;

    /* Initialization complete. */
    g_initialized_vec[et_fifo]  = true;

    return RET_OK;
}

et_RET FIFO__Set(et_FIFO et_fifo,\
                 void *  value_ptr)
{
    et_RET et_ret = RET_UNEXPECTED;

    /* Check if pointer is NULL. */
    CENTI_CHECK_PTR(value_ptr);
    /* Check initialization. */
    CENTI_CHECK_INIT(g_initialized_vec[et_fifo]);

    switch (ET_FIFO_VALUE_TYPE[et_fifo])
    {
        case FIFO_VALUE_TYPE_U8:

            ((uint8_t *)(g_ptr_vec[et_fifo]))[g_head_idx_vec[et_fifo]] = \
                    *((uint8_t *)value_ptr);
            et_ret = RET_OK;
            break;

        case FIFO_VALUE_TYPE_CHAR:

            ((char *)(g_ptr_vec[et_fifo]))[g_head_idx_vec[et_fifo]] = \
                    *((char *)value_ptr);
            et_ret = RET_OK;
            break;

        case FIFO_VALUE_TYPE_FLOAT:

            ((float *)(g_ptr_vec[et_fifo]))[g_head_idx_vec[et_fifo]] = \
                    *((float *)value_ptr);
            et_ret = RET_OK;
            break;
        
        default:

            et_ret = RET_INVALID_PARAMETER;
            break;
    }

    CENTI_CHECK_RET(et_ret);

    FIFO__Inc_idx(et_fifo, &(g_head_idx_vec[et_fifo]));
    g_total_vec[et_fifo]++;

    return RET_OK;
}

et_RET FIFO__Get(et_FIFO et_fifo,\
                 void *  value_ptr)
{
    et_RET et_ret = RET_UNEXPECTED;

    /* Check if pointer is NULL. */
    CENTI_CHECK_PTR(value_ptr);
    /* Check initialization. */
    CENTI_CHECK_INIT(g_initialized_vec[et_fifo]);

    if (g_total_vec[et_fifo] > 0)
    {
        switch (ET_FIFO_VALUE_TYPE[et_fifo])
        {
            case FIFO_VALUE_TYPE_U8:

                *((uint8_t *)value_ptr) = \
                        ((uint8_t *)(g_ptr_vec[et_fifo]))[g_tail_idx_vec[et_fifo]];
                et_ret = RET_OK;
                break;
            
            case FIFO_VALUE_TYPE_CHAR:

                *((char *)value_ptr) = \
                        ((char *)(g_ptr_vec[et_fifo]))[g_tail_idx_vec[et_fifo]];
                et_ret = RET_OK;
                break;

            case FIFO_VALUE_TYPE_FLOAT:

                *((float *)value_ptr) = \
                        ((float *)(g_ptr_vec[et_fifo]))[g_tail_idx_vec[et_fifo]];
                et_ret = RET_OK;
                break;
            
            default:

                et_ret = RET_INVALID_PARAMETER;
                break;
        }
    }
    else
    {
        et_ret = RET_INVALID_PARAMETER;
    }

    CENTI_CHECK_RET(et_ret);

    FIFO__Inc_idx(et_fifo, &(g_tail_idx_vec[et_fifo]));
    g_total_vec[et_fifo]--;

    return RET_OK;
}

size_t FIFO__GetRemain(et_FIFO et_fifo)
{
    return g_total_vec[et_fifo];
}


#endif /* defined(__CENTI_FIFO_IN_USE__) */

/* -- End of file -- */
