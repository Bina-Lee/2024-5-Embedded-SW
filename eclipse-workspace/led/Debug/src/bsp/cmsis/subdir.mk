################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/cmsis/system_stm32f7xx.c 

OBJS += \
./src/bsp/cmsis/system_stm32f7xx.o 

C_DEPS += \
./src/bsp/cmsis/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/cmsis/%.o: ../src/bsp/cmsis/%.c src/bsp/cmsis/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=softfp -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wall  -g3 -DSTM32F746xx -DUSE-USB_FS -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\lib\STM32F7xx_HAL_Driver\Inc" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp\cmsis" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp\cmsis\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


