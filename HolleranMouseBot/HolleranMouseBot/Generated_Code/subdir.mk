################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/ADC1.c" \
"../Generated_Code/BitIoLdd1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/CsIO1.c" \
"../Generated_Code/DMA1.c" \
"../Generated_Code/IO1.c" \
"../Generated_Code/IR.c" \
"../Generated_Code/LEDpin1.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/PwmLdd1.c" \
"../Generated_Code/PwmLdd2.c" \
"../Generated_Code/TU1.c" \
"../Generated_Code/TU2.c" \
"../Generated_Code/Vectors.c" \
"../Generated_Code/left.c" \
"../Generated_Code/right.c" \
"../Generated_Code/w.c" \

C_SRCS += \
../Generated_Code/ADC1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/Cpu.c \
../Generated_Code/CsIO1.c \
../Generated_Code/DMA1.c \
../Generated_Code/IO1.c \
../Generated_Code/IR.c \
../Generated_Code/LEDpin1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/PwmLdd2.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/Vectors.c \
../Generated_Code/left.c \
../Generated_Code/right.c \
../Generated_Code/w.c \

OBJS += \
./Generated_Code/ADC1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/Cpu.o \
./Generated_Code/CsIO1.o \
./Generated_Code/DMA1.o \
./Generated_Code/IO1.o \
./Generated_Code/IR.o \
./Generated_Code/LEDpin1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/Vectors.o \
./Generated_Code/left.o \
./Generated_Code/right.o \
./Generated_Code/w.o \

C_DEPS += \
./Generated_Code/ADC1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/Cpu.d \
./Generated_Code/CsIO1.d \
./Generated_Code/DMA1.d \
./Generated_Code/IO1.d \
./Generated_Code/IR.d \
./Generated_Code/LEDpin1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/PwmLdd2.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/Vectors.d \
./Generated_Code/left.d \
./Generated_Code/right.d \
./Generated_Code/w.d \

OBJS_QUOTED += \
"./Generated_Code/ADC1.o" \
"./Generated_Code/BitIoLdd1.o" \
"./Generated_Code/Cpu.o" \
"./Generated_Code/CsIO1.o" \
"./Generated_Code/DMA1.o" \
"./Generated_Code/IO1.o" \
"./Generated_Code/IR.o" \
"./Generated_Code/LEDpin1.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/PwmLdd1.o" \
"./Generated_Code/PwmLdd2.o" \
"./Generated_Code/TU1.o" \
"./Generated_Code/TU2.o" \
"./Generated_Code/Vectors.o" \
"./Generated_Code/left.o" \
"./Generated_Code/right.o" \
"./Generated_Code/w.o" \

C_DEPS_QUOTED += \
"./Generated_Code/ADC1.d" \
"./Generated_Code/BitIoLdd1.d" \
"./Generated_Code/Cpu.d" \
"./Generated_Code/CsIO1.d" \
"./Generated_Code/DMA1.d" \
"./Generated_Code/IO1.d" \
"./Generated_Code/IR.d" \
"./Generated_Code/LEDpin1.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/PwmLdd1.d" \
"./Generated_Code/PwmLdd2.d" \
"./Generated_Code/TU1.d" \
"./Generated_Code/TU2.d" \
"./Generated_Code/Vectors.d" \
"./Generated_Code/left.d" \
"./Generated_Code/right.d" \
"./Generated_Code/w.d" \

OBJS_OS_FORMAT += \
./Generated_Code/ADC1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/Cpu.o \
./Generated_Code/CsIO1.o \
./Generated_Code/DMA1.o \
./Generated_Code/IO1.o \
./Generated_Code/IR.o \
./Generated_Code/LEDpin1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/Vectors.o \
./Generated_Code/left.o \
./Generated_Code/right.o \
./Generated_Code/w.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/ADC1.o: ../Generated_Code/ADC1.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/ADC1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/ADC1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitIoLdd1.o: ../Generated_Code/BitIoLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/BitIoLdd1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/BitIoLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CsIO1.o: ../Generated_Code/CsIO1.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CsIO1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CsIO1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/DMA1.o: ../Generated_Code/DMA1.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/DMA1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/DMA1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO1.o: ../Generated_Code/IO1.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IO1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IO1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IR.o: ../Generated_Code/IR.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/IR.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/IR.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/LEDpin1.o: ../Generated_Code/LEDpin1.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/LEDpin1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/LEDpin1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PwmLdd1.o: ../Generated_Code/PwmLdd1.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PwmLdd1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PwmLdd1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PwmLdd2.o: ../Generated_Code/PwmLdd2.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PwmLdd2.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PwmLdd2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU1.o: ../Generated_Code/TU1.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU1.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TU2.o: ../Generated_Code/TU2.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TU2.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TU2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/left.o: ../Generated_Code/left.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/left.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/left.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/right.o: ../Generated_Code/right.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/right.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/right.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/w.o: ../Generated_Code/w.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/w.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/w.o"
	@echo 'Finished building: $<'
	@echo ' '


