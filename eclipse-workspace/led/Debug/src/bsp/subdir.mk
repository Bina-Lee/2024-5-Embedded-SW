################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/bsp.c \
../src/bsp/stm32f7xx_it.c \
../src/bsp/syscalls.c 

OBJS += \
./src/bsp/bsp.o \
./src/bsp/stm32f7xx_it.o \
./src/bsp/syscalls.o 

C_DEPS += \
./src/bsp/bsp.d \
./src/bsp/stm32f7xx_it.d \
./src/bsp/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/%.o: ../src/bsp/%.c src/bsp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=softfp -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wall  -g3 -DSTM32F746xx -DUSE-USB_FS -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\lib\STM32F7xx_HAL_Driver\Inc" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp\cmsis" -I"C:\Users\Herb\Desktop\eclipse-workspace\led\src\bsp\cmsis\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


