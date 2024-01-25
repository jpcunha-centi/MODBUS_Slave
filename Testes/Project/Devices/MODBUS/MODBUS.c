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
#define COMMAND_SIZE  (8)
#define RESPONSE_SIZE (7)


/* ************************************************************************************ */
/* * Private Constant Variables                                                       * */
/* ************************************************************************************ */
/* Device configuration. */
static const st_MODBUS_conf ST_CONF[MODBUS_TOTAL] = \
    { FOREACH_MODBUS(GENERATE_MODBUS_CONF) };


/* ************************************************************************************ */
/* * Private Global Variables                                                         * */
/* ************************************************************************************ */
/* Indication if initialization procedure was successful. */
static bool g_initialized[MODBUS_TOTAL] = {};

/* ************************************************************************************ */
/* * Private Functions Prototypes		                                              * */
/* ************************************************************************************ */

static uint16_t MODBUS__Calc_CRC(uint8_t *vec, uint8_t size);
static bool MODBUS__Check_CRC(uint8_t *vec, uint8_t size);

/* ************************************************************************************ */
/* * Communication Functions Prototypes                                               * */
/* ************************************************************************************ */
static et_RET COM__Write(et_MODBUS et_dev, uint8_t *vec, uint8_t size);
static et_RET COM__Read(et_MODBUS et_dev, uint8_t *vec, uint8_t size);


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
    HAL_Delay(1000);
    /* Indicate that initialization was successfully complete. */
    g_initialized[et_dev] = true;
    /* Exiting debug message. */
    CENTI_DEBUG__Info("MODBUS initialization complete!");
    return RET_OK;
}

et_RET MODBUS__Send_Response(et_MODBUS et_dev, uint8_t *MODBUS_msg, uint8_t msg_size)
{
    et_RET et_ret = RET_UNEXPECTED;
    uint16_t crc = 0;

    /* Entering debug message. */
    CENTI_DEBUG__Info("MODBUS Send RESPONSE!");

    crc = MODBUS__Calc_CRC(MODBUS_msg, msg_size);
    MODBUS_msg[msg_size + 1] = ((crc >> 8) & 0xFF);
    MODBUS_msg[msg_size + 2] = (crc & 0xFF);
    et_ret = COM__Write(et_dev, MODBUS_msg, (msg_size + 2));
    CENTI_CHECK_RET(et_ret);
    CENTI_DEBUG__Info("MODBUS Send Request finished!");
    return RET_OK;
}

et_RET MODBUS__Send_Command_Write(et_MODBUS et_dev, st_MODBUS_COMMAND_WRITE command)
{
    et_RET et_ret = RET_UNEXPECTED;
    uint8_t vec_command[COMMAND_SIZE] = {};
    uint16_t crc = 0;

    /* Entering debug message. */
    CENTI_DEBUG__Info("MODBUS Send Request!");
    vec_command[0] = command.slave_addr;
    vec_command[1] = command.function_code;
    vec_command[2] = command.register_addr.ut_high_u1B.value_u8;
    vec_command[3] = command.register_addr.ut_low_u1B.value_u8;
    vec_command[4] = command.register_value.ut_high_u1B.value_u8;
    vec_command[5] = command.register_value.ut_low_u1B.value_u8;
    crc = MODBUS__Calc_CRC(vec_command, 6);
    vec_command[6] = ((crc >> 8) & 0xFF);
    vec_command[7] = (crc & 0xFF);
    et_ret = COM__Write(et_dev, vec_command, COMMAND_SIZE);
    CENTI_CHECK_RET(et_ret);
    CENTI_DEBUG__Info("MODBUS Send Request finished!");
    return RET_OK;
}

bool MODBUS__Check_Receive (et_MODBUS et_dev)
{
	bool received = FLAG_OFF;
	(ST_CONF[et_dev].uart__GetRemain() >= COMMAND_SIZE) ? (received = FLAG_ON) : (received = FLAG_OFF);
	return received;
}

et_RET MODBUS__Get_Command(et_MODBUS et_dev, st_MODBUS_COMMAND *command)
{
    et_RET et_ret = RET_UNEXPECTED;
    uint8_t vec_received[COMMAND_SIZE] = {};
    CENTI_CHECK_PTR(command);

    ST_CONF[et_dev].delay__ms(50);
    if(ST_CONF[et_dev].uart__GetRemain() >= COMMAND_SIZE)
    {
    	et_ret = RET_OK;
    }
    else
    {
    	ST_CONF[et_dev].uart__ClearRxFifo();
    	CENTI_DEBUG__Error("Response not received");
    	et_ret = RET_INVALID_OPERATION;
    }
	CENTI_CHECK_RET(et_ret);
	et_ret = COM__Read(et_dev, vec_received, COMMAND_SIZE);
	CENTI_CHECK_RET(et_ret);

	if(!MODBUS__Check_CRC(vec_received, COMMAND_SIZE))
	{
    	CENTI_DEBUG__Error("Response with checksum incorrect");
    	et_ret = RET_INVALID_PARAMETER;
	}
	CENTI_CHECK_RET(et_ret);
	if(vec_received[0] != command-> slave_addr)
	{
		CENTI_DEBUG__Error("Response with wrong slave address %02X", vec_received[0]);
		CENTI_DEBUG__Verbose("Expected slave addr %02X", command-> slave_addr);
		et_ret = RET_INVALID_PARAMETER;
	}
	CENTI_CHECK_RET(et_ret);
	if(vec_received[1] >= 0x80)
	{
		CENTI_DEBUG__Error("Response with a exception value, request no complete");
		et_ret = RET_INVALID_OPERATION;
	}
	CENTI_CHECK_RET(et_ret);
	command->slave_addr                    		= vec_received[0];
	command->function_code                 		= vec_received[1];
	command->register_addr.ut_high_u1B.value_u8 = vec_received[2];
	command->register_addr.ut_low_u1B.value_u8	= vec_received[3];
	command->size.ut_high_u1B.value_u8			= vec_received[4];
	command->size.ut_low_u1B.value_u8			= vec_received[5];
	command->crc_16.ut_low_u1B.value_u8    		= vec_received[6];
	command->crc_16.ut_high_u1B.value_u8   		= vec_received[7];

	CENTI_DEBUG__Verbose("slave_addr:0x%02X", 		 		command->slave_addr);
	CENTI_DEBUG__Verbose("function_code:0x%02X", 			command->function_code);
	CENTI_DEBUG__Verbose("register:0x%04X",		 			command->register_addr.value_u16);
	CENTI_DEBUG__Verbose("size of expected data:0x%04X", 	command->size.value_u16);
	CENTI_DEBUG__Verbose("crc:0x%04X", 			 			command->crc_16.value_u16);
    return RET_OK;
}



/* ************************************************************************************ */
/* * Private Functions                                                          * */
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

static bool MODBUS__Check_CRC(uint8_t *vec, uint8_t size)
{
	uint16_t crc = 0xFFFF;
	uint16_t aux_crc = 0;
	bool valid_crc = FLAG_OFF;

	crc = MODBUS__Calc_CRC(vec, size - 2);
	aux_crc = ((vec[size - 2] & 0xFF) << 8);
	aux_crc |= (vec[size - 1] & 0xFF);
	(aux_crc == crc) ? (valid_crc = FLAG_ON) : (valid_crc = FLAG_OFF);

	return valid_crc;
}


/* ************************************************************************************ */
/* * Communication Functions                                                          * */
/* ************************************************************************************ */
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

static et_RET COM__Read(et_MODBUS et_dev, uint8_t *vec, uint8_t size)
{
    et_RET et_ret = RET_UNEXPECTED;
    CENTI_CHECK_PTR(vec);
	ST_CONF[et_dev].gpio__Setlevel(MODBUS_MODE_READ);
	et_ret = ST_CONF[et_dev].uart__Read(vec, size);
	CENTI_CHECK_RET(et_ret);
	return RET_OK;
}


#endif /* (defined(__MODBUS_IN_USE__)) */

/* -- End of file -- */
