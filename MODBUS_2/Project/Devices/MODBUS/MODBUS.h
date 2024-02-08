/*
 * Path:    Project/Devices/MODBUS/
 * File:    MODBUS.h
 * Author:  João Cunha
 *
 * Created on 08/01/2024
 * Modified on 08/01/2024
 */


#ifndef __PROJECT_DEVICES_MODBUS_MODBUS_H__
#define	__PROJECT_DEVICES_MODBUS_MODBUS_H__


/* ************************************************************************************ */
/* * Device in use                                                                    * */
/* ************************************************************************************ */
#include "../../Defines/MODBUS_defines.h"
#if (defined(__MODBUS_IN_USE__))


/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
#include "../../Configs/MODBUS_configs.h"


/* ************************************************************************************ */
/* * Public Functions                                                                 * */
/* ************************************************************************************ */
/**
 * @brief Initialize MODBUS API.
 *
 * @param[in]   et_dev  Device instance.
 *
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET MODBUS__Initialize(et_MODBUS et_dev);

#if (defined(__MODBUS_AS_MASTER__))
/**
 * @brief   Send a command.
 *
 * @param[in] 'et_dev'  Device instance.
 * @param[in] 'command' Command.
 *
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET MODBUS__Send_Command(et_MODBUS et_dev, st_MODBUS_COMMAND command);

et_RET MODBUS__Send_Command_Write(et_MODBUS et_dev, st_MODBUS_COMMAND_WRITE command);

/**
 * @brief   Receive a response.
 *
 * @param[in]   'et_dev'    Device instance.
 * @param[out]  'response'  Response.
 *
 * @return Indication if everything worked fine.
 * @retval  RET_OK  Everything worked fine.
 * @retval  Other   See et_RET.
 */
et_RET MODBUS__Get_Response(et_MODBUS et_dev, st_MODBUS_RESPONSE *response);

et_RET MODBUS__Get_Echo(et_MODBUS et_dev);

#elif (defined(__MODBUS_AS_SLAVE__))

bool MODBUS__Check_Valid_Message (uint8_t *MODBUS_Msg, uint8_t size);

void MODBUS__Parser_Command (uint8_t *MODBUS_Msg, st_MODBUS_COMMAND *command);

#endif /* (defined(__MODBUS_AS_SLAVE__)) */

bool MODBUS__Check_CRC(uint8_t *vec, uint8_t size);


et_RET MODBUS__Send(et_MODBUS et_dev, uint8_t *MODBUS_msg, uint8_t msg_size);

et_RET MODBUS__Receive (et_MODBUS et_dev, uint8_t *MODBUS_msg, uint8_t *msg_size);


#endif /* (defined(__MODBUS_IN_USE__)) */

#endif	/* __PROJECT_DEVICES_MODBUS_MODBUS_H__ */

/* -- End of file -- */
