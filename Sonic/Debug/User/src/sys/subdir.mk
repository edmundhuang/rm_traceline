################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/src/sys/class_task.c \
../User/src/sys/lib_system.c 

OBJS += \
./User/src/sys/class_task.o \
./User/src/sys/lib_system.o 

C_DEPS += \
./User/src/sys/class_task.d \
./User/src/sys/lib_system.d 


# Each subdirectory must supply rules for building sources it contributes
User/src/sys/%.o: ../User/src/sys/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F427xx -I../LibInc -I../LibInc/hal -I../LibInc/inc -I../LibInc/inc/user -I../LibInc/m3 -I../LibInc/os -I../LibInc/src -I../User/inc -I../User/src/sys -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


