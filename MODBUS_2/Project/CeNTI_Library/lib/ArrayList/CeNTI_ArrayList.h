/* 
 * Path:   Project/lib/ArrayList/
 * File:   CeNTI_ArrayList.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */

#ifndef __PROJECT_CENTI_LIBRARY_LIB_ARRAYLIST_CENTI_ARRAYLIST_H__
#define __PROJECT_CENTI_LIBRARY_LIB_ARRAYLIST_CENTI_ARRAYLIST_H__

/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_ArrayList_defines.h"
#if (defined(__CENTI_ARRAYLIST_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_ArrayList_types.h"
#include "../Debug/CeNTI_Debug_Returns.h"
#include <stddef.h>
#include <stdint.h>


/* ************************************************************************************ */
/* * Public Functions Prototypes                                                      * */
/* ************************************************************************************ */
/**
 * @brief Initialize an ArrayList.
 * 
 * @param[in] et_arraylist  ArrayList instance. 
 * @param[in] p_vector      Vector's address where ArrayList will store the elements.
 * @param[in] num_elem      Number of elements in the vector.
 * @param[in] size_elem     Size of each element.
 * @param[in] cmp_fn        Comparison function.
 * 
 * @return Indication if everything worked fine.
 * @retval      RET_OK      Everything worked fine.
 * @retval      Other       See et_RET.
 */
et_RET ArrayList__Initialize(et_ARRAYLIST    et_arraylist,
                            void *           p_vector,
                            size_t           num_elem,
                            size_t           size_elem, 
                            t__ARRAYLIST_cmp cmp_fn);

/**
 * @brief Set a new comparison function to match an element.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * @param[in] cmp_fn        Comparison function.
 *
 * @return      Indication if everything worked fine.
 * @retval      RET_OK              Everything worked fine.
 * @retval      RET_NULL_POINTER    cmp_fn is NULL.
 */
et_RET ArrayList__Set_CompareFunction(et_ARRAYLIST     et_arraylist,
                                      t__ARRAYLIST_cmp cmp_fn);

/**
 * @brief Search an element in the ArrayList. 
 * 
 * @param[in]   et_arraylist    ArrayList instance.
 * @param[in]   elem            Element to search.
 * @param[out]  index           Index of the element.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK      Everything worked fine.
 * @retval      Other       See et_RET.
 */
et_RET ArrayList__Search(et_ARRAYLIST et_arraylist,
                         void *       elem,
                         size_t *     index );

/**
 * @brief Get an element from the ArrayList.
 * 
 * @param[in]   et_arraylist    ArrayList instance.
 * @param[in]   index           Index of the element.
 * @param[out]  elem            Element to get.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                      Everything worked fine.
 * @retval      RET_INVALID_PARAMETER       Index is invalid.
 * @retval      Other                       See et_RET.
 */
et_RET ArrayList__Get(et_ARRAYLIST et_arraylist,
                      size_t       index,
                      void *       elem);

/**
 * @brief Add an element in the ArrayList.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * @param[in] elem          Element to add.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK         Everything worked fine.
 * @retval      RET_FULL       ArrayList is full.
 * @retval      Other          See et_RET.
 */
et_RET ArrayList__Add(et_ARRAYLIST et_arraylist,
                      void *       elem);

/**
 * @brief Remove an element from the ArrayList.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * @param[in] elem          Element to remove.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                  Everything worked fine.
 * @retval      RET_INVALID_PARAMETER   Element doesn't exist.
 * @retval      Other                   See et_RET.
 */
et_RET ArrayList__Remove(et_ARRAYLIST et_arraylist,
                         void *       elem);

/**
 * @brief Remove an element from the ArrayList by index.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * @param[in] index         Index of the element.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                  Everything worked fine.
 * @retval      Other                   See et_RET.
 */
et_RET ArrayList__RemoveAt(et_ARRAYLIST et_arraylist,
                           size_t       index);

/**
 * @brief Remove the last element from the ArrayList.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                  Everything worked fine.
 * @retval      Other                   See et_RET.
 */
et_RET ArrayList__RemoveLast(et_ARRAYLIST et_arraylist);

/** 
 * @brief For each element in the ArrayList call a callback.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * @param[in] cb            Callback function.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                  Everything worked fine.
 * @retval      Other                   See et_RET.
 */
et_RET ArrayList_ForEach(et_ARRAYLIST    et_arraylist,
                         t__ARRAYLIST_cb cb);

/**
 * @brief Sort the ArrayList.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * @param[in] sort_fn       Comparison function (qsort style).
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                  Everything worked fine.
 * @retval      Other                   See et_RET.
 */
et_RET ArrayList__Sort(et_ARRAYLIST      et_arraylist,
                       t__ARRAYLIST_sort sort_fn);

/**
 * @brief Clear and deinit the ArrayList.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                  Everything worked fine.
 * @retval      Other                   See et_RET.
 */
et_RET ArrayList__Clear(et_ARRAYLIST et_arraylist);

/**
 * @brief Get the number of elements in the ArrayList.
 * 
 * @param[in] et_arraylist  ArrayList instance.
 * 
 * @return Number of elements in ArrayList.
 */
size_t ArrayList__Get_ElementCounter(et_ARRAYLIST et_arraylist);

/**
 * @brief Check if an element exists in the ArrayList.
 * 
 * @param[in]   et_arraylist ArrayList instance.
 * @param[in]   elem         Element to check.
 * @param[out]  contains     An indication if the element exists.
 * 
 * @return      Indication if everything worked fine.
 * @retval      RET_OK                  Everything worked fine.
 * @retval      Other                   See et_RET.
 */
et_RET ArrayList__Contains(et_ARRAYLIST et_arraylist,
                           void *       elem,
                           bool *       contains);


#endif /* __CENTI_ARRAYLIST_IN_USE__ */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_ARRAYLIST_CENTI_ARRAYLIST_H__ */

/* -- End of file -- */
