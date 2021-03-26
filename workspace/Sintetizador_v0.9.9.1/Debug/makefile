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
all: Sintetizador_v0.9.9.1.axf

# Tool invocations
Sintetizador_v0.9.9.1.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
<<<<<<< HEAD
	arm-none-eabi-gcc -nostdlib -L"C:\repo proyecto final\proyecto-final\workspace\lpc_chip_175x_6x\Debug" -L"C:\repo proyecto final\proyecto-final\workspace\lpc_board_nxp_lpcxpresso_1769\Debug" -L"C:\repo proyecto final\proyecto-final\workspace\lpc_chip_175x_6x\libs" -Xlinker -Map="Sintetizador_v0.9.9.1.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Sintetizador_v0_9_5_Debug.ld" -o "Sintetizador_v0.9.9.1.axf" $(OBJS) $(USER_OBJS) $(LIBS)
=======
	arm-none-eabi-gcc -nostdlib -L"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_chip_175x_6x/Debug" -L"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_board_nxp_lpcxpresso_1769/Debug" -L"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_chip_175x_6x/libs" -Xlinker -Map="Sintetizador_v0.9.9.1.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Sintetizador_v0_9_5_Debug.ld" -o "Sintetizador_v0.9.9.1.axf" $(OBJS) $(USER_OBJS) $(LIBS)
>>>>>>> 3f16a922beb5e105e2b5fc5cda1b636fcdc94e8b
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Sintetizador_v0.9.9.1.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Sintetizador_v0.9.9.1.axf"; # arm-none-eabi-objcopy -v -O binary "Sintetizador_v0.9.9.1.axf" "Sintetizador_v0.9.9.1.bin" ; # checksum -p LPC1769 -d "Sintetizador_v0.9.9.1.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
