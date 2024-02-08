/* 
 * Path:    Project/Manager/
 * File:    Manager.c
 * Author:  CeNTI
 *
 * Created on %<%DATE%>%
 * Modified on %<%DATE%>%
 */


/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */
#include "Manager.h"

/* Include CeNTI library. */
#include "../CeNTI_Library/lib/CeNTI_lib_includes.h"

/* Include MODBUS library */
#include "../Devices/MODBUS/MODBUS.h"


/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */
#define MAX_MSG_VEC_SIZE (100)
/* ************************************************************************************ */
/* * Private Typedefs                                                                 * */
/* ************************************************************************************ */
// ...


/* ************************************************************************************ */
/* * Private Enumerations                                                             * */
/* ************************************************************************************ */
/* Manager states. */
typedef enum _enum_manager_state {
    MANAGER_STATE_ERROR = 0             ,
    MANAGER_STATE_INIT                  ,
    MANAGER_STATE_LOOP                  ,
    /* Add states ... */
    // ...
} et_MANAGER_STATE;

typedef enum _enum_modbus_cmd_states{
	MODBUS_CMD_STATE__IDLE = 0,
	MODBUS_CMD_STATE__INIT,
	MODBUS_CMD_STATE__GETCMD,
	MODBUS_CMD_STATE__COMPLETE,
	MODBUS_CMD_STATE__ERROR,
}et_MODBUS_CMD_STATE;

typedef enum _enum_modbus_cmd_errors{
	MODBUS_CMD_ERROR__NONE = 0,
	MODBUS_CMD_ERROR__OVERSIZE,
	MODBUS_CMD_ERROR__WRONG_STATE,
}et_MODBUS_CMD_ERROR;


/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */



/* ************************************************************************************ */
/* * Private Global variables                                                         * */
/* ************************************************************************************ */
/* Indication if initialization procedure was successful. */
static bool g_initialized = false;

/* Manager state. */
static et_MANAGER_STATE g_et_state = MANAGER_STATE_INIT;


/* ************************************************************************************ */
/* * Private Macros                                                                   * */
/* ************************************************************************************ */
/* 
 * @brief Manager check return value.
 *
 * @details Check if return value is not OK. If it is not, set the state to error and
 *          check the return value.
 *
 * @param et_ret - Return value.
 * 
 * @return None.
 */
#define MANAGER_CHECK_RET(et_ret) \
{ \
    if (et_ret != RET_OK) { g_et_state = MANAGER_STATE_ERROR; \
                            CENTI_CHECK_RET(et_ret); } \
}


/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */



/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET Manager__Initialize(void)
{
    et_RET et_ret = RET_UNEXPECTED;
    
    CENTI_DEBUG__Info("Manager - Initialization started!");

    et_ret = MODBUS__Initialize(MODBUS_DEFAULT);
    CENTI_CHECK_RET (et_ret);

    /* Indicate that initialization was successfully complete. */
    g_initialized = true;
    
    g_et_state = MANAGER_STATE_LOOP;

    CENTI_DEBUG__Info("Manager - Initialization complete!");

    return RET_OK;
}

et_RET Manager__Loop(void)
{
    et_RET et_ret = RET_UNEXPECTED;
    static uint8_t vec[30] = {};
    static uint8_t msg_size = 0;
    st_MODBUS_COMMAND cmd = {};

    switch (g_et_state)
    {
        case MANAGER_STATE_ERROR:

            CENTI_DEBUG__Error("Manager - Loop error");
            CENTI_DEBUG__Info("Manager - Reinitializing...");
            
            /* Add error management. */
            // ...
            
            g_et_state = MANAGER_STATE_INIT;
            
        case MANAGER_STATE_INIT:
            
            et_ret = Manager__Initialize();
            MANAGER_CHECK_RET(et_ret);
            
            g_et_state = MANAGER_STATE_LOOP;
            
            break;
            
        case MANAGER_STATE_LOOP:
        	et_ret = MODBUS__Receive(MODBUS_DEFAULT, vec, &msg_size);
        	if (et_ret == RET_OK)
			{
        		if (MODBUS__Check_Valid_Message(vec, msg_size))
        		{
        			MODBUS__Parser_Command (vec, &cmd);
        			CENTI_DEBUG__Verbose("Function code: %02X", cmd.function_code);
        			CENTI_DEBUG__Verbose("Function code: %02X", cmd.register_addr);
        		}
        		CENTI_DEBUG__Verbose("%d", msg_size);
        		MODBUS__Send (MODBUS_DEFAULT, vec, msg_size - 2);
			}

            break;
            
        default:
            
            g_et_state = MANAGER_STATE_ERROR;
            
        break;
    }
    
    return RET_OK;
}


/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */


/* -- End of file -- */
