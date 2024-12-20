################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Drivers/LED.c \
../Src/Drivers/SPI.c \
../Src/Drivers/SYSTICK.c \
../Src/Drivers/UART.c 

OBJS += \
./Src/Drivers/LED.o \
./Src/Drivers/SPI.o \
./Src/Drivers/SYSTICK.o \
./Src/Drivers/UART.o 

C_DEPS += \
./Src/Drivers/LED.d \
./Src/Drivers/SPI.d \
./Src/Drivers/SYSTICK.d \
./Src/Drivers/UART.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Drivers/%.o Src/Drivers/%.su Src/Drivers/%.cyclo: ../Src/Drivers/%.c Src/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F401xE -c -I../Inc -I"../$(ProjDirPath)/Headers/CMSIS/Include" -I"../$(ProjDirPath)/Headers/CMSIS/Device/ST/STM32F4xx/Include" -I../$(ProjDirPath)/Inc/Drivers -I../$(ProjDirPath)/Inc/SDCard -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Drivers

clean-Src-2f-Drivers:
	-$(RM) ./Src/Drivers/LED.cyclo ./Src/Drivers/LED.d ./Src/Drivers/LED.o ./Src/Drivers/LED.su ./Src/Drivers/SPI.cyclo ./Src/Drivers/SPI.d ./Src/Drivers/SPI.o ./Src/Drivers/SPI.su ./Src/Drivers/SYSTICK.cyclo ./Src/Drivers/SYSTICK.d ./Src/Drivers/SYSTICK.o ./Src/Drivers/SYSTICK.su ./Src/Drivers/UART.cyclo ./Src/Drivers/UART.d ./Src/Drivers/UART.o ./Src/Drivers/UART.su

.PHONY: clean-Src-2f-Drivers

