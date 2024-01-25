################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/Devices/MODBUS/MODBUS.c 

OBJS += \
./Project/Devices/MODBUS/MODBUS.o 

C_DEPS += \
./Project/Devices/MODBUS/MODBUS.d 


# Each subdirectory must supply rules for building sources it contributes
Project/Devices/MODBUS/%.o Project/Devices/MODBUS/%.su Project/Devices/MODBUS/%.cyclo: ../Project/Devices/MODBUS/%.c Project/Devices/MODBUS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-Devices-2f-MODBUS

clean-Project-2f-Devices-2f-MODBUS:
	-$(RM) ./Project/Devices/MODBUS/MODBUS.cyclo ./Project/Devices/MODBUS/MODBUS.d ./Project/Devices/MODBUS/MODBUS.o ./Project/Devices/MODBUS/MODBUS.su

.PHONY: clean-Project-2f-Devices-2f-MODBUS

