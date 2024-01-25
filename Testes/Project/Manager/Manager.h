/* 
 * Path:    Project/Manager/
 * File:    Manager.h
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


#ifndef __PROJECT_MANAGER_MANAGER_H__
#define	__PROJECT_MANAGER_MANAGER_H__


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "Manager_types.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/* 
 * @brief Manager initialization.
 * 
 * @param None.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET Manager__Initialize(void);

/* 
 * @brief Manager loop.
 * 
 * @param None.
 * 
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET Manager__Loop(void);


#endif /* __PROJECT_MANAGER_MANAGER_H__ */

/* -- End of file -- */