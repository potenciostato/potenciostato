################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
all: usbd_lib_hid_generic.axf

# Tool invocations
usbd_lib_hid_generic.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\repo proyecto final\proyecto-final\workspace\lpc_chip_175x_6x\Debug" -L"C:\repo proyecto final\proyecto-final\workspace\lpc_board_nxp_lpcxpresso_1769\Debug" -L"C:\repo proyecto final\proyecto-final\workspace\lpc_chip_175x_6x\libs" -Xlinker -Map="usbd_lib_hid_generic.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "usbd_lib_hid_generic_Debug.ld" -o "usbd_lib_hid_generic.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) usbd_lib_hid_generic.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "usbd_lib_hid_generic.axf"; # arm-none-eabi-objcopy -v -O binary "usbd_lib_hid_generic.axf" "usbd_lib_hid_generic.bin" ; # checksum -p LPC1769 -d "usbd_lib_hid_generic.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
