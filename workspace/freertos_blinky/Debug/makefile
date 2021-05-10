################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include freertos/src/subdir.mk
-include example/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: freertos_blinky.axf

# Tool invocations
freertos_blinky.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_chip_175x_6x\Debug" -L"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_chip_175x_6x" -L"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_board_nxp_lpcxpresso_1769\Debug" -Xlinker -Map="freertos_blinky.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "freertos_blinky_Debug.ld" -o "freertos_blinky.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) freertos_blinky.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "freertos_blinky.axf"; # arm-none-eabi-objcopy -v -O binary "freertos_blinky.axf" "freertos_blinky.bin" ; # checksum -p LPC1769 -d "freertos_blinky.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
