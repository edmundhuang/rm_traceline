################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/src/sys/subdir.mk
-include User/src/dev/subdir.mk
-include LibInc/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: tutorial_lib.elf

# Tool invocations
tutorial_lib.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -L../LibInc/src -specs=nosys.specs -specs=nano.specs -T"../STM32F427IIHx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "tutorial_lib.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS) tutorial_lib.elf
	-@echo ' '

post-build:
	-@echo 'Generating hex and Printing size information:'
	-arm-none-eabi-objcopy -O ihex "tutorial_lib.elf" "tutorial_lib.hex" && arm-none-eabi-size "tutorial_lib.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
