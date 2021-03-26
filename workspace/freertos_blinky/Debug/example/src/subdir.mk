################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/cr_startup_lpc175x_6x.c \
../example/src/freertos_blinky.c \
../example/src/freertos_blinky_test.c \
../example/src/setup.c \
../example/src/sysinit.c 

OBJS += \
./example/src/cr_startup_lpc175x_6x.o \
./example/src/freertos_blinky.o \
./example/src/freertos_blinky_test.o \
./example/src/setup.o \
./example/src/sysinit.o 

C_DEPS += \
./example/src/cr_startup_lpc175x_6x.d \
./example/src/freertos_blinky.d \
./example/src/freertos_blinky_test.d \
./example/src/setup.d \
./example/src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
<<<<<<< HEAD
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\repo proyecto final\proyecto-final\workspace\lpc_chip_175x_6x\inc" -I"C:\repo proyecto final\proyecto-final\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\repo proyecto final\proyecto-final\workspace\freertos_blinky\example\inc" -I"C:\repo proyecto final\proyecto-final\workspace\freertos_blinky\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
=======
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_chip_175x_6x/inc" -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/freertos_blinky/example/inc" -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/freertos_blinky/freertos/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
>>>>>>> 3f16a922beb5e105e2b5fc5cda1b636fcdc94e8b
	@echo 'Finished building: $<'
	@echo ' '


