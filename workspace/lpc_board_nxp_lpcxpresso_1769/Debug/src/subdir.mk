################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board.c \
../src/board_sysinit.c \
../src/lpc_phy_smsc87x0.c 

OBJS += \
./src/board.o \
./src/board_sysinit.o \
./src/lpc_phy_smsc87x0.o 

C_DEPS += \
./src/board.d \
./src/board_sysinit.d \
./src/lpc_phy_smsc87x0.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
<<<<<<< HEAD
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_chip_175x_6x\inc" -I"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
=======
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_chip_175x_6x/inc" -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_board_nxp_lpcxpresso_1769/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
>>>>>>> f8ad0eb3378b38581f40400976370f7e95f6e148
	@echo 'Finished building: $<'
	@echo ' '


