################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_0_Master.c \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_1_Master.c \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_2_Master.c \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_3_Master.c \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_4_Master.c \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_5_Master.c \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_6_Master.c \
../Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_7_Master.c 

OBJS += \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_0_Master.o \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_1_Master.o \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_2_Master.o \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_3_Master.o \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_4_Master.o \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_5_Master.o \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_6_Master.o \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_7_Master.o 

C_DEPS += \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_0_Master.d \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_1_Master.d \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_2_Master.d \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_3_Master.d \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_4_Master.d \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_5_Master.d \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_6_Master.d \
./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_7_Master.d 


# Each subdirectory must supply rules for building sources it contributes
Project/CeNTI_Library/HAL/COM/SPI/Master/%.o Project/CeNTI_Library/HAL/COM/SPI/Master/%.su Project/CeNTI_Library/HAL/COM/SPI/Master/%.cyclo: ../Project/CeNTI_Library/HAL/COM/SPI/Master/%.c Project/CeNTI_Library/HAL/COM/SPI/Master/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-SPI-2f-Master

clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-SPI-2f-Master:
	-$(RM) ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_0_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_0_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_0_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_0_Master.su ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_1_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_1_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_1_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_1_Master.su ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_2_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_2_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_2_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_2_Master.su ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_3_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_3_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_3_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_3_Master.su ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_4_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_4_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_4_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_4_Master.su ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_5_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_5_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_5_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_5_Master.su ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_6_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_6_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_6_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_6_Master.su ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_7_Master.cyclo ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_7_Master.d ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_7_Master.o ./Project/CeNTI_Library/HAL/COM/SPI/Master/CeNTI_SPI_7_Master.su

.PHONY: clean-Project-2f-CeNTI_Library-2f-HAL-2f-COM-2f-SPI-2f-Master

