################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CanOpenSTM32/CANopenNode_STM32/CANopen.c \
../CanOpenSTM32/CANopenNode_STM32/CO_Emergency.c \
../CanOpenSTM32/CANopenNode_STM32/CO_GFC.c \
../CanOpenSTM32/CANopenNode_STM32/CO_HBconsumer.c \
../CanOpenSTM32/CANopenNode_STM32/CO_LEDs.c \
../CanOpenSTM32/CANopenNode_STM32/CO_LSSmaster.c \
../CanOpenSTM32/CANopenNode_STM32/CO_LSSslave.c \
../CanOpenSTM32/CANopenNode_STM32/CO_NMT_Heartbeat.c \
../CanOpenSTM32/CANopenNode_STM32/CO_Node_Guarding.c \
../CanOpenSTM32/CANopenNode_STM32/CO_ODinterface.c \
../CanOpenSTM32/CANopenNode_STM32/CO_PDO.c \
../CanOpenSTM32/CANopenNode_STM32/CO_SDOclient.c \
../CanOpenSTM32/CANopenNode_STM32/CO_SDOserver.c \
../CanOpenSTM32/CANopenNode_STM32/CO_SRDO.c \
../CanOpenSTM32/CANopenNode_STM32/CO_SYNC.c \
../CanOpenSTM32/CANopenNode_STM32/CO_TIME.c \
../CanOpenSTM32/CANopenNode_STM32/CO_app_STM32.c \
../CanOpenSTM32/CANopenNode_STM32/CO_driver_STM32.c \
../CanOpenSTM32/CANopenNode_STM32/CO_fifo.c \
../CanOpenSTM32/CANopenNode_STM32/CO_storageBlank.c \
../CanOpenSTM32/CANopenNode_STM32/OD.c \
../CanOpenSTM32/CANopenNode_STM32/crc16-ccitt.c 

OBJS += \
./CanOpenSTM32/CANopenNode_STM32/CANopen.o \
./CanOpenSTM32/CANopenNode_STM32/CO_Emergency.o \
./CanOpenSTM32/CANopenNode_STM32/CO_GFC.o \
./CanOpenSTM32/CANopenNode_STM32/CO_HBconsumer.o \
./CanOpenSTM32/CANopenNode_STM32/CO_LEDs.o \
./CanOpenSTM32/CANopenNode_STM32/CO_LSSmaster.o \
./CanOpenSTM32/CANopenNode_STM32/CO_LSSslave.o \
./CanOpenSTM32/CANopenNode_STM32/CO_NMT_Heartbeat.o \
./CanOpenSTM32/CANopenNode_STM32/CO_Node_Guarding.o \
./CanOpenSTM32/CANopenNode_STM32/CO_ODinterface.o \
./CanOpenSTM32/CANopenNode_STM32/CO_PDO.o \
./CanOpenSTM32/CANopenNode_STM32/CO_SDOclient.o \
./CanOpenSTM32/CANopenNode_STM32/CO_SDOserver.o \
./CanOpenSTM32/CANopenNode_STM32/CO_SRDO.o \
./CanOpenSTM32/CANopenNode_STM32/CO_SYNC.o \
./CanOpenSTM32/CANopenNode_STM32/CO_TIME.o \
./CanOpenSTM32/CANopenNode_STM32/CO_app_STM32.o \
./CanOpenSTM32/CANopenNode_STM32/CO_driver_STM32.o \
./CanOpenSTM32/CANopenNode_STM32/CO_fifo.o \
./CanOpenSTM32/CANopenNode_STM32/CO_storageBlank.o \
./CanOpenSTM32/CANopenNode_STM32/OD.o \
./CanOpenSTM32/CANopenNode_STM32/crc16-ccitt.o 

C_DEPS += \
./CanOpenSTM32/CANopenNode_STM32/CANopen.d \
./CanOpenSTM32/CANopenNode_STM32/CO_Emergency.d \
./CanOpenSTM32/CANopenNode_STM32/CO_GFC.d \
./CanOpenSTM32/CANopenNode_STM32/CO_HBconsumer.d \
./CanOpenSTM32/CANopenNode_STM32/CO_LEDs.d \
./CanOpenSTM32/CANopenNode_STM32/CO_LSSmaster.d \
./CanOpenSTM32/CANopenNode_STM32/CO_LSSslave.d \
./CanOpenSTM32/CANopenNode_STM32/CO_NMT_Heartbeat.d \
./CanOpenSTM32/CANopenNode_STM32/CO_Node_Guarding.d \
./CanOpenSTM32/CANopenNode_STM32/CO_ODinterface.d \
./CanOpenSTM32/CANopenNode_STM32/CO_PDO.d \
./CanOpenSTM32/CANopenNode_STM32/CO_SDOclient.d \
./CanOpenSTM32/CANopenNode_STM32/CO_SDOserver.d \
./CanOpenSTM32/CANopenNode_STM32/CO_SRDO.d \
./CanOpenSTM32/CANopenNode_STM32/CO_SYNC.d \
./CanOpenSTM32/CANopenNode_STM32/CO_TIME.d \
./CanOpenSTM32/CANopenNode_STM32/CO_app_STM32.d \
./CanOpenSTM32/CANopenNode_STM32/CO_driver_STM32.d \
./CanOpenSTM32/CANopenNode_STM32/CO_fifo.d \
./CanOpenSTM32/CANopenNode_STM32/CO_storageBlank.d \
./CanOpenSTM32/CANopenNode_STM32/OD.d \
./CanOpenSTM32/CANopenNode_STM32/crc16-ccitt.d 


# Each subdirectory must supply rules for building sources it contributes
CanOpenSTM32/CANopenNode_STM32/%.o CanOpenSTM32/CANopenNode_STM32/%.su CanOpenSTM32/CANopenNode_STM32/%.cyclo: ../CanOpenSTM32/CANopenNode_STM32/%.c CanOpenSTM32/CANopenNode_STM32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Hp/ST_Workspace/Bidirectional_com_CAN_SERIAL_F446/CanOpenSTM32/CANopenNode_STM32" -I"C:/Users/Hp/ST_Workspace/Bidirectional_com_CAN_SERIAL_F446/CanOpenSTM32/CANopenNode/storage" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CanOpenSTM32-2f-CANopenNode_STM32

clean-CanOpenSTM32-2f-CANopenNode_STM32:
	-$(RM) ./CanOpenSTM32/CANopenNode_STM32/CANopen.cyclo ./CanOpenSTM32/CANopenNode_STM32/CANopen.d ./CanOpenSTM32/CANopenNode_STM32/CANopen.o ./CanOpenSTM32/CANopenNode_STM32/CANopen.su ./CanOpenSTM32/CANopenNode_STM32/CO_Emergency.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_Emergency.d ./CanOpenSTM32/CANopenNode_STM32/CO_Emergency.o ./CanOpenSTM32/CANopenNode_STM32/CO_Emergency.su ./CanOpenSTM32/CANopenNode_STM32/CO_GFC.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_GFC.d ./CanOpenSTM32/CANopenNode_STM32/CO_GFC.o ./CanOpenSTM32/CANopenNode_STM32/CO_GFC.su ./CanOpenSTM32/CANopenNode_STM32/CO_HBconsumer.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_HBconsumer.d ./CanOpenSTM32/CANopenNode_STM32/CO_HBconsumer.o ./CanOpenSTM32/CANopenNode_STM32/CO_HBconsumer.su ./CanOpenSTM32/CANopenNode_STM32/CO_LEDs.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_LEDs.d ./CanOpenSTM32/CANopenNode_STM32/CO_LEDs.o ./CanOpenSTM32/CANopenNode_STM32/CO_LEDs.su ./CanOpenSTM32/CANopenNode_STM32/CO_LSSmaster.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_LSSmaster.d ./CanOpenSTM32/CANopenNode_STM32/CO_LSSmaster.o ./CanOpenSTM32/CANopenNode_STM32/CO_LSSmaster.su ./CanOpenSTM32/CANopenNode_STM32/CO_LSSslave.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_LSSslave.d ./CanOpenSTM32/CANopenNode_STM32/CO_LSSslave.o ./CanOpenSTM32/CANopenNode_STM32/CO_LSSslave.su ./CanOpenSTM32/CANopenNode_STM32/CO_NMT_Heartbeat.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_NMT_Heartbeat.d ./CanOpenSTM32/CANopenNode_STM32/CO_NMT_Heartbeat.o ./CanOpenSTM32/CANopenNode_STM32/CO_NMT_Heartbeat.su ./CanOpenSTM32/CANopenNode_STM32/CO_Node_Guarding.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_Node_Guarding.d ./CanOpenSTM32/CANopenNode_STM32/CO_Node_Guarding.o ./CanOpenSTM32/CANopenNode_STM32/CO_Node_Guarding.su ./CanOpenSTM32/CANopenNode_STM32/CO_ODinterface.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_ODinterface.d ./CanOpenSTM32/CANopenNode_STM32/CO_ODinterface.o ./CanOpenSTM32/CANopenNode_STM32/CO_ODinterface.su ./CanOpenSTM32/CANopenNode_STM32/CO_PDO.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_PDO.d ./CanOpenSTM32/CANopenNode_STM32/CO_PDO.o ./CanOpenSTM32/CANopenNode_STM32/CO_PDO.su ./CanOpenSTM32/CANopenNode_STM32/CO_SDOclient.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_SDOclient.d ./CanOpenSTM32/CANopenNode_STM32/CO_SDOclient.o ./CanOpenSTM32/CANopenNode_STM32/CO_SDOclient.su ./CanOpenSTM32/CANopenNode_STM32/CO_SDOserver.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_SDOserver.d ./CanOpenSTM32/CANopenNode_STM32/CO_SDOserver.o ./CanOpenSTM32/CANopenNode_STM32/CO_SDOserver.su ./CanOpenSTM32/CANopenNode_STM32/CO_SRDO.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_SRDO.d ./CanOpenSTM32/CANopenNode_STM32/CO_SRDO.o ./CanOpenSTM32/CANopenNode_STM32/CO_SRDO.su ./CanOpenSTM32/CANopenNode_STM32/CO_SYNC.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_SYNC.d ./CanOpenSTM32/CANopenNode_STM32/CO_SYNC.o ./CanOpenSTM32/CANopenNode_STM32/CO_SYNC.su ./CanOpenSTM32/CANopenNode_STM32/CO_TIME.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_TIME.d ./CanOpenSTM32/CANopenNode_STM32/CO_TIME.o ./CanOpenSTM32/CANopenNode_STM32/CO_TIME.su ./CanOpenSTM32/CANopenNode_STM32/CO_app_STM32.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_app_STM32.d ./CanOpenSTM32/CANopenNode_STM32/CO_app_STM32.o ./CanOpenSTM32/CANopenNode_STM32/CO_app_STM32.su ./CanOpenSTM32/CANopenNode_STM32/CO_driver_STM32.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_driver_STM32.d ./CanOpenSTM32/CANopenNode_STM32/CO_driver_STM32.o ./CanOpenSTM32/CANopenNode_STM32/CO_driver_STM32.su ./CanOpenSTM32/CANopenNode_STM32/CO_fifo.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_fifo.d ./CanOpenSTM32/CANopenNode_STM32/CO_fifo.o ./CanOpenSTM32/CANopenNode_STM32/CO_fifo.su ./CanOpenSTM32/CANopenNode_STM32/CO_storageBlank.cyclo ./CanOpenSTM32/CANopenNode_STM32/CO_storageBlank.d ./CanOpenSTM32/CANopenNode_STM32/CO_storageBlank.o ./CanOpenSTM32/CANopenNode_STM32/CO_storageBlank.su ./CanOpenSTM32/CANopenNode_STM32/OD.cyclo ./CanOpenSTM32/CANopenNode_STM32/OD.d ./CanOpenSTM32/CANopenNode_STM32/OD.o ./CanOpenSTM32/CANopenNode_STM32/OD.su ./CanOpenSTM32/CANopenNode_STM32/crc16-ccitt.cyclo ./CanOpenSTM32/CANopenNode_STM32/crc16-ccitt.d ./CanOpenSTM32/CANopenNode_STM32/crc16-ccitt.o ./CanOpenSTM32/CANopenNode_STM32/crc16-ccitt.su

.PHONY: clean-CanOpenSTM32-2f-CANopenNode_STM32

