################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/opt/Freescale/KSDK_1.2.0/examples/frdmk64f/board.c \
/opt/Freescale/KSDK_1.2.0/examples/frdmk64f/gpio_pins.c \
/opt/Freescale/KSDK_1.2.0/examples/frdmk64f/demo_apps/usb/device/hid/hhkb/hardware_init.c \
/opt/Freescale/KSDK_1.2.0/examples/frdmk64f/pin_mux.c 

OBJS += \
./board/board.o \
./board/gpio_pins.o \
./board/hardware_init.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/gpio_pins.d \
./board/hardware_init.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/board.o: /opt/Freescale/KSDK_1.2.0/examples/frdmk64f/board.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK64FN1M0VMD12 -DFRDM_K64F -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MK64F12/include -I../../../../../../../../../../platform/devices/MK64F12/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/frdmk64f -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/frdmk64f -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../usb/usb_core/otg/sources/driver/khci -I../../../../../../../../../../usb/usb_core/otg/sources/driver/max3353/sdk -I../../../../../../../../../../usb/usb_core/otg/sources/include -I../../../../../../../../../../usb/usb_core/otg/sources/otg -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/src/uart -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/edma -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/system/inc -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/gpio_pins.o: /opt/Freescale/KSDK_1.2.0/examples/frdmk64f/gpio_pins.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK64FN1M0VMD12 -DFRDM_K64F -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MK64F12/include -I../../../../../../../../../../platform/devices/MK64F12/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/frdmk64f -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/frdmk64f -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../usb/usb_core/otg/sources/driver/khci -I../../../../../../../../../../usb/usb_core/otg/sources/driver/max3353/sdk -I../../../../../../../../../../usb/usb_core/otg/sources/include -I../../../../../../../../../../usb/usb_core/otg/sources/otg -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/src/uart -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/edma -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/system/inc -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/hardware_init.o: /opt/Freescale/KSDK_1.2.0/examples/frdmk64f/demo_apps/usb/device/hid/hhkb/hardware_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK64FN1M0VMD12 -DFRDM_K64F -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MK64F12/include -I../../../../../../../../../../platform/devices/MK64F12/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/frdmk64f -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/frdmk64f -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../usb/usb_core/otg/sources/driver/khci -I../../../../../../../../../../usb/usb_core/otg/sources/driver/max3353/sdk -I../../../../../../../../../../usb/usb_core/otg/sources/include -I../../../../../../../../../../usb/usb_core/otg/sources/otg -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/src/uart -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/edma -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/system/inc -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/pin_mux.o: /opt/Freescale/KSDK_1.2.0/examples/frdmk64f/pin_mux.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK64FN1M0VMD12 -DFRDM_K64F -DFREEDOM -I../../../../../../../../../../platform/osa/inc -I../../../../../../../../../../rtos -I../../../../../../../../../../platform/utilities/inc -I../../../../../../../../../../platform/CMSIS/Include -I../../../../../../../../../../platform/devices -I../../../../../../../../../../platform/devices/MK64F12/include -I../../../../../../../../../../platform/devices/MK64F12/startup -I../../../../../../../.. -I../../../../../../../../../../usb/adapter/sources -I../../../../../../../../../../usb/adapter/sources/sdk -I../../../../../../../../../../usb/usb_core/device/include/frdmk64f -I../../../../../../../../../../usb/usb_core/device/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/audio -I../../../../../../../../../../usb/usb_core/device/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/device/sources/classes/common -I../../../../../../../../../../usb/usb_core/device/sources/classes/composite -I../../../../../../../../../../usb/usb_core/device/sources/classes/hid -I../../../../../../../../../../usb/usb_core/device/sources/classes/include -I../../../../../../../../../../usb/usb_core/device/sources/classes/include/config -I../../../../../../../../../../usb/usb_core/device/sources/classes/msd -I../../../../../../../../../../usb/usb_core/device/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/device/sources/controller/khci -I../../../../../../../../../../usb/usb_core/device/sources/controller -I../../../../../../../../../../usb/usb_core/hal -I../../../../../../../../../../usb/usb_core/host/include/frdmk64f -I../../../../../../../../../../usb/usb_core/host/include -I../../../../../../../../../../usb/usb_core/host/sources/classes/audio -I../../../../../../../../../../usb/usb_core/host/sources/classes/cdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/hid -I../../../../../../../../../../usb/usb_core/host/sources/classes/hub -I../../../../../../../../../../usb/usb_core/host/sources/classes/msd -I../../../../../../../../../../usb/usb_core/host/sources/classes/phdc -I../../../../../../../../../../usb/usb_core/host/sources/classes/printer -I../../../../../../../../../../usb/usb_core/host/sources/controller/khci -I../../../../../../../../../../usb/usb_core/host/sources/controller -I../../../../../../../../../../usb/usb_core/include -I../../../../../../../../../../usb/usb_core/otg/sources/driver/khci -I../../../../../../../../../../usb/usb_core/otg/sources/driver/max3353/sdk -I../../../../../../../../../../usb/usb_core/otg/sources/include -I../../../../../../../../../../usb/usb_core/otg/sources/otg -I../../../../../../../../../../platform/hal/inc -I../../../../../../../../../../platform/drivers/src/uart -I../../../../../../../../../../platform/drivers/src/gpio -I../../../../../../../../../../platform/drivers/src/pit -I../../../../../../../../../../platform/drivers/src/edma -I../../../../../../../../../../platform/drivers/inc -I../../../../../../../../../../platform/system/inc -std=gnu99 -fno-strict-aliasing -Wno-format  -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

