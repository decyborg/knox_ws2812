################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MagniV_API/CPMU/cpmu.c" \

C_SRCS += \
../Sources/MagniV_API/CPMU/cpmu.c \

OBJS += \
./Sources/MagniV_API/CPMU/cpmu_c.obj \

OBJS_QUOTED += \
"./Sources/MagniV_API/CPMU/cpmu_c.obj" \

C_DEPS += \
./Sources/MagniV_API/CPMU/cpmu_c.d \

C_DEPS_QUOTED += \
"./Sources/MagniV_API/CPMU/cpmu_c.d" \

OBJS_OS_FORMAT += \
./Sources/MagniV_API/CPMU/cpmu_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/MagniV_API/CPMU/cpmu_c.obj: ../Sources/MagniV_API/CPMU/cpmu.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/MagniV_API/CPMU/cpmu.args" -o "Sources/MagniV_API/CPMU/cpmu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/MagniV_API/CPMU/%.d: ../Sources/MagniV_API/CPMU/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


