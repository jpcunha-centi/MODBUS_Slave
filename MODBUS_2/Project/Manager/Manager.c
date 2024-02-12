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

typedef enum _enum_manager_loop_states{
	MANAGER_LOOP_IDLE = 0,
	MANAGER_LOOP_INIT,
	MANAGER_LOOP_CHECK_CONDITIONS,
	MANAGER_LOOP_EXECUTE,
	MANAGER_LOOP_COMPLETE
} et_MANAGER_LOOP_STATE;

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

static void MANAGER__clear_vec (uint8_t *vec, uint8_t vec_size);
static void MANAGER_MODBUS__Build_Response_Msg (uint8_t *MODBUS_cmd, uint8_t *MODBUS_response, uint8_t *response_size);


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
    static uint8_t vec[MAX_MSG_VEC_SIZE] = {};
    static uint8_t msg_size = 0;
    st_MODBUS_COMMAND cmd = {};
    static et_MANAGER_LOOP_STATE manager_loop_state = MANAGER_LOOP_IDLE;

    static uint8_t MODBUS_response_vec[MAX_MSG_VEC_SIZE] = {};

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
        	switch (manager_loop_state){
        	case MANAGER_LOOP_IDLE:
        		CENTI_DEBUG__Verbose("MANAGER LOOP IDLING...");
        	case MANAGER_LOOP_INIT:
        		CENTI_DEBUG__Verbose("MANAGER LOOP INITIALIZATION...");
        		MANAGER__clear_vec (vec, sizeof(vec));
        		msg_size = 0;
        		manager_loop_state = MANAGER_LOOP_CHECK_CONDITIONS;
        		CENTI_DEBUG__Verbose("MANAGER LOOP CHECKING CONDITIONS...");
        		break;
        	case MANAGER_LOOP_CHECK_CONDITIONS:
				et_ret = MODBUS__Receive(MODBUS_DEFAULT, vec, &msg_size);
				if (et_ret == RET_OK)
				{
					manager_loop_state = MANAGER_LOOP_EXECUTE;
				}
				break;
        	case MANAGER_LOOP_EXECUTE:
        		CENTI_DEBUG__Verbose("MANAGER LOOP EXECUTING...");
				if (MODBUS_Slave__Check_Valid_Message(vec, msg_size))
				{
					MODBUS_Slave__Parser_Command (vec, &cmd);
					switch (cmd.function_code)
					{
					case READ_COIL:
						CENTI_DEBUG__Verbose("Request to read coil");
						break;
					case READ_DISCRETE_INPUT:
						CENTI_DEBUG__Verbose("Request to read discrete input");
						break;
					case READ_MULTIPLE_HOLDING_REGS:
						CENTI_DEBUG__Verbose("Request to read multiple holding registers");
						break;
					case READ_INPUT:
						CENTI_DEBUG__Verbose("Request to read input");
						MANAGER_MODBUS__Build_Response_Msg(vec, MODBUS_response_vec, &msg_size);
						MODBUS__Send(MODBUS_DEFAULT, MODBUS_response_vec, msg_size);
						break;
					case WRITE_SINGLE_COIL:
						CENTI_DEBUG__Verbose("Request to write single coil");
		        		MODBUS__Send (MODBUS_DEFAULT, vec, msg_size - 2);
						break;
					case WRITE_SINGLE_REG:
						CENTI_DEBUG__Verbose("Request to write single register");
		        		MODBUS__Send (MODBUS_DEFAULT, vec, msg_size - 2);
						break;
					case WRITE_MULTIPLE_COILS:
						CENTI_DEBUG__Verbose("Request to wrtie multiple coils");
		        		MODBUS__Send (MODBUS_DEFAULT, vec, msg_size - 2);
						break;
					case WRITE_MULTIPLE_HOLDING_REG:
						CENTI_DEBUG__Verbose("Request to write multiple registers");
		        		MODBUS__Send (MODBUS_DEFAULT, vec, msg_size - 2);
						break;
					default:
						CENTI_DEBUG__Verbose("Wrong function code");
						break;
					}
				}
				manager_loop_state = MANAGER_LOOP_COMPLETE;
				break;
        	case MANAGER_LOOP_COMPLETE:
        		CENTI_DEBUG__Verbose("MANAGER LOOP COMPLETE !!");
        		manager_loop_state = MANAGER_LOOP_IDLE;
        		break;
        	default:
        		manager_loop_state = MANAGER_LOOP_IDLE;
        		break;
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
static void MANAGER__clear_vec (uint8_t *vec, uint8_t vec_size)
{
	for (uint8_t i = 0; i < vec_size; i++)
		vec[i] = '\0';
}

static void MANAGER_MODBUS__Build_Response_Msg (uint8_t *MODBUS_cmd, uint8_t *MODBUS_response, uint8_t *response_size)
{
	(*response_size) = 0;
	uint8_t num_register = 0;

	CENTI_DEBUG__Verbose("num of registers to read: %d", num_register);
	MODBUS_response[(*response_size)++] = DEVICE_ADDR;
	MODBUS_response[(*response_size)++] = MODBUS_cmd[1];


	switch (MODBUS_cmd[1])
	{
		case READ_COIL:
			MODBUS_response[(*response_size)++] = 0x01;
			MODBUS_response[(*response_size)++] = 0x00;
			MODBUS_response[(*response_size)++] = 0x01;
			break;
		case READ_DISCRETE_INPUT:
			MODBUS_response[(*response_size)++] = 0x01;
			MODBUS_response[(*response_size)++] = 0xAA;
			MODBUS_response[(*response_size)++] = 0xBB;
			break;
		case READ_MULTIPLE_HOLDING_REGS:
			num_register = ((MODBUS_cmd[4] << 8) + MODBUS_cmd[5]);
			MODBUS_response[(*response_size)++] = num_register;
			for (uint8_t i = 0; i < num_register; i++)
			{
				MODBUS_response[(*response_size)++] = 0xAA;
				MODBUS_response[(*response_size)++] = 0xBB;
			}
			break;
		case READ_INPUT:
			num_register = ((MODBUS_cmd[4] << 8) + MODBUS_cmd[5]);
			MODBUS_response[(*response_size)++] = num_register;
			for (uint8_t i = 0; i < num_register; i++)
			{
				MODBUS_response[(*response_size)++] = 0xAA;
				MODBUS_response[(*response_size)++] = 0xBB;
			}
			break;
	}
}

/* -- End of file -- */
