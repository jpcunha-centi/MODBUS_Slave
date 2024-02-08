################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_0_RingBuffer.c \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_1_RingBuffer.c \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_2_RingBuffer.c \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_3_RingBuffer.c \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_4_RingBuffer.c \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_5_RingBuffer.c \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_6_RingBuffer.c \
../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_7_RingBuffer.c 

OBJS += \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_0_RingBuffer.o \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_1_RingBuffer.o \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_2_RingBuffer.o \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_3_RingBuffer.o \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_4_RingBuffer.o \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_5_RingBuffer.o \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_6_RingBuffer.o \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_7_RingBuffer.o 

C_DEPS += \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_0_RingBuffer.d \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_1_RingBuffer.d \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_2_RingBuffer.d \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_3_RingBuffer.d \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_4_RingBuffer.d \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_5_RingBuffer.d \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_6_RingBuffer.d \
./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_7_RingBuffer.d 


# Each subdirectory must supply rules for building sources it contributes
Project/CeNTI_Library/HAL/COM/UART/RingBuffer/%.o Project/CeNTI_Library/HAL/COM/UART/RingBuffer/%.su Project/CeNTI_Library/HAL/COM/UART/RingBuffer/%.cyclo: ../Project/CeNTI_Library/HAL/COM/UART/RingBuffer/%.c Project/CeNTI_Library/HAL/COM/UART/RingBuffer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-UART-2f-RingBuffer

clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-UART-2f-RingBuffer:
	-$(RM) ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_0_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_0_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_0_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_0_RingBuffer.su ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_1_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_1_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_1_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_1_RingBuffer.su ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_2_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_2_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_2_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_2_RingBuffer.su ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_3_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_3_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_3_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_3_RingBuffer.su ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_4_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_4_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_4_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_4_RingBuffer.su ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_5_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_5_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_5_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_5_RingBuffer.su ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_6_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_6_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_6_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_6_RingBuffer.su ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_7_RingBuffer.cyclo ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_7_RingBuffer.d ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_7_RingBuffer.o ./Project/CeNTI_Library/HAL/COM/UART/RingBuffer/CeNTI_UART_7_RingBuffer.su

.PHONY: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-UART-2f-RingBuffer

