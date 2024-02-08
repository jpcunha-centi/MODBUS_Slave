################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/Manager/Manager.c 

OBJS += \
./Project/Manager/Manager.o 

C_DEPS += \
./Project/Manager/Manager.d 


# Each subdirectory must supply rules for building sources it contributes
Project/Manager/%.o Project/Manager/%.su Project/Manager/%.cyclo: ../Project/Manager/%.c Project/Manager/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-Manager

clean-Project-2f-Manager:
	-$(RM) ./Project/Manager/Manager.cyclo ./Project/Manager/Manager.d ./Project/Manager/Manager.o ./Project/Manager/Manager.su

.PHONY: clean-Project-2f-Manager

