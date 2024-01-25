################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/CeNTI_Library/lib/SoftTimer/CeNTI_SoftTimer.c 

OBJS += \
./Project/CeNTI_Library/lib/SoftTimer/CeNTI_SoftTimer.o 

C_DEPS += \
./Project/CeNTI_Library/lib/SoftTimer/CeNTI_SoftTimer.d 


# Each subdirectory must supply rules for building sources it contributes
Project/CeNTI_Library/lib/SoftTimer/%.o Project/CeNTI_Library/lib/SoftTimer/%.su Project/CeNTI_Library/lib/SoftTimer/%.cyclo: ../Project/CeNTI_Library/lib/SoftTimer/%.c Project/CeNTI_Library/lib/SoftTimer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-CeNTI_Library-2f-lib-2f-SoftTimer

clean-Project-2f-CeNTI_Library-2f-lib-2f-SoftTimer:
	-$(RM) ./Project/CeNTI_Library/lib/SoftTimer/CeNTI_SoftTimer.cyclo ./Project/CeNTI_Library/lib/SoftTimer/CeNTI_SoftTimer.d ./Project/CeNTI_Library/lib/SoftTimer/CeNTI_SoftTimer.o ./Project/CeNTI_Library/lib/SoftTimer/CeNTI_SoftTimer.su

.PHONY: clean-Project-2f-CeNTI_Library-2f-lib-2f-SoftTimer

