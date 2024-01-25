################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/CeNTI_Library/lib/Debug/CeNTI_Debug.c 

OBJS += \
./Project/CeNTI_Library/lib/Debug/CeNTI_Debug.o 

C_DEPS += \
./Project/CeNTI_Library/lib/Debug/CeNTI_Debug.d 


# Each subdirectory must supply rules for building sources it contributes
Project/CeNTI_Library/lib/Debug/%.o Project/CeNTI_Library/lib/Debug/%.su Project/CeNTI_Library/lib/Debug/%.cyclo: ../Project/CeNTI_Library/lib/Debug/%.c Project/CeNTI_Library/lib/Debug/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-CeNTI_Library-2f-lib-2f-Debug

clean-Project-2f-CeNTI_Library-2f-lib-2f-Debug:
	-$(RM) ./Project/CeNTI_Library/lib/Debug/CeNTI_Debug.cyclo ./Project/CeNTI_Library/lib/Debug/CeNTI_Debug.d ./Project/CeNTI_Library/lib/Debug/CeNTI_Debug.o ./Project/CeNTI_Library/lib/Debug/CeNTI_Debug.su

.PHONY: clean-Project-2f-CeNTI_Library-2f-lib-2f-Debug

