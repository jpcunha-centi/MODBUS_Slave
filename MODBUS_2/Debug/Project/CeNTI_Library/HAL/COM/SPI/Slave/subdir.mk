################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_0_Slave.c \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_1_Slave.c \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_2_Slave.c \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_3_Slave.c \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_4_Slave.c \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_5_Slave.c \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_6_Slave.c \
../Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_7_Slave.c 

OBJS += \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_0_Slave.o \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_1_Slave.o \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_2_Slave.o \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_3_Slave.o \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_4_Slave.o \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_5_Slave.o \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_6_Slave.o \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_7_Slave.o 

C_DEPS += \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_0_Slave.d \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_1_Slave.d \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_2_Slave.d \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_3_Slave.d \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_4_Slave.d \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_5_Slave.d \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_6_Slave.d \
./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_7_Slave.d 


# Each subdirectory must supply rules for building sources it contributes
Project/CeNTI_Library/HAL/COM/SPI/Slave/%.o Project/CeNTI_Library/HAL/COM/SPI/Slave/%.su Project/CeNTI_Library/HAL/COM/SPI/Slave/%.cyclo: ../Project/CeNTI_Library/HAL/COM/SPI/Slave/%.c Project/CeNTI_Library/HAL/COM/SPI/Slave/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-SPI-2f-Slave

clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-SPI-2f-Slave:
	-$(RM) ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_0_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_0_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_0_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_0_Slave.su ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_1_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_1_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_1_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_1_Slave.su ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_2_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_2_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_2_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_2_Slave.su ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_3_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_3_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_3_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_3_Slave.su ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_4_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_4_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_4_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_4_Slave.su ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_5_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_5_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_5_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_5_Slave.su ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_6_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_6_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_6_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_6_Slave.su ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_7_Slave.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_7_Slave.d ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_7_Slave.o ./Project/CeNTI_Library/HAL/COM/SPI/Slave/CeNTI_SPI_7_Slave.su

.PHONY: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-SPI-2f-Slave

