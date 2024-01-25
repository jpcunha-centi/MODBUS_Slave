/* 
 * Path:   Project/lib/ArrayList/
 * File:   CeNTI_ArrayList.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_ArrayList_defines.h"
#if (defined(__CENTI_ARRAYLIST_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_ArrayList.h"
#include "../Utils/CeNTI_Data_types.h"
#include "../Utils/CeNTI_Utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/* ************************************************************************************ */
/* * Global Variables                                                                 * */
/* ************************************************************************************ */
/* Indication of initialization procedure was successful. */
static bool g_initialized_vec[ARRAYLIST_TOTAL] = {0};
/* Vector with the elements. */
static st_ARRAYLIST g_arraylist_inst[ARRAYLIST_TOTAL] = {STRUCT_ARRAYLIST_INIT};

/* ************************************************************************************ */
/* * Macros                                                                           * */
/* ************************************************************************************ */
/**
 * @brief Check if two elements are equal.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * @param[in] index         Index of the element.
 * @param[in] elem          Element.
 * 
 * @return true if they are equal, false otherwise.
 */
static inline bool Element_Is_Equal(et_ARRAYLIST et_arraylist,
                                    size_t       index,
                                    void *       elem)
{
    return g_arraylist_inst[et_arraylist].cmp_fn(\
            g_arraylist_inst[et_arraylist].p_vector + \
            (index * g_arraylist_inst[et_arraylist].elem_size), elem);
}


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET ArrayList__Initialize(et_ARRAYLIST     et_arraylist,
                             void *           p_vector,
                             size_t           num_elem,
                             size_t           size_elem, 
                             t__ARRAYLIST_cmp cmp_fn)
{
    et_RET et_ret = RET_UNEXPECTED;

    CENTI_CHECK_PTR(p_vector);

    if ((num_elem <= 1) || (size_elem == 0))
    {
        CENTI_CHECK_RET(RET_INVALID_PARAMETER);
    }

    et_ret = ArrayList__Clear(et_arraylist);
    CENTI_CHECK_RET(et_ret);

    g_arraylist_inst[et_arraylist].p_vector      = (uint8_t *) p_vector;
    g_arraylist_inst[et_arraylist].elem_capacity = num_elem;
    g_arraylist_inst[et_arraylist].elem_size     = size_elem;

    if (cmp_fn != NULL)
    {
        g_arraylist_inst[et_arraylist].cmp_fn = cmp_fn;
    }

    g_initialized_vec[et_arraylist] = true;

    return RET_OK;
}

et_RET ArrayList__Set_CompareFunction(et_ARRAYLIST     et_arraylist,
                                      t__ARRAYLIST_cmp cmp_fn)
{
    CENTI_CHECK_PTR(cmp_fn);

    g_arraylist_inst[et_arraylist].cmp_fn = cmp_fn;

    return RET_OK;
}

et_RET ArrayList__Search(et_ARRAYLIST et_arraylist,
                         void *       elem,
                         size_t *     index )
{
    CENTI_CHECK_PTR(elem);
    CENTI_CHECK_PTR(index);
    CENTI_CHECK_PTR(g_arraylist_inst[et_arraylist].cmp_fn);
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    *index = CENTI_ARRAYLIST_INVALID_INDEX;

    for(size_t elem_idx = 0; elem_idx < g_arraylist_inst[et_arraylist].elem_counter; elem_idx++)
    {
        if (Element_Is_Equal(et_arraylist, elem_idx, elem))
        {
            *index = elem_idx;
            break;
        }
    }
    
    if (*index == CENTI_ARRAYLIST_INVALID_INDEX)
    {
        CENTI_CHECK_RET(RET_INVALID_PARAMETER);
    }
    
    return RET_OK;
}

et_RET ArrayList__Get(et_ARRAYLIST et_arraylist,
                      size_t       index,
                      void *       elem)
{
    CENTI_CHECK_PTR(elem);
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    if (index >= g_arraylist_inst->elem_counter)
    {
        CENTI_CHECK_RET(RET_INVALID_PARAMETER);
    }

    memcpy(elem,
           g_arraylist_inst[et_arraylist].p_vector + (index * g_arraylist_inst[et_arraylist].elem_size),
           g_arraylist_inst[et_arraylist].elem_size);

    return RET_OK;
}

et_RET ArrayList__Add(et_ARRAYLIST et_arraylist,
                      void *       elem)
{
    CENTI_CHECK_PTR(elem);
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    if (g_arraylist_inst[et_arraylist].elem_counter == g_arraylist_inst[et_arraylist].elem_capacity)
    {
        CENTI_CHECK_RET(RET_FULL);
    }

    memcpy(g_arraylist_inst[et_arraylist].p_vector + (g_arraylist_inst[et_arraylist].elem_counter * g_arraylist_inst[et_arraylist].elem_size),
           elem,
           g_arraylist_inst[et_arraylist].elem_size);
    g_arraylist_inst[et_arraylist].elem_counter++;

    return RET_OK;
}

et_RET ArrayList__RemoveAt(et_ARRAYLIST et_arraylist,
                           size_t       index)
{
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    if (index >= g_arraylist_inst[et_arraylist].elem_counter)
    {
        CENTI_CHECK_RET(RET_INVALID_PARAMETER);
    }
    
    memmove(g_arraylist_inst[et_arraylist].p_vector + (index * g_arraylist_inst[et_arraylist].elem_size),
            g_arraylist_inst[et_arraylist].p_vector + ((index + 1) * g_arraylist_inst[et_arraylist].elem_size),
            ((g_arraylist_inst[et_arraylist].elem_counter - 1) - index) * g_arraylist_inst[et_arraylist].elem_size);
    
    memset(g_arraylist_inst[et_arraylist].p_vector + ((g_arraylist_inst[et_arraylist].elem_counter - 1) * g_arraylist_inst[et_arraylist].elem_size),
           0,
           g_arraylist_inst[et_arraylist].elem_size);

    g_arraylist_inst[et_arraylist].elem_counter--;

    return RET_OK;
}

et_RET ArrayList__Remove(et_ARRAYLIST et_arraylist,
                        void *        elem)
{
    et_RET et_ret = RET_INVALID_PARAMETER;

    CENTI_CHECK_PTR(elem);
    CENTI_CHECK_PTR(g_arraylist_inst[et_arraylist].cmp_fn);
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    for(size_t elem_idx = 0; elem_idx < g_arraylist_inst[et_arraylist].elem_counter; elem_idx++)
    {
        if (Element_Is_Equal(et_arraylist, elem_idx, elem))
        {
            et_ret = ArrayList__RemoveAt(et_arraylist, elem_idx);
            break;
        }
    }

    CENTI_CHECK_RET(et_ret);

    return RET_OK;
}

et_RET ArrayList__RemoveLast(et_ARRAYLIST et_arraylist)
{
    et_RET et_ret = RET_OK;
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    if (g_arraylist_inst[et_arraylist].elem_counter == 0)
    {
        CENTI_CHECK_RET(RET_EMPTY);
    }

    et_ret = ArrayList__RemoveAt(et_arraylist, g_arraylist_inst[et_arraylist].elem_counter - 1);
    CENTI_CHECK_RET(et_ret);

    return RET_OK;
}

et_RET ArrayList__Sort(et_ARRAYLIST      et_arraylist,
                       t__ARRAYLIST_sort sort_fn)
{
    CENTI_CHECK_PTR(sort_fn);
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    qsort(g_arraylist_inst[et_arraylist].p_vector, 
          g_arraylist_inst[et_arraylist].elem_counter, 
          g_arraylist_inst[et_arraylist].elem_size, 
          sort_fn);

    return RET_OK;
}

et_RET ArrayList_ForEach(et_ARRAYLIST    et_arraylist,
                         t__ARRAYLIST_cb cb)
{
    CENTI_CHECK_PTR(cb);
    CENTI_CHECK_INIT(g_initialized_vec[et_arraylist]);

    for(size_t elem_idx = 0; elem_idx < g_arraylist_inst[et_arraylist].elem_counter; elem_idx++)
    {
        cb(g_arraylist_inst[et_arraylist].p_vector + (elem_idx * g_arraylist_inst[et_arraylist].elem_size));
    }

    return RET_OK;
}

size_t ArrayList__Get_ElementCounter(et_ARRAYLIST et_arraylist)
{
    return g_arraylist_inst[et_arraylist].elem_counter;
}

et_RET ArrayList__Clear(et_ARRAYLIST et_arraylist)
{
    st_ARRAYLIST clear_arraylist   = STRUCT_ARRAYLIST_INIT;
    g_arraylist_inst[et_arraylist] = clear_arraylist;

    g_initialized_vec[et_arraylist] = false;

    return RET_OK;    
}

et_RET ArrayList__Contains(et_ARRAYLIST et_arraylist,
                           void *       elem,
                           bool *       contains)
{
    et_RET et_ret = RET_UNEXPECTED;
    size_t idx    = 0;
    
    et_ret = ArrayList__Search(et_arraylist, elem, &idx);    
    CENTI_CHECK_RET(et_ret);

    *contains = (idx != CENTI_ARRAYLIST_INVALID_INDEX);

    return RET_OK;    
}


#endif /* defined(__CENTI_ARRAYLIST_IN_USE__) */

/* -- End of file -- */
