/* 
 * Path:    Project/Manager/
 * File:    Manager.c
 * Author:  CeNTI
 *
 * Created on January 10, 2024
 * Modified on January 11, 2024
 */


/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */
#include "Manager.h"

/* Include CeNTI library. */
#include "../CeNTI_Library/lib/CeNTI_lib_includes.h"

#include "../Devices/MODBUS/MODBUS.h"


/* ************************************************************************************ */
/* * Devices States                                                                   * */
/* ************************************************************************************ */
/* ********** Command processing status. ******************************************** */

typedef enum _enum_DEVICE_processing_status {
    DEVICE_PROCESS_STATUS__IDLE = 0,
    DEVICE_PROCESS_STATUS__PROCESSING,
    DEVICE_PROCESS_STATUS__DONE,
    DEVICE_PROCESS_STATUS__ERROR
}et_DEVICE_PROCESS_STATUS;

/* ********** Add all the commands here. ******************************************** */

typedef enum _enum_DEVICE_commands {
    DEVICE_CMD__NONE = -1      		,          // No command.
    DEVICE_CMD__INIT = 0       		,          // Initializes device.
    DEVICE_CMD__GET_DATA = 1   		,          // Get data from device.
	DEVICE_CMD__CONFIGURE_DEVICE = 2,		   // Configure a device.
}et_DEVICE_CMD;

/* ********************************************************************************** */
/* ********** Add all the states here. ********************************************** */

typedef enum _enum_DEVICE_command_states {
    DEVICE_CMD_STATE__INIT = 0       ,   // Initializes device.
    DEVICE_CMD_STATE__RECEIVE_CMD    ,   // Sends command to device.
	DEVICE_CMD_STATE__READ_SENSOR	 ,
	DEVICE_CMD_STATE__PROCESS_DATA	 ,	 // Process the data.
    DEVICE_CMD_STATE__REPORT_DATA    ,   // Reports data from device.
    DEVICE_CMD_STATE__DONE           ,   // Done.
}et_DEVICE_CMD_STATE;


/* ********************************************************************************** */
/* ********** Add all the vectors here. ********************************************* */

const et_DEVICE_CMD_STATE DEVICE_CMD_init_vec[] = {
    DEVICE_CMD_STATE__INIT			 ,
    DEVICE_CMD_STATE__DONE
};

const et_DEVICE_CMD_STATE DEVICE_CMD_configure_device_vec[] = {
	DEVICE_CMD_STATE__INIT			 ,
	DEVICE_CMD_STATE__DONE
};

const et_DEVICE_CMD_STATE DEVICE_CMD__get_data[] = {
	DEVICE_CMD_STATE__INIT			 ,
	DEVICE_CMD_STATE__READ_SENSOR	 ,
	DEVICE_CMD_STATE__DONE
};

const et_DEVICE_CMD_STATE DEVICE_CMD__report_data[] = {
	DEVICE_CMD_STATE__INIT			 ,
	DEVICE_CMD_STATE__READ_SENSOR	 ,
	DEVICE_CMD_STATE__PROCESS_DATA	 ,
	DEVICE_CMD_STATE__REPORT_DATA	 ,
	DEVICE_CMD_STATE__DONE
};

/* ********************************************************************************** */
/* ********** Creation of the state vectors. **************************************** */

#define FOREACH_DEVICE_CMD_STATES(CMD_STATES)\
        CMD_STATES(DEVICE_STATE_INIT, DEVICE_CMD_init_vec)\
		CMD_STATES(DEVICE_STATE_CONFIGURE_DEVICE, DEVICE_CMD_configure_device_vec)\
		CMD_STATES(DEVICE_STATE_GET_DATA, DEVICE_CMD__get_data)\
		CMD_STATES(DEVICE_STATE_REPORT_DATA, DEVICE_CMD__report_data)

#define GENERATE_DEVICE_CMD_STATES_ENUM(ENUM, VEC) ENUM,
#define GENERATE_DEVICE_CMD_STATES_STATE(ENUM, VEC) VEC,

typedef enum _enum_DEVICE_STATES {
    FOREACH_DEVICE_CMD_STATES(GENERATE_DEVICE_CMD_STATES_ENUM)
    DEVICE_STATE_TOTAL
}et_DEVICE_STATE;

const et_DEVICE_CMD_STATE * DEVICE_STATE_vec[DEVICE_STATE_TOTAL] = {
    FOREACH_DEVICE_CMD_STATES(GENERATE_DEVICE_CMD_STATES_STATE)
};

/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */
#define MAX_WAITING_MANAGER_CMDS (30)
#define SLAVE_ADDRESS (0x30)
#define MAX_MODBUS_MSG_SIZE (16)

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
	MANAGER_STATE_IDLE					,
    MANAGER_STATE_PROCESS_CMD           ,
} et_MANAGER_STATE;


/* ************************************************************************************ */
/* * Private Structures                                                               * */
/* ************************************************************************************ */


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
/* * Flags (Add desired flags here)                                                   * */
/* ************************************************************************************ */
#if (defined(__CENTI_SOFTTIMER_IN_USE__))

    /* Add desired flags here. */
    /* Example:
     * static t_FLAG f_LED1 = FLAG_OFF; */
    static t_FLAG f_collect_data = FLAG_OFF;

    /* Define each flag SoftTimer instance.
     * Don't forget the '\' at the end of each line. */
    /* Example:
     *     | Name          		| SoftTimer instance             	    | Flag variable     |
     * FLAG( FLAG_LED1     		, SOFTTIMER_INSTANCE_LED1_LOOP      	, f_LED1            ) */
    #define FOREACH_FLAG(FLAG)\
    FLAG( FLAG_collect_data    	, SOFTTIMER_INSTANCE_collect_data_LOOP  , f_collect_data	)


#endif

/* ************************************************************************************ */
/* * SoftTimer Flags                                                                  * */
/* ************************************************************************************ */
#if (defined(__CENTI_SOFTTIMER_IN_USE__))

    /* Macros to generate enums and flags. */
    #define GENERATE_FLAG_ENUM(ENUM, SOFT_INST, FLAG) ENUM,
    #define GENERATE_FLAG_FLAG(ENUM, SOFT_INST, FLAG) &FLAG,
    #define GENERATE_FLAG_SOFT_INST(ENUM, SOFT_INST, FLAG) SOFT_INST,

    /* Enumerate all flags. */
    typedef enum _enum_FLAG {
        FOREACH_FLAG(GENERATE_FLAG_ENUM)
        FLAG_TOTAL
    }et_FLAG;
    /* Total number of flags. */
    volatile uint8_t FLAGS_TOTAL = FLAG_TOTAL;
    /* Pointers to all flags. */
    volatile t_FLAG * vecFLAGS[FLAG_TOTAL] = { FOREACH_FLAG(GENERATE_FLAG_FLAG) };
    volatile t_FLAG **FLAGS = &vecFLAGS[0];
    /* Pointers to all SoftTimer instances. */
    volatile et_SOFTTIMER_INSTANCE vecET_FLAG_SOFTTIMER_INSTANCES[FLAG_TOTAL] = \
        { FOREACH_FLAG(GENERATE_FLAG_SOFT_INST) };
    volatile et_SOFTTIMER_INSTANCE *ET_FLAG_SOFTTIMER_INSTANCES = \
        &vecET_FLAG_SOFTTIMER_INSTANCES[0];
#endif


/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */
// ...


/* ************************************************************************************ */
/* * Private Global variables                                                         * */
/* ************************************************************************************ */
/* Indication if initialization procedure was successful. */
static bool g_initialized = false;
/* Manager state. */
static et_MANAGER_STATE g_et_state = MANAGER_STATE_INIT;
/* Device state */
static et_DEVICE_PROCESS_STATUS g_et_device_process_status = DEVICE_PROCESS_STATUS__IDLE;
/* Vector Device state commands */
static et_DEVICE_CMD vec_MANAGER_CMDS__waiting[MAX_WAITING_MANAGER_CMDS] = {};
/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */
/**
 * @brief Device state machine.
 *
 * @param et_cmd - Device command.
 *
 * @return Indication if everything worked fine.
 */
static et_RET Manager_DEVICE__StateMachine(et_DEVICE_CMD et_cmd);

static bool Manager__NewCommandAvailable(void);

static et_RET Manager__GetCommand(et_DEVICE_CMD *et_cmd);

static void DEVICE__Build_Data_Message (uint8_t *MODBUS_msg, et_MODBUS_FUNCTION_CODES function_code, uint16_t data, uint8_t *msg_size);

/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET Manager__Initialize(void)
{
    et_RET et_ret = RET_UNEXPECTED;
    st_TIME ST_COLLECT_DATA_TIME = { .sec = 5, .msec = 0 };
    CENTI_DEBUG__Info("Manager initialization");
    /* Initialize each device. */
    SoftTimer__Start(SOFTTIMER_INSTANCE_collect_data_LOOP, ST_COLLECT_DATA_TIME);
    et_ret = ArrayList__Initialize(LIST_MANAGER_COMMANDS_WAITING, vec_MANAGER_CMDS__waiting, MAX_WAITING_MANAGER_CMDS, sizeof(et_DEVICE_CMD), NULL);
    MANAGER_CHECK_RET(et_ret);
    et_ret = MODBUS__Initialize(MODBUS_DEFAULT);
    MANAGER_CHECK_RET(et_ret);

    /* Indicate that initialization was successfully complete. */
    g_initialized = true;
    g_et_state = MANAGER_STATE_IDLE;
    CENTI_DEBUG__Info("Manager initialization complete");
    return RET_OK;
}

et_RET Manager__Loop(void)
{
    et_RET et_ret = RET_UNEXPECTED;
    static et_DEVICE_CMD et_cmd = DEVICE_CMD__NONE;
    et_DEVICE_CMD et_aux_cmd = DEVICE_STATE_GET_DATA;
    st_MODBUS_COMMAND command = {};
        
    switch (g_et_state)
    {
        case MANAGER_STATE_ERROR:
            CENTI_DEBUG__Error("Manager error");
            CENTI_DEBUG__Info("Reinitializing manager");
            g_et_state = MANAGER_STATE_INIT;
        case MANAGER_STATE_INIT:
            et_ret = Manager__Initialize();
            MANAGER_CHECK_RET(et_ret);
            et_cmd = DEVICE_CMD_STATE__INIT;
            et_ret = Manager_DEVICE__StateMachine(et_cmd);
			MANAGER_CHECK_RET(et_ret);
			g_et_state = MANAGER_STATE_IDLE;
            break;
        case MANAGER_STATE_IDLE:
        	if (f_collect_data == FLAG_ON)
            {
				CENTI_DEBUG__Info("Time to get data");
				f_collect_data = FLAG_OFF;
				et_ret = ArrayList__Add(LIST_MANAGER_COMMANDS_WAITING, &et_aux_cmd);
				MANAGER_CHECK_RET(et_ret);
				SoftTimer__Restart(SOFTTIMER_INSTANCE_collect_data_LOOP);
				g_et_state = MANAGER_STATE_IDLE;
                break;
            }
        	if (Manager__NewCommandAvailable())
			{
				CENTI_DEBUG__Info("New command available");
				et_ret = Manager__GetCommand(&et_cmd);
				MANAGER_CHECK_RET(et_ret);
				g_et_state = MANAGER_STATE_PROCESS_CMD;
				break;
			}
        	if (MODBUS__Check_Receive(MODBUS_DEFAULT))
        	{
        		command.slave_addr = SLAVE_ADDRESS;
        		MODBUS__Get_Command(MODBUS_DEFAULT, &command);
        		switch (command.function_code) {
					case MODBUS_FUNCTION_CODES__READ_INPUT:
						et_aux_cmd = DEVICE_STATE_REPORT_DATA;
		        		ArrayList__Add(LIST_MANAGER_COMMANDS_WAITING, &et_aux_cmd);

						g_et_state = MANAGER_STATE_IDLE;
						break;
					default:
						break;
				}
        	}
        	break;

        case MANAGER_STATE_PROCESS_CMD:
        	et_ret = Manager_DEVICE__StateMachine(et_cmd);
			MANAGER_CHECK_RET(et_ret);
			if (g_et_device_process_status == DEVICE_PROCESS_STATUS__DONE)
			{
				g_et_state = MANAGER_STATE_IDLE;
				et_cmd = DEVICE_CMD__NONE;
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
static et_RET Manager_DEVICE__StateMachine(et_DEVICE_CMD et_cmd)
{
    et_RET et_ret = RET_UNEXPECTED;
    static uint8_t state_idx = 0;
    static uint8_t msg_size = 0;
    static uint8_t MODBUS_msg[MAX_MODBUS_MSG_SIZE] = {};
    static et_MODBUS_FUNCTION_CODES function_code = MODBUS_FUNCTION_CODES__NONE;
    static uint16_t data = 0;

    switch (DEVICE_STATE_vec[et_cmd][state_idx])
    {
        case DEVICE_CMD_STATE__INIT:
            CENTI_DEBUG__Info("Device initialization");
            g_et_device_process_status = DEVICE_PROCESS_STATUS__PROCESSING;
            state_idx++;
            break;
        case DEVICE_CMD_STATE__READ_SENSOR:
            CENTI_DEBUG__Info("Collect data from sensors connected");
            /* random data */
            data = 0x0145;
            state_idx++;
			break;
        case DEVICE_CMD_STATE__RECEIVE_CMD:
            CENTI_DEBUG__Info("Device received command");
            function_code = MODBUS_FUNCTION_CODES__READ_INPUT;
            state_idx++;
            break;
        case DEVICE_CMD_STATE__PROCESS_DATA:
        	CENTI_DEBUG__Info("Device processing data");
        	state_idx++;
        	break;
        case DEVICE_CMD_STATE__REPORT_DATA:
            CENTI_DEBUG__Info("Device reporting data");

            function_code = MODBUS_FUNCTION_CODES__READ_INPUT;

            DEVICE__Build_Data_Message (MODBUS_msg, function_code, data, &msg_size);
            MODBUS__Send_Response(MODBUS_DEFAULT, MODBUS_msg, msg_size);
            state_idx++;
            break;
        case DEVICE_CMD_STATE__DONE:
            CENTI_DEBUG__Info("Device done");
            g_et_device_process_status = DEVICE_PROCESS_STATUS__DONE;
            state_idx = 0;
            break;
        default:
            state_idx = 0;
            break;
    }
    return RET_OK;
}


static bool Manager__NewCommandAvailable(void)
{
	bool counter = FLAG_OFF;

    (ArrayList__Get_ElementCounter(LIST_MANAGER_COMMANDS_WAITING) > 0) ? (counter = FLAG_ON) : (counter = FLAG_OFF);
    return counter;
}


static et_RET Manager__GetCommand(et_DEVICE_CMD *et_cmd)
{
    et_RET et_ret = RET_UNEXPECTED;
	et_ret = ArrayList__Get(LIST_MANAGER_COMMANDS_WAITING, 0, et_cmd);
	MANAGER_CHECK_RET(et_ret);
	et_ret = ArrayList__RemoveAt(LIST_MANAGER_COMMANDS_WAITING, 0);
	MANAGER_CHECK_RET(et_ret);
    return RET_OK;
}

static void DEVICE__Build_Data_Message (uint8_t *MODBUS_msg, et_MODBUS_FUNCTION_CODES function_code, uint16_t data, uint8_t *msg_size)
{
	// verificar se comando válido ou excepção
	*msg_size = 0;
	MODBUS_msg[(*msg_size)++] = SLAVE_ADDRESS;
	MODBUS_msg[(*msg_size)++] = function_code;
	MODBUS_msg[(*msg_size)++] = sizeof(data);
	MODBUS_msg[(*msg_size)++] = ((data >> 8) & 0xFF);
	MODBUS_msg[(*msg_size)++] = (data & 0xFF);


}


/* -- End of file -- */
