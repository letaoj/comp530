################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HW3.c \
../buffer.c \
../semaphore.c 

O_SRCS += \
../semaphore.o 

OBJS += \
./HW3.o \
./buffer.o \
./semaphore.o 

C_DEPS += \
./HW3.d \
./buffer.d \
./semaphore.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -Ist -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


