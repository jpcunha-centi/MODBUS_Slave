/* 
 * Path:    Project/Manager/
 * File:    Manager_types.h
 * Author:  CeNTI
 *
 * Created on %<%DATE%>%
 * Modified on %<%DATE%>%
 */


#ifndef __PROJECT_MANAGER_DECLARATIONS_H__
#define	__PROJECT_MANAGER_DECLARATIONS_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* Include Manager defines. */
#include "../Defines/Manager_defines.h"

/* Add each device_types.h file */
#include "../Devices/MODBUS/MODBUS_types.h"


/* ************************************************************************************ */
/* * External variables                                                               * */
/* ************************************************************************************ */
#if (defined(__CENTI_SOFTTIMER_IN_USE__))
    extern volatile t_FLAG **               FLAGS;
    extern volatile et_SOFTTIMER_INSTANCE * ET_FLAG_SOFTTIMER_INSTANCES;
    extern volatile uint8_t                 FLAGS_TOTAL;
#endif


#endif /* __PROJECT_MANAGER_DECLARATIONS_H__ */

/* -- End of file -- */
