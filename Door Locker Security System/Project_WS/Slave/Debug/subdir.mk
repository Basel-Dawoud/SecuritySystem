################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CONTROL_ECU_AppFile.c \
../DCMotor.c \
../PWM.c \
../adc.c \
../buzzer.c \
../external_eeprom.c \
../gpio.c \
../lcd.c \
../security_functions.c \
../timer1.c \
../twi.c \
../uart.c 

OBJS += \
./CONTROL_ECU_AppFile.o \
./DCMotor.o \
./PWM.o \
./adc.o \
./buzzer.o \
./external_eeprom.o \
./gpio.o \
./lcd.o \
./security_functions.o \
./timer1.o \
./twi.o \
./uart.o 

C_DEPS += \
./CONTROL_ECU_AppFile.d \
./DCMotor.d \
./PWM.d \
./adc.d \
./buzzer.d \
./external_eeprom.d \
./gpio.d \
./lcd.d \
./security_functions.d \
./timer1.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


