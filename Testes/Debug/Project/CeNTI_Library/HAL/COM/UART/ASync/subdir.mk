################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_0_ASync.c \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_1_ASync.c \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_2_ASync.c \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_3_ASync.c \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_4_ASync.c \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_5_ASync.c \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_6_ASync.c \
../Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_7_ASync.c 

OBJS += \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_0_ASync.o \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_1_ASync.o \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_2_ASync.o \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_3_ASync.o \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_4_ASync.o \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_5_ASync.o \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_6_ASync.o \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_7_ASync.o 

C_DEPS += \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_0_ASync.d \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_1_ASync.d \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_2_ASync.d \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_3_ASync.d \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_4_ASync.d \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_5_ASync.d \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_6_ASync.d \
./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_7_ASync.d 


# Each subdirectory must supply rules for building sources it contributes
Project/CeNTI_Library/HAL/COM/UART/ASync/%.o Project/CeNTI_Library/HAL/COM/UART/ASync/%.su Project/CeNTI_Library/HAL/COM/UART/ASync/%.cyclo: ../Project/CeNTI_Library/HAL/COM/UART/ASync/%.c Project/CeNTI_Library/HAL/COM/UART/ASync/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-UART-2f-ASync

clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-UART-2f-ASync:
	-$(RM) ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_0_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_0_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_0_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_0_ASync.su ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_1_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_1_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_1_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_1_ASync.su ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_2_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_2_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_2_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_2_ASync.su ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_3_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_3_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_3_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_3_ASync.su ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_4_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_4_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_4_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_4_ASync.su ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_5_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_5_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_5_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_5_ASync.su ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_6_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_6_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_6_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_6_ASync.su ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_7_ASync.cyclo ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_7_ASync.d ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_7_ASync.o ./Project/CeNTI_Library/HAL/COM/UART/ASync/CeNTI_UART_7_ASync.su

.PHONY: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-UART-2f-ASync

