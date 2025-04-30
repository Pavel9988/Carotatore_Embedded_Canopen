################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CanOpenSTM32/CANopenNode/example/main_blank.c 

OBJS += \
./CanOpenSTM32/CANopenNode/example/main_blank.o 

C_DEPS += \
./CanOpenSTM32/CANopenNode/example/main_blank.d 


# Each subdirectory must supply rules for building sources it contributes
CanOpenSTM32/CANopenNode/example/%.o CanOpenSTM32/CANopenNode/example/%.su CanOpenSTM32/CANopenNode/example/%.cyclo: ../CanOpenSTM32/CANopenNode/example/%.c CanOpenSTM32/CANopenNode/example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Hp/ST_Workspace/Bidirectional_com_CAN_SERIAL_F446/CanOpenSTM32/CANopenNode_STM32" -I/Bidirectional_com_CAN_SERIAL_F446/CanOpenSTM32/CANopenNode -I/Bidirectional_com_CAN_SERIAL_F446/CanOpenSTM32/CANopenNode/storage -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CanOpenSTM32-2f-CANopenNode-2f-example

clean-CanOpenSTM32-2f-CANopenNode-2f-example:
	-$(RM) ./CanOpenSTM32/CANopenNode/example/main_blank.cyclo ./CanOpenSTM32/CANopenNode/example/main_blank.d ./CanOpenSTM32/CANopenNode/example/main_blank.o ./CanOpenSTM32/CANopenNode/example/main_blank.su

.PHONY: clean-CanOpenSTM32-2f-CANopenNode-2f-example

