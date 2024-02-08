/* 
 * Path:   Project/lib/ArrayList/
 * File:   CeNTI_ArrayList_types.h
 * Author: CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */

#ifndef __PROJECT_CENTI_LIBRARY_LIB_ARRAYLIST_CENTI_ARRAYLIST_TYPES_H__
#define __PROJECT_CENTI_LIBRARY_LIB_ARRAYLIST_CENTI_ARRAYLIST_TYPES_H__


/* ************************************************************************************ */
/* * Check if enable                                                                  * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_ArrayList_defines.h"
#if (defined(__CENTI_ARRAYLIST_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include <stddef.h>
#include <stdbool.h>


/* ************************************************************************************ */
/* * Defines                                                                          * */
/* ************************************************************************************ */
#define CENTI_ARRAYLIST_INVALID_INDEX ((size_t) -1)


/* ************************************************************************************ */
/* * Typedefs                                                                         * */
/* ************************************************************************************ */
typedef void (*t__ARRAYLIST_cb) (void* elem); 
typedef int (*t__ARRAYLIST_sort) (const void* elem1, const void* elem2);
typedef bool (*t__ARRAYLIST_cmp) (const void* elem1, const void* elem2);


/* ************************************************************************************ */
/* * Structures                                                                       * */
/* ************************************************************************************ */
typedef struct _struct_arraylist {
    /* Pointer to the array */
    uint8_t * p_vector;
    /* Maximum number of elements that p_vector can store */
    size_t elem_capacity;
    /* Size of each element in p_vector */
    size_t elem_size;
    /* Current number of elements in p_vector */
    size_t elem_counter;
    /* Comparison Function */ 
    t__ARRAYLIST_cmp cmp_fn;
}st_ARRAYLIST;

/* Initialization for the ArrayList structure. */
#define STRUCT_ARRAYLIST_INIT {NULL, CENTI_ARRAYLIST_INVALID_INDEX, CENTI_ARRAYLIST_INVALID_INDEX, 0, NULL}


/* ************************************************************************************ */
/* * Instances                                                                        * */
/* ************************************************************************************ */
/* Add '\' between lines. */
/*               | Instance name             | */ \
#define FOREACH_ARRAYLIST(ARRAYLIST) \
		ARRAYLIST(ARRAY_DEFAULT)\
		ARRAYLIST (LIST_FUNCTION_CODES)\
		ARRAYLIST (LIST_REGISTERS)\

#define GENERATE_ARRAYLIST_ENUM(ENUM) ENUM,

typedef enum _enum_arraylist {
    FOREACH_ARRAYLIST(GENERATE_ARRAYLIST_ENUM)
    ARRAYLIST_TOTAL
} et_ARRAYLIST;


#endif /* (defined(__CENTI_ARRAYLIST_IN_USE__)) */

#endif /* __PROJECT_CENTI_LIBRARY_LIB_ARRAYLIST_CENTI_ARRAYLIST_TYPES_H__ */

/* -- End of file -- */
