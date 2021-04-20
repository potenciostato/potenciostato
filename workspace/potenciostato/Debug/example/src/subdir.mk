################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/cr_startup_lpc175x_6x.c \
../example/src/hid_desc.c \
../example/src/hid_generic.c \
../example/src/main.c \
../example/src/setup.c \
../example/src/sysinit.c 

OBJS += \
./example/src/cr_startup_lpc175x_6x.o \
./example/src/hid_desc.o \
./example/src/hid_generic.o \
./example/src/main.o \
./example/src/setup.o \
./example/src/sysinit.o 

C_DEPS += \
./example/src/cr_startup_lpc175x_6x.d \
./example/src/hid_desc.d \
./example/src/hid_generic.d \
./example/src/main.d \
./example/src/setup.d \
./example/src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_chip_175x_6x\inc" -I"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_chip_175x_6x\inc\usbd" -I"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\potenciostato\example\inc" -I"E:\UTN\Proyecto Final\drive\desarrollo\software\repo\proyecto-final\workspace\potenciostato\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


