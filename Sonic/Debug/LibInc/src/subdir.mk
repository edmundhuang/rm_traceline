################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../LibInc/src/startup_stm32f427xx.s 

C_SRCS += \
../LibInc/src/stm32f4xx_it.c 

OBJS += \
./LibInc/src/startup_stm32f427xx.o \
./LibInc/src/stm32f4xx_it.o 

C_DEPS += \
./LibInc/src/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
LibInc/src/%.o: ../LibInc/src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

LibInc/src/%.o: ../LibInc/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F427xx -I../LibInc -I../LibInc/hal -I../LibInc/inc -I../LibInc/inc/user -I../LibInc/m3 -I../LibInc/os -I../LibInc/src -I../User/inc -I../User/src/sys -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


