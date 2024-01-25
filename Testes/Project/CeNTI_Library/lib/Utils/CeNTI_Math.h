/* Path:    Project/CeNTI_Library/lib/Utils/
 * File:    CeNTI_Math.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_MATH_H__
#define	__PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_MATH_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "CeNTI_Data_types.h"


/* ************************************************************************************ */
/* * Values                                                                           * */
/* ************************************************************************************ */
/* Pi. */
#define PI  ((float)3.141592)


/* ************************************************************************************ */
/* * Macros                                                                           * */
/* ************************************************************************************ */
#define KILO(val)   ((float)(((float)(val))*1000.0))
#define MEGA(val)   ((float)(KILO(val)*1000.0))
#define GIGA(val)   ((float)(MEGA(val)*1000.0))
#define TERA(val)   ((float)(GIGA(val)*1000.0))
#define MILI(val)   ((float)(((float)(val))/1000.0))
#define MICRO(val)  ((float)(MILI(val)/1000.0))
#define NANO(val)   ((float)(MICRO(val)/1000.0))
#define PICO(val)   ((float)(NANO(val)/1000.0))

/* Power by 2. */
#define PWR_2(val)  (float)((val)*(val))

/* Return the smaller value of 2. */
#define CENTI__MIN(v1, v2) (((v1)<(v2)) ? (v1) : (v2))
/* Return the bigger value of 2. */
#define CENTI__MAX(v1, v2) (((v1)>(v2)) ? (v1) : (v2))
/* Return the absolute value. */
#define CENTI__ABS(val) (((val)<0) ? ((val)*(-1)) : (val))


#endif /* __PROJECT_CENTI_LIBRARY_LIB_UTILS_CENTI_MATH_H__ */

/* -- End of file -- */
