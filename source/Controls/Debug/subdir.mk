################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ras_Controls.cpp \
../ras_DataFormatter.cpp \
../ras_DataSource.cpp \
../ras_ElementControlInterface.cpp 

OBJS += \
./ras_Controls.o \
./ras_DataFormatter.o \
./ras_DataSource.o \
./ras_ElementControlInterface.o 

CPP_DEPS += \
./ras_Controls.d \
./ras_DataFormatter.d \
./ras_DataSource.d \
./ras_ElementControlInterface.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/kezeali/tbb/include -I"/home/kezeali/FusionGit/ScriptUtils/include" -I"${BOOST_ROOT}/include" -O0 -g3 -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


