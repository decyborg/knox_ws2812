################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ws2812b/ws2812b.c" \

C_SRCS += \
../Sources/ws2812b/ws2812b.c \

OBJS += \
./Sources/ws2812b/ws2812b_c.obj \

OBJS_QUOTED += \
"./Sources/ws2812b/ws2812b_c.obj" \

C_DEPS += \
./Sources/ws2812b/ws2812b_c.d \

C_DEPS_QUOTED += \
"./Sources/ws2812b/ws2812b_c.d" \

OBJS_OS_FORMAT += \
./Sources/ws2812b/ws2812b_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/ws2812b/ws2812b_c.obj: ../Sources/ws2812b/ws2812b.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/ws2812b/ws2812b.args" -o "Sources/ws2812b/ws2812b_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/ws2812b/%.d: ../Sources/ws2812b/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


