################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/src/FreeRTOSCommonHooks.c \
../freertos/src/heap_3.c \
../freertos/src/list.c \
../freertos/src/port.c \
../freertos/src/queue.c \
../freertos/src/tasks.c 

OBJS += \
./freertos/src/FreeRTOSCommonHooks.o \
./freertos/src/heap_3.o \
./freertos/src/list.o \
./freertos/src/port.o \
./freertos/src/queue.o \
./freertos/src/tasks.o 

C_DEPS += \
./freertos/src/FreeRTOSCommonHooks.d \
./freertos/src/heap_3.d \
./freertos/src/list.d \
./freertos/src/port.d \
./freertos/src/queue.d \
./freertos/src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/src/%.o: ../freertos/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
<<<<<<< HEAD
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\repo proyecto final\proyecto-final\workspace\lpc_chip_175x_6x\inc" -I"C:\repo proyecto final\proyecto-final\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\repo proyecto final\proyecto-final\workspace\freertos_blinky\example\inc" -I"C:\repo proyecto final\proyecto-final\workspace\freertos_blinky\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
=======
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_chip_175x_6x/inc" -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/freertos_blinky/example/inc" -I"/home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/workspace/freertos_blinky/freertos/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
>>>>>>> 3f16a922beb5e105e2b5fc5cda1b636fcdc94e8b
	@echo 'Finished building: $<'
	@echo ' '


