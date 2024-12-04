################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/SDCard/CMD.c \
../Src/SDCard/RSP.c \
../Src/SDCard/SDCard.c 

OBJS += \
./Src/SDCard/CMD.o \
./Src/SDCard/RSP.o \
./Src/SDCard/SDCard.o 

C_DEPS += \
./Src/SDCard/CMD.d \
./Src/SDCard/RSP.d \
./Src/SDCard/SDCard.d 


# Each subdirectory must supply rules for building sources it contributes
Src/SDCard/%.o Src/SDCard/%.su Src/SDCard/%.cyclo: ../Src/SDCard/%.c Src/SDCard/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F401xE -c -I../Inc -I"../$(ProjDirPath)/Headers/CMSIS/Include" -I"../$(ProjDirPath)/Headers/CMSIS/Device/ST/STM32F4xx/Include" -I../$(ProjDirPath)/Inc/Drivers -I../$(ProjDirPath)/Inc/SDCard -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-SDCard

clean-Src-2f-SDCard:
	-$(RM) ./Src/SDCard/CMD.cyclo ./Src/SDCard/CMD.d ./Src/SDCard/CMD.o ./Src/SDCard/CMD.su ./Src/SDCard/RSP.cyclo ./Src/SDCard/RSP.d ./Src/SDCard/RSP.o ./Src/SDCard/RSP.su ./Src/SDCard/SDCard.cyclo ./Src/SDCard/SDCard.d ./Src/SDCard/SDCard.o ./Src/SDCard/SDCard.su

.PHONY: clean-Src-2f-SDCard

