################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Project/Manager/subdir.mk
-include Project/Devices/MODBUS/subdir.mk
-include Project/CeNTI_Library/lib/Time/subdir.mk
-include Project/CeNTI_Library/lib/SoftTimer/subdir.mk
-include Project/CeNTI_Library/lib/FIFO/subdir.mk
-include Project/CeNTI_Library/lib/CRC/subdir.mk
-include Project/CeNTI_Library/lib/ArrayList/subdir.mk
-include Project/CeNTI_Library/HAL/Timers/subdir.mk
-include Project/CeNTI_Library/HAL/GPIO/subdir.mk
-include Project/CeNTI_Library/HAL/COM/UART/RingBuffer/subdir.mk
-include Project/CeNTI_Library/HAL/COM/UART/ASync/subdir.mk
-include Project/CeNTI_Library/HAL/COM/SPI/Slave/subdir.mk
-include Project/CeNTI_Library/HAL/COM/SPI/Master/subdir.mk
-include Project/CeNTI_Library/HAL/COM/I2C/Slave/subdir.mk
-include Project/CeNTI_Library/HAL/COM/I2C/Master/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MODBUS
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MODBUS.elf \

MAP_FILES += \
MODBUS.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MODBUS.list \


# All Target
all: main-build

# Main-build Target
main-build: MODBUS.elf secondary-outputs

# Tool invocations
MODBUS.elf MODBUS.map: $(OBJS) $(USER_OBJS) C:\Github\Private_rep\MODBUS_Slave\MODBUS_2\STM32L476RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "MODBUS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Github\Private_rep\MODBUS_Slave\MODBUS_2\STM32L476RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MODBUS.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MODBUS.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MODBUS.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MODBUS.elf MODBUS.list MODBUS.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
