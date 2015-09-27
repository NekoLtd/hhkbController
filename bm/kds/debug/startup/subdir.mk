################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/opt/Freescale/KSDK_1.2.0/platform/devices/startup.c \
/opt/Freescale/KSDK_1.2.0/platform/devices/MK64F12/startup/system_MK64F12.c 

S_UPPER_SRCS += \
/opt/Freescale/KSDK_1.2.0/platform/devices/MK64F12/startup/gcc/startup_MK64F12.S 

OBJS += \
./startup/startup.o \
./startup/startup_MK64F12.o \
./startup/system_MK64F12.o 

C_DEPS += \
./startup/startup.d \
./startup/system_MK64F12.d 

S_UPPER_DEPS += \
./startup/startup_MK64F12.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup.o: /opt/Freescale/KSDK_1.2.0/platform/devices/startup.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK64FN1M0VMD12 -DFRDM_K64F -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MK64F12/include -I../../../../../../../../../../platform/devices/MK64F12/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/frdmk64f -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/frdmk64f -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../usb/usb_core/otg/sources/driver/khci -I../../../../../../../../../../usb/usb_core/otg/sources/driver/max3353/sdk -I../../../../../../../../../../usb/usb_core/otg/sources/include -I../../../../../../../../../../usb/usb_core/otg/sources/otg -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/src/uart -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/edma -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/system/inc -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/startup_MK64F12.o: /opt/Freescale/KSDK_1.2.0/platform/devices/MK64F12/startup/gcc/startup_MK64F12.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -x assembler-with-cpp -DDEBUG -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mapcs  -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/system_MK64F12.o: /opt/Freescale/KSDK_1.2.0/platform/devices/MK64F12/startup/system_MK64F12.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK64FN1M0VMD12 -DFRDM_K64F -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MK64F12/include -I../../../../../../../../../../platform/devices/MK64F12/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/frdmk64f -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/frdmk64f -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../usb/usb_core/otg/sources/driver/khci -I../../../../../../../../../../usb/usb_core/otg/sources/driver/max3353/sdk -I../../../../../../../../../../usb/usb_core/otg/sources/include -I../../../../../../../../../../usb/usb_core/otg/sources/otg -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/src/uart -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/edma -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/system/inc -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


