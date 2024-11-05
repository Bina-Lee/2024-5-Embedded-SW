################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/led.c \
../src/main.c 

OBJS += \
./src/led.o \
./src/main.o 

C_DEPS += \
./src/led.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=softfp -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wall  -g3 -DSTM32F746xx -DUSE-USB_FS -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\lib\STM32F7xx_HAL_Driver\Inc" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp\cmsis" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp\cmsis\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


