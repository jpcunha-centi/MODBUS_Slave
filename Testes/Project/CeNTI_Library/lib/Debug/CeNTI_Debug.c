/* 
 * Path:    Project/Devices/CENTI_DEBUG/
 * File:    CENTI_DEBUG.c
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Device in use                                                                    * */
/* ************************************************************************************ */
#include "../Defines/CeNTI_Debug_defines.h"
#if (defined(__CENTI_DEBUG_IN_USE__))


/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */
#include "CeNTI_Debug.h"


/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_RETURN)

    /* Vector with all the returns messages. */
    const char * RET_MSG_VEC[CENTI_DEBUG_MSG_RET_TOTAL] =\
        { FOREACH_MSG_RET(GENERATE_MSG_RET_MSG) };

    /* Vector with all the returns. */
    const et_RET RET_VEC[CENTI_DEBUG_MSG_RET_TOTAL] =\
        { FOREACH_MSG_RET(GENERATE_MSG_RET_RET) };

#endif /* (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_RETURN) */


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
#if (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_RETURN)

    void CeNTI_Debug__Return(et_RET et_ret)
    {
        for (uint8_t ret_idx=0; ret_idx<CENTI_DEBUG_MSG_RET_TOTAL; ret_idx++)
        {
            if (ret_idx == CENTI_DEBUG_MSG_RET_TOTAL)
            {
                CENTI_DEBUG__Output("%s", CENTI_DEBUG_MSG_NOT_AVAILABLE);
                break;
            }
            if (RET_VEC[ret_idx] == et_ret)
            {
                CENTI_DEBUG__Output("%s", RET_MSG_VEC[ret_idx]);
                break;
            }
        }
    }

#endif /* (CENTI_DEBUG_MSG_TYPE & CENTI_DEBUG_MSG_TYPE_RETURN) */


#endif /* (defined(__CENTI_DEBUG_IN_USE__)) */

/* -- End of file -- */
