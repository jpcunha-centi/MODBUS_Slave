/*
 * Path:    Project/Devices/MODBUS/
 * File:    MODBUS.c
 * Author:  João Cunha
 *
 * Created on 08/01/2024
 * Modified on 08/01/2024
 */


/* ************************************************************************************ */
/* * Device in use                                                                    * */
/* ************************************************************************************ */
#include "../../Defines/MODBUS_defines.h"
#if (defined(__MODBUS_IN_USE__))


/* ************************************************************************************ */
/* * Private Includes                                                                 * */
/* ************************************************************************************ */
#include "MODBUS.h"


/* ************************************************************************************ */
/* * Private Defines                                                                  * */
/* ************************************************************************************ */
#define FUNCTION_CODES_SIZE (15)
#define REGISTERS_SIZE (20)

#define MODBUS_MAX_SIZE (30)


/* ************************************************************************************ */
/* * Timers                                                                           * */
/* ************************************************************************************ */
# if (defined(__CENTI_TIME_IN_USE__))

    static const st_TIME ST_MODBUS_TIMEOUT = { .sec = 0, .msec = 35 };

#endif


/* ************************************************************************************ */
/* * Flags (Add desired flags here)                                                   * */
/* ************************************************************************************ */
#if (defined(__CENTI_SOFTTIMER_IN_USE__))

	static t_FLAG f_MODBUS_TIMEOUT = FLAG_OFF;

    #define FOREACH_FLAG(FLAG)\
    FLAG (FLAG_MODBUS_TIMOUT, SOFTTIMER_INSTANCE_MODBUS_TIMEOUT  , f_MODBUS_TIMEOUT)\


/* ************************************************************************************ */
/* * SoftTimer Flags                                                                  * */
/* ************************************************************************************ */

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
/* Device configuration. */
static const st_MODBUS_CONFIGURATION ST_CONF[MODBUS_TOTAL] = \
    { FOREACH_MODBUS(GENERATE_MODBUS_CONF) };

/* ************************************************************************************ */
/* * Private Global Variables                                                         * */
/* ************************************************************************************ */
/* Indication if initialization procedure was successful. */
static bool g_initialized[MODBUS_TOTAL] = {};


#if (defined(__MODBUS_AS_SLAVE__))

uint8_t vec_function_codes[FUNCTION_CODES_SIZE] = {};
uint16_t vec_registers[REGISTERS_SIZE] = {};

/* ************************************************************************************ */
/* * Private Functions Prototypes		                                              * */
/* ************************************************************************************ */

static et_RET MODBUS_Slave__ARRAYLIST_Function_Codes_Init (void);
static et_RET MODBUS_Slave__ARRAYLIST_Registers_Init (void);

bool MODBUS_Slave__Check_Valid_Function_Code (uint8_t function_code);
bool MODBUS_Slave__Check_Valid_Register_Address (uint16_t register_addr);

static bool MODBUS__function_code_Cmp (const void *elem1, const void *elem2);
static bool MODBUS__register_Cmp (const void *elem1, const void *elem2);

#endif /* (defined(__MODBUS_AS_SLAVE__)) */

static uint16_t MODBUS__Calc_CRC(uint8_t *vec, uint8_t size);


/* ************************************************************************************ */
/* * Communication Functions Prototypes                                               * */
/* ************************************************************************************ */
static et_RET COM__Write(et_MODBUS et_dev, uint8_t *vec, uint8_t size);
static et_RET COM__Read(et_MODBUS et_dev, uint8_t *vec);



/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
et_RET MODBUS__Initialize(et_MODBUS et_dev)
{
    et_RET et_ret = RET_UNEXPECTED;

    /* Entering debug message. */
    CENTI_DEBUG__Info("MODBUS initialization started!");
    /* Priority tasks. */
    CENTI_CHECK_PTR(ST_CONF[et_dev].uart__Initialize);
    CENTI_CHECK_PTR(ST_CONF[et_dev].uart__Write);
    CENTI_CHECK_PTR(ST_CONF[et_dev].uart__Read);
    CENTI_CHECK_PTR(ST_CONF[et_dev].uart__GetRemain);
    CENTI_CHECK_PTR(ST_CONF[et_dev].gpio__Setlevel);
    CENTI_CHECK_PTR(ST_CONF[et_dev].delay__ms);
    et_ret = ST_CONF[et_dev].uart__Initialize();
    CENTI_CHECK_RET(et_ret);
    ST_CONF[et_dev].gpio__Setlevel(MODBUS_MODE_READ);

#if (defined(__MODBUS_AS_SLAVE__))
    et_ret = MODBUS_Slave__ARRAYLIST_Function_Codes_Init ();
    CENTI_CHECK_RET(et_ret);
	et_ret = MODBUS_Slave__ARRAYLIST_Registers_Init ();
	CENTI_CHECK_RET(et_ret);
#endif /* (defined(__MODBUS_AS_SLAVE__)) */

    /* Indicate that initialization was successfully complete. */
    g_initialized[et_dev] = true;
    /* Exiting debug message. */
    CENTI_DEBUG__Info("MODBUS initialization complete!");
    return RET_OK;
}

#if (defined(__MODBUS_AS_SLAVE__))

static et_RET MODBUS_Slave__ARRAYLIST_Function_Codes_Init (void)
{
	et_RET et_ret = RET_UNEXPECTED;
	uint8_t aux_function_code = 0;

	et_ret = ArrayList__Initialize(LIST_FUNCTION_CODES, vec_function_codes, FUNCTION_CODES_SIZE, sizeof(vec_function_codes[0]), MODBUS__function_code_Cmp);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = READ_COIL;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = READ_DISCRETE_INPUT;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = READ_MULTIPLE_HOLDING_REGS;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = READ_INPUT;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = WRITE_SINGLE_COIL;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = WRITE_SINGLE_REG;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = WRITE_MULTIPLE_COILS;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);
	aux_function_code = WRITE_MULTIPLE_HOLDING_REG;
	et_ret =  ArrayList__Add(LIST_FUNCTION_CODES, &aux_function_code);
	CENTI_CHECK_RET(et_ret);

	return RET_OK;
}

static et_RET MODBUS_Slave__ARRAYLIST_Registers_Init (void)
{
	et_RET et_ret = RET_UNEXPECTED;
	uint16_t aux_register = 0;

	et_ret = ArrayList__Initialize(LIST_REGISTERS, vec_registers, REGISTERS_SIZE, sizeof(vec_registers[0]), MODBUS__register_Cmp);
	CENTI_CHECK_RET(et_ret);
	aux_register = MODBUS_REG_0101;
	et_ret =  ArrayList__Add(LIST_REGISTERS, &aux_register);
	CENTI_CHECK_RET(et_ret);
	aux_register = MODBUS_REG_0202;
	et_ret =  ArrayList__Add(LIST_REGISTERS, &aux_register);
	CENTI_CHECK_RET(et_ret);
	aux_register = MODBUS_REG_0303;
	et_ret =  ArrayList__Add(LIST_REGISTERS, &aux_register);
	CENTI_CHECK_RET(et_ret);
	aux_register = MODBUS_REG_0A0A;
	et_ret =  ArrayList__Add(LIST_REGISTERS, &aux_register);
	CENTI_CHECK_RET(et_ret);

	return RET_OK;
}

bool MODBUS_Slave__Check_Valid_Function_Code (uint8_t function_code)
{
	et_RET et_ret = RET_UNEXPECTED;
	size_t aux = 0;

	et_ret = ArrayList__Search(LIST_FUNCTION_CODES, &function_code, &aux);
	if(et_ret == RET_OK)
	{
		return FLAG_ON;
	}
	else
	{
		return FLAG_OFF;
	}
}

bool MODBUS_Slave__Check_Valid_Register_Address (uint16_t register_addr)
{
	et_RET et_ret = RET_UNEXPECTED;
	size_t aux = 0;

	et_ret = ArrayList__Search(LIST_REGISTERS, &register_addr, &aux);
	if(et_ret == RET_OK)
	{
		return FLAG_ON;
	}
	else
	{
		return FLAG_OFF;
	}
}

bool MODBUS_Slave__Check_Valid_Message (uint8_t *MODBUS_Msg, uint8_t size)
{
	if (!MODBUS__Check_CRC(MODBUS_Msg, size))
	{
		return false;
	}
	if (!MODBUS_Slave__Check_Valid_Function_Code(MODBUS_Msg[1])){
		return false;
	}
	if (!MODBUS_Slave__Check_Valid_Register_Address((uint16_t)((MODBUS_Msg[2] << 8) + MODBUS_Msg[3])))
	{
		return false;
	}
	return true;
}

void MODBUS_Slave__Parser_Command (uint8_t *MODBUS_Msg, st_MODBUS_COMMAND *command)
{
	uint8_t idx = 0;

	command->slave_addr = 							MODBUS_Msg[idx++];
	command->function_code = 						MODBUS_Msg[idx++];
	command->register_addr.ut_high_u1B.value_u8 = 	MODBUS_Msg[idx++];
	command->register_addr.ut_low_u1B.value_u8 = 	MODBUS_Msg[idx++];
	command->size.ut_high_u1B.value_u8 = 			MODBUS_Msg[idx++];
	command->size.ut_low_u1B.value_u8 = 			MODBUS_Msg[idx++];

}

#elif (defined(__MODBUS_AS_MASTER__))

et_RET MODBUS_Master__Send_Command(et_MODBUS et_dev, st_MODBUS_COMMAND command)
{
    et_RET et_ret = RET_UNEXPECTED;
    uint8_t vec_command[MODBUS_MAX_SIZE] = {};
    uint8_t idx = 0;
    uint16_t crc = 0;

    /* Entering debug message. */
    CENTI_DEBUG__Info("MODBUS Send Request!");
    vec_command[idx++] = command.slave_addr;
    vec_command[idx++] = command.function_code;
    vec_command[idx++] = command.register_addr.ut_high_u1B.value_u8;
    vec_command[idx++] = command.register_addr.ut_low_u1B.value_u8;
    vec_command[idx++] = command.size.ut_high_u1B.value_u8;
    vec_command[idx++] = command.size.ut_low_u1B.value_u8;
    crc = MODBUS__Calc_CRC(vec_command, idx);
    vec_command[idx++] = ((crc >> 8) & 0xFF);
    vec_command[idx++] = (crc & 0xFF);
    et_ret = COM__Write(et_dev, vec_command, idx);
    CENTI_CHECK_RET(et_ret);
    CENTI_DEBUG__Info("MODBUS Send Request finished!");
    return RET_OK;
}

et_RET MODBUS_Master__Send_Command_Write(et_MODBUS et_dev, st_MODBUS_COMMAND_WRITE command)
{
    et_RET et_ret = RET_UNEXPECTED;
    uint8_t vec_command[MODBUS_MAX_SIZE] = {};
    uint8_t idx = 0;
    uint16_t crc = 0;

    /* Entering debug message. */
    CENTI_DEBUG__Info("MODBUS Send Request!");
    vec_command[idx++] = command.slave_addr;
    vec_command[idx++] = command.function_code;
    vec_command[idx++] = command.register_addr.ut_high_u1B.value_u8;
    vec_command[idx++] = command.register_addr.ut_low_u1B.value_u8;
    vec_command[idx++] = command.register_value.ut_high_u1B.value_u8;
    vec_command[idx++] = command.register_value.ut_low_u1B.value_u8;
    crc = MODBUS__Calc_CRC(vec_command, idx);
    vec_command[idx++] = ((crc >> 8) & 0xFF);
    vec_command[idx++] = (crc & 0xFF);
    et_ret = COM__Write(et_dev, vec_command, idx);
    CENTI_CHECK_RET(et_ret);
    CENTI_DEBUG__Info("MODBUS Send Request finished!");
    return RET_OK;
}

et_RET MODBUS_Master__Get_Response(et_MODBUS et_dev, st_MODBUS_RESPONSE *response)
{
    et_RET et_ret = RET_UNEXPECTED;
    uint8_t vec_response[MODBUS_MAX_SIZE] = {};
    uint8_t msg_size = 0;
    CENTI_CHECK_PTR(response);

    et_ret = MODBUS__Receive (et_dev, vec_response, &msg_size);
	if (et_ret != RET_OK)
	{
		return RET_INVALID_OPERATION;
	}
	else
	{
		if(!MODBUS__Check_CRC(vec_response, msg_size))
		{
			CENTI_DEBUG__Error("Response with checksum incorrect");
			et_ret = RET_INVALID_PARAMETER;
		}
		CENTI_CHECK_RET(et_ret);
		if(vec_response[0] != response-> slave_addr)
		{
			CENTI_DEBUG__Error("Response with wrong slave address %02X", vec_response[0]);
			CENTI_DEBUG__Verbose("Expected slave addr %02X", response-> slave_addr);
			et_ret = RET_INVALID_PARAMETER;
		}
		CENTI_CHECK_RET(et_ret);
		if(vec_response[1] >= 0x80)
		{
			CENTI_DEBUG__Error("Response with a exception value, request no complete");
			et_ret = RET_INVALID_OPERATION;
		}
		CENTI_CHECK_RET(et_ret);
		response->slave_addr                    = vec_response[0];
		response->function_code                 = vec_response[1];
		response->size                          = vec_response[2];
		response->data.ut_low_u1B.value_u8      = vec_response[3];
		response->data.ut_high_u1B.value_u8     = vec_response[4];
		response->crc_16.ut_low_u1B.value_u8    = vec_response[5];
		response->crc_16.ut_high_u1B.value_u8   = vec_response[6];
		CENTI_DEBUG__Verbose("slave_addr:0x%02X", 	 response->slave_addr);
		CENTI_DEBUG__Verbose("function_code:0x%02X", response->function_code);
		CENTI_DEBUG__Verbose("size:0x%02X", 		 response->size);
		CENTI_DEBUG__Verbose("data:0x%04X", 		 response->data.value_u16);
		CENTI_DEBUG__Verbose("crc:0x%04X", 			 response->crc_16.value_u16);
	}
    return RET_OK;
}

et_RET MODBUS_Master__Get_Echo(et_MODBUS et_dev)
{
    et_RET et_ret = RET_UNEXPECTED;
    uint8_t vec_echo[MODBUS_MAX_SIZE] = {};
    uint8_t msg_size = 0;

    ST_CONF[et_dev].delay__ms(50);
    CENTI_CHECK_RET(et_ret);
    et_ret = MODBUS__Receive (et_dev, vec_echo, &msg_size);
	CENTI_CHECK_RET(et_ret);
	(vec_echo[1] > 0x80) ? (et_ret = RET_FAIL) : (et_ret = RET_OK);
	CENTI_CHECK_RET(et_ret);
	return RET_OK;
}

#else
	#error Not defined!


#endif


bool MODBUS__Check_CRC(uint8_t *vec, uint8_t size)
{
	uint16_t crc = 0xFFFF;
	uint16_t aux_crc = 0;
	bool valid_crc = FLAG_OFF;

	crc = MODBUS__Calc_CRC(vec, size - 2);
	aux_crc = ((vec[size - 2] & 0xFF) << 8);
	aux_crc |= (vec[size - 1] & 0xFF);
	CENTI_DEBUG__Verbose("Expected crc: %04X", crc);
	CENTI_DEBUG__Verbose("Received crc: %04X", aux_crc);
	(aux_crc == crc) ? (valid_crc = FLAG_ON) : (valid_crc = FLAG_OFF);

	return valid_crc;
}


/* ************************************************************************************ */
/* * Private Functions                                                       	      * */
/* ************************************************************************************ */

static uint16_t MODBUS__Calc_CRC(uint8_t *vec, uint8_t size)
{
	uint16_t aux_crc = 0xFFFF;
	uint16_t crc = 0;
	uint8_t j;

	for (j = 0; j < size; j++)
	{
		aux_crc ^= vec[j];
		for (uint8_t i = 0; i < 8; i++)
		{
			if (aux_crc & 0x01)
			{
				aux_crc >>= 1;
				aux_crc ^= 0xA001;
			}
			else
				aux_crc >>= 1;
		}
	}
	crc = ((aux_crc & 0xFF) << 8);
	crc |= ((aux_crc >> 8) & 0xFF);
	return crc;
}

static bool MODBUS__function_code_Cmp (const void *elem1, const void *elem2)
{
	if((*(uint8_t *) elem1) == (*(uint8_t *) elem2))
		return true;
	else
		return false;
}

static bool MODBUS__register_Cmp (const void *elem1, const void *elem2)
{
	if((*(uint16_t *) elem1) == (*(uint16_t *) elem2))
		return true;
	else
		return false;
}


/* ************************************************************************************ */
/* * Communication Functions                                                          * */
/* ************************************************************************************ */

et_RET MODBUS__Send (et_MODBUS et_dev, uint8_t *MODBUS_msg, uint8_t msg_size)
{
	et_RET et_ret = RET_UNEXPECTED;
	uint16_t crc = 0;

    crc = MODBUS__Calc_CRC(MODBUS_msg, msg_size);
    MODBUS_msg[msg_size++] = ((crc >> 8) & 0xFF);
    MODBUS_msg[msg_size++] = (crc & 0xFF);
    CENTI_DEBUG__Info("MODBUS Send Started!");
    et_ret = COM__Write(et_dev, MODBUS_msg, msg_size);
    CENTI_CHECK_RET(et_ret);
    CENTI_DEBUG__Info("MODBUS Send Finished!");

	return RET_OK;
}

et_RET MODBUS__Receive (et_MODBUS et_dev, uint8_t *MODBUS_msg, uint8_t *msg_size)
{
	et_RET et_ret = RET_UNEXPECTED;

	CENTI_CHECK_PTR(MODBUS_msg);
	CENTI_CHECK_PTR(msg_size);

	et_MODBUS_STATE g_et_modbus_state = MODBUS_STATE__IDLE;

	while(ST_CONF[et_dev].uart__GetRemain() > 0)
    {
    	switch(g_et_modbus_state)
		{
			case MODBUS_STATE__IDLE:
		        CENTI_DEBUG__Info("MODBUS Received Started!");
				g_et_modbus_state = MODBUS_STATE__INIT;

			case MODBUS_STATE__INIT:
				CENTI_DEBUG__Verbose("MODBUS Rx command state: Initialize");
				for(uint8_t i = 0; i < MODBUS_MAX_SIZE; i++)
				{
					MODBUS_msg[i] = '\0';
				}
				*msg_size = 0;
				SoftTimer__Start(SOFTTIMER_INSTANCE_MODBUS_TIMEOUT, ST_MODBUS_TIMEOUT);
				f_MODBUS_TIMEOUT = FLAG_OFF;

				g_et_modbus_state = MODBUS_STATE__GET_MSG;

			case MODBUS_STATE__GET_MSG:
				UART_1_RingBuffer__Read(&(MODBUS_msg[(*msg_size)]), 1);
				CENTI_DEBUG__Verbose("MODBUS Rx command byte: 0x%02X", MODBUS_msg[*msg_size]);
				CENTI_DEBUG__Verbose("size: %d", *msg_size);
				SoftTimer__Restart(SOFTTIMER_INSTANCE_MODBUS_TIMEOUT);

				(*msg_size)++;
				// vec size
				if (*msg_size >= MODBUS_MAX_SIZE)
				{
					*msg_size = 0;
					CENTI_DEBUG__Verbose("MODBUS Rx command oversized");
					g_et_modbus_state = MODBUS_STATE__ERROR;
					break;
				}
				break;
			default:
				CENTI_DEBUG__Verbose("MODBUS Rx command in default state");
				g_et_modbus_state = MODBUS_STATE__ERROR;
				break;
		}
		if (g_et_modbus_state == MODBUS_STATE__ERROR)
		{
			*msg_size = 0;
			CENTI_DEBUG__Verbose("MODBUS Rx command entering error state");
			UART_1_RingBuffer__ClearRxFIFO();
			SoftTimer__Stop(SOFTTIMER_INSTANCE_MODBUS_TIMEOUT);
			f_MODBUS_TIMEOUT = FLAG_OFF;
			break;
		}
    }
	// timeout
	if(f_MODBUS_TIMEOUT == FLAG_ON)
	{
		SoftTimer__Stop(SOFTTIMER_INSTANCE_MODBUS_TIMEOUT);
		f_MODBUS_TIMEOUT = FLAG_OFF;
		CENTI_DEBUG__Verbose("MODBUS Rx command timeout");
		g_et_modbus_state = MODBUS_STATE__COMPLETE;
	}
	// command complete
	if (g_et_modbus_state == MODBUS_STATE__COMPLETE)
	{
		g_et_modbus_state = MODBUS_STATE__IDLE;
		CENTI_DEBUG__Verbose("size: %d", *msg_size);
		if (MODBUS__Check_CRC(MODBUS_msg, *msg_size)) /////// check here
		{
			CENTI_DEBUG__Info("MODBUS Rx command: Complete command!");

			for (uint8_t i=0; i<*msg_size; i++)
			{
				CENTI_DEBUG__Verbose("0x%02X", MODBUS_msg[i]);
			}
			et_ret = RET_OK;
		}
		else
		{
			CENTI_DEBUG__Info("MODBUS Rx command: Invalid command! Ignoring...");
			g_et_modbus_state = MODBUS_STATE__ERROR;
		}
	}
	if (g_et_modbus_state == MODBUS_STATE__ERROR)
	{
		CENTI_DEBUG__Warning("MODBUS Rx command Error!");
		g_et_modbus_state = MODBUS_STATE__IDLE;
		return RET_INVALID_STATE;
	}
	return et_ret;
}

static et_RET COM__Write(et_MODBUS et_dev, uint8_t *vec, uint8_t size)
{
    et_RET et_ret = RET_UNEXPECTED;
    CENTI_CHECK_PTR(vec);
	ST_CONF[et_dev].gpio__Setlevel(MODBUS_MODE_WRITE);
	et_ret = ST_CONF[et_dev].uart__Write(vec, size);
	CENTI_CHECK_RET(et_ret);
	ST_CONF[et_dev].gpio__Setlevel(MODBUS_MODE_READ);
	return RET_OK;
}

static et_RET COM__Read(et_MODBUS et_dev, uint8_t *vec)
{
    et_RET et_ret = RET_UNEXPECTED;
    CENTI_CHECK_PTR(vec);
	ST_CONF[et_dev].gpio__Setlevel(MODBUS_MODE_READ);
	et_ret = ST_CONF[et_dev].uart__Read(vec, 1);
	CENTI_CHECK_RET(et_ret);
	return RET_OK;
}


#endif /* (defined(__MODBUS_IN_USE__)) */

/* -- End of file -- */
