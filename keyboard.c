/**HEADER********************************************************************
 *
* Copyright (c) 2004 -2010, 2013- 2015 Freescale Semiconductor;
 * All Rights Reserved
 *
 *
 ***************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************
 *
 * $FileName:keyboard.c
 * $Version :
 * $Date    :
 *
 * Comments:
 * 
 *
 *END************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "usb_class_hid.h"
#include "keyboard.h"   /* Keyboard Application Header File */
#include "usb_descriptor.h"

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_port_hal.h"

#include "gpio_pins.h"
#include "fsl_lptmr_driver.h"

#include <stdio.h>
#include <stdlib.h>
#endif
/* skip the inclusion in dependency stage */
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#include <stdlib.h>
#include <string.h>
#endif

#if USBCFG_DEV_COMPOSITE
#error This application requires USBCFG_DEV_COMPOSITE defined zero in usb_device_config.h. Please recompile usbd with this option.
#endif

extern void Main_Task(uint32_t param);
#define MAIN_TASK       10

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
    { MAIN_TASK, Main_Task, 2000L, 7L, "Main", MQX_AUTO_START_TASK, 0, 0 },
    { 0L, 0L, 0L, 0L, 0L, 0L, 0, 0 }
};
#endif

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/* Add all the variables needed for mouse.c to this structure */
extern usb_desc_request_notify_struct_t g_desc_callback;
keyboard_global_variable_struct_t g_keyboard;
uint32_t g_process_times = 1;
uint8_t g_key_index = 2;
uint8_t g_new_key_pressed = 0;

/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/
// QWERTY Map for HHKB
uint8_t qwertyMap[8][8] = {
	{
		KEY_2_AT,
		KEY_Q,
		KEY_W,
		KEY_S,
		KEY_A,
		KEY_Z,
		KEY_X,
		KEY_C
	},
	{
		KEY_3_NUMBER_SIGN,
		KEY_4_DOLLAR,
		KEY_R,
		KEY_E,
		KEY_D,
		KEY_F,
		KEY_V,
		KEY_B
	},
	{
		KEY_5_PERCENT,
		KEY_6_CARET,
		KEY_Y,
		KEY_T,
		KEY_G,
		KEY_H,
		KEY_N,
		KEY_NONE
	},
	{
		KEY_1_EXCLAMATION_MARK,
		KEY_ESCAPE,
		KEY_TAB,
		MODIFERKEYS_LEFT_CTRL,
		MODIFERKEYS_LEFT_SHIFT,
		MODIFERKEYS_LEFT_ALT,
		MODIFERKEYS_LEFT_GUI,
		KEY_SPACEBAR
	},
	{
		KEY_7_AMPERSAND,
		KEY_8_ASTERISK,
		KEY_U,
		KEY_I,
		KEY_K,
		KEY_J,
		KEY_M,
		KEY_NONE
	},
	{
		KEY_BACKSLASH_VERTICAL_BAR,
		KEY_GRAVE_ACCENT_AND_TILDE,
		KEY_BACKSPACE, //KEY_DELETE,
		KEY_ENTER,
		KEY_NONE, //Fn Key
		MODIFERKEYS_RIGHT_SHIFT,
		MODIFERKEYS_RIGHT_ALT,
		MODIFERKEYS_RIGHT_GUI
	},
	{
		KEY_9_OPARENTHESIS,
		KEY_0_CPARENTHESIS,
		KEY_O,
		KEY_P,
		KEY_SEMICOLON_COLON,
		KEY_L,
		KEY_COMMA_AND_LESS,
		KEY_NONE
	},
	{
		KEY_MINUS_UNDERSCORE,
		KEY_EQUAL_PLUS,
		KEY_CBRACKET_AND_CBRACE,
		KEY_OBRACKET_AND_OBRACE,
		KEY_SINGLE_AND_DOUBLE_QUOTE,
		KEY_SLASH_QUESTION,
		KEY_DOT_GREATER,
		KEY_NONE
	},
};

unsigned int rowSizes[] = {
	8,
	8,
	7,
	8,
	7,
	8,
	7,
	7
};

unsigned int sendBuffer[128];
unsigned int sendBufferWrite = 0;
unsigned int sendBufferRead = 0;

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
//void TestApp_Init(void);

// Interrupt for lptmr0
void LPTMR0_IRQHandler(void)
{
    LPTMR_DRV_IRQHandler(0U);
}

// The actual callback for the interrupt
volatile unsigned int scanCounter;
volatile unsigned int bufferCounter = 2;
volatile bool shouldWrite = false;
keys keepKeys = {.size=0};
keys newKeys = {.size=0};
keys keepMods = {.size=0};
keys newMods = {.size=0};
uint8_t prevBuffer[8];
void lptmr_isr_callback(void)
{
    // Efficient modulus by 64 (max val is 63)
    scanCounter &= 0x003F;

    // temps
    uint8_t rowC, rowB, rowA, colC, colB, colA;
    rowC = (scanCounter & 0x0020) >> 5;
    rowB = (scanCounter & 0x0010) >> 4;
    rowA = (scanCounter & 0x0008) >> 3;
    colC = (scanCounter & 0x0004) >> 2;
    colB = (scanCounter & 0x0002) >> 1;
    colA = (scanCounter & 0x0001);
    uint8_t indexRow = rowC*4 + rowB*2 + rowA;
    uint8_t indexCol = colC*4 + colB*2 + colA;

    if(qwertyMap[indexRow][indexCol] == KEY_NONE) {
    	scanCounter++;
    	//PRINTF("HOPPED!\n\r");
    	return;
    }

    // Arrange the select signals
    GPIO_DRV_WritePinOutput(hhkbRowC, rowC);
    GPIO_DRV_WritePinOutput(hhkbRowB, rowB);
    GPIO_DRV_WritePinOutput(hhkbRowA, rowA);
    GPIO_DRV_WritePinOutput(hhkbColC, colC);
    GPIO_DRV_WritePinOutput(hhkbColB, colB);
    GPIO_DRV_WritePinOutput(hhkbColA, colA);

	// Activate the Strobe signal with a little delay before reading inputs
	for(int i = 0; i < 10; i++) {
	    GPIO_DRV_WritePinOutput(hhkbStrobe, 0);
	}
    //GPIO_DRV_WritePinOutput(hhkbStrobe, 0);

	if(GPIO_DRV_ReadPinInput(hhkbKey) == 0) {
		if(GPIO_DRV_ReadPinInput(hhkbHys == 1)) {
			if(indexRow != 3 && indexRow != 5) {
				keepKeys.buf[keepKeys.size] = qwertyMap[indexRow][indexCol];
				keepKeys.size++;
			}
			else if(indexRow == 3) {
				switch(indexCol) {
				case (3 || 4 || 5 || 6):
					keepMods.buf[keepMods.size] = qwertyMap[indexRow][indexCol];
					keepMods.size++;
					break;
				default:
					keepKeys.buf[keepKeys.size] = qwertyMap[indexRow][indexCol];
					keepKeys.size++;
				}
			}
			else {
				switch(indexCol) {
				case (5 || 6 || 7):
					keepMods.buf[keepMods.size] = qwertyMap[indexRow][indexCol];
				keepMods.size++;
					break;
				default:
					keepKeys.buf[keepKeys.size] = qwertyMap[indexRow][indexCol];
					keepKeys.size++;
				}
			}

		}
		else {
					if(indexRow != 3 && indexRow != 5) {
						newKeys.buf[newKeys.size] = qwertyMap[indexRow][indexCol];
						newKeys.size++;
					}
					else if(indexRow == 3) {
						switch(indexCol) {
						case (3 || 4 || 5 || 6):
							newMods.buf[newMods.size] = qwertyMap[indexRow][indexCol];
						newMods.size++;
							break;
						default:
							newKeys.buf[newKeys.size] = qwertyMap[indexRow][indexCol];
							newKeys.size++;
						}
					}
					else {
						switch(indexCol) {
						case (5 || 6 || 7):
							newMods.buf[newMods.size] = qwertyMap[indexRow][indexCol];
						newMods.size++;
							break;
						default:
							newKeys.buf[newKeys.size] = qwertyMap[indexRow][indexCol];
							newKeys.size++;
						}
					}

				}
		//2g_keyboard.rpt_buf[bufferCounter] = qwertyMap[indexRow][indexCol];
		//bufferCounter++;
		//PRINTF("DETECTED %i %i SCANCOUNTER %i\n\r", indexRow, indexCol, scanCounter);
		//scanCounter++;
		//LED1_TOGGLE;

	}

	// Deactivate the strobe
	GPIO_DRV_WritePinOutput(hhkbStrobe, 1);

    scanCounter++;
	//if(qwertyMap[indexRow][indexCol++] == KEY_NONE)
	//      scanCounter++;

    // Once all the keys have been scanned clear out the buffer and
    // reset the variables
    if(scanCounter == 1) {
    	//PRINTF("reached 64!\n\r");
    	//shouldWrite = true;
    	LED1_TOGGLE;
    	for(int i = 0; i < 8; i++) {
    		prevBuffer[i] = g_keyboard.rpt_buf[i];
    	}
    	updateKeys(&keepKeys, &newKeys, &keepMods, &newMods, g_keyboard.rpt_buf);
    	shouldWrite = true;
    }

    return;
}

gpio_output_pin_user_config_t hhkbOutputPins[] = {
	{
		.pinName = hhkbRowA,
		.config.outputLogic = 1,
		.config.slewRate = kPortFastSlewRate,
		.config.isOpenDrainEnabled = false,
		.config.driveStrength = kPortLowDriveStrength,
	},
	{
		.pinName = hhkbRowB,
		.config.outputLogic = 1,
		.config.slewRate = kPortFastSlewRate,
		.config.isOpenDrainEnabled = false,
		.config.driveStrength = kPortLowDriveStrength,
	},
	{
		.pinName = hhkbRowC,
		.config.outputLogic = 1,
		.config.slewRate = kPortFastSlewRate,
		.config.isOpenDrainEnabled = false,
		.config.driveStrength = kPortLowDriveStrength,
	},
	{
		.pinName = hhkbColA,
		.config.outputLogic = 1,
		.config.slewRate = kPortFastSlewRate,
		.config.isOpenDrainEnabled = false,
		.config.driveStrength = kPortLowDriveStrength,
	},
	{
		.pinName = hhkbColB,
		.config.outputLogic = 1,
		.config.slewRate = kPortFastSlewRate,
		.config.isOpenDrainEnabled = false,
		.config.driveStrength = kPortLowDriveStrength,
	},
	{
		.pinName = hhkbColC,
		.config.outputLogic = 1,
		.config.slewRate = kPortFastSlewRate,
		.config.isOpenDrainEnabled = false,
		.config.driveStrength = kPortLowDriveStrength,
	},
	{
		.pinName = hhkbStrobe,
		.config.outputLogic = 1,
		.config.slewRate = kPortFastSlewRate,
		.config.isOpenDrainEnabled = false,
		.config.driveStrength = kPortLowDriveStrength,
	},
	{
		.pinName = GPIO_PINS_OUT_OF_RANGE,
	}
};

gpio_input_pin_user_config_t hhkbInputPins[] = {
	{
		.pinName = hhkbKey,
		.config.isPullEnable = true,
		.config.pullSelect = kPortPullUp,
		.config.isPassiveFilterEnabled = false,
		.config.interrupt = kPortIntDisabled
	},
	{
		.pinName = hhkbHys,
		.config.isPullEnable = true,
		.config.pullSelect = kPortPullUp,
		.config.isPassiveFilterEnabled = false,
		.config.interrupt = kPortIntDisabled
	},
	{
		.pinName = GPIO_PINS_OUT_OF_RANGE,
	}
};

// lptmr stuff
#define LPTMR_INSTANCE 0U
lptmr_state_t lptmrState;
lptmr_user_config_t lptmr0Config =
{
    .timerMode            = kLptmrTimerModeTimeCounter, /*! Use LPTMR in Time Counter mode */
    .freeRunningEnable    = false, /*! When hit compare value, set counter back to zero */
    .prescalerEnable      = false, /*! bypass prescaler */
	.prescalerClockSource = kClockLptmrSrcMcgIrClk, /*! use fast clock because 1kHz is too slow */
    .isInterruptEnabled   = true
};

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
void USB_App_Device_Callback(uint8_t event_type, void* val, void* arg);
uint8_t USB_App_Class_Callback(uint8_t request, uint16_t value, uint8_t ** data,
    uint32_t* size, void* arg);

/*****************************************************************************
 * Local Variables
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/******************************************************************************
 * @name:         KeyBoard_Events_Process
 *
 * @brief:        This function gets the input from keyboard, the keyboard
 *                does not include the code to filter the glitch on keys since
 *                it is just for demo
 *
 * @param:        None
 *
 * @return:       None
 *
 *****************************************************************************
 * This function sends the keyboard data depending on which key is pressed on
 * the board
 *****************************************************************************/
void KeyBoard_Events_Process(void)
{
    //static int32_t x = 0;
    //static enum { UP, DOWN} dir = UP;
	//PRINTF("HIT\n");
/*
    if(GPIO_DRV_ReadPinInput(switchPins[0].pinName) == 1) {
    	//GPIO_DRV_SetPinOutput(ledPins[0].pinName);
    	LED1_EN;
    }
    else {
    	//GPIO_DRV_ClearPinOutput(ledPins[0].pinName);
    }
*/
    //GPIO_DRV_SetPinOutput(ledPins[0].pinName);
/*
    switch(dir)
    {
    case UP:
        g_keyboard.rpt_buf[g_key_index] = KEY_NONE;
        x++;
        if (x > 100)
        {
            dir = DOWN;
        }
        break;
    case DOWN:
        g_keyboard.rpt_buf[g_key_index] = KEY_NONE;
        x--;
        if (x < 0)
        {
            dir = UP;
        }
        break;
    }
*/
   //if(shouldWrite == true) {
	//bool dupCheck = true;
	//for(int i = 0; i < 8; i++) {
	//	if(prevBuffer[i] != g_keyboard.rpt_buf[i]) {
	//		dupCheck = false;
	//		break;
	//	}
	//}
	//if(!dupCheck)
		(void) USB_Class_HID_Send_Data(g_keyboard.app_handle, HID_ENDPOINT, g_keyboard.rpt_buf, KEYBOARD_BUFF_SIZE);
   //shouldWrite = false;
   //}

    return;
}

/******************************************************************************
 *
 *    @name        USB_App_Device_Callback
 *
 *    @brief       This function handles the callback  
 *
 *    @param       handle : handle to Identify the controller
 *    @param       event_type       : value of the event
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************/
void USB_App_Device_Callback(uint8_t event_type, void* val, void* arg)
{
    UNUSED_ARGUMENT (arg)
    UNUSED_ARGUMENT (val)

    switch(event_type)
    {
    case USB_DEV_EVENT_BUS_RESET:
        g_keyboard.keyboard_init = FALSE;
        if (USB_OK == USB_Class_HID_Get_Speed(g_keyboard.app_handle, &g_keyboard.app_speed))
        {
            USB_Desc_Set_Speed(g_keyboard.app_handle, g_keyboard.app_speed);
        }
        break;
    case USB_DEV_EVENT_ENUM_COMPLETE:
        g_keyboard.keyboard_init = TRUE;
        g_process_times = 1;
        KeyBoard_Events_Process();/* run the cursor movement code */
        break;
    case USB_DEV_EVENT_ERROR:
        /* user may add code here for error handling 
         NOTE : val has the value of error from h/w*/
        break;
    default:
        break;
    }
    return;
}

/******************************************************************************
 *
 *    @name        USB_App_Class_Callback
 *
 *    @brief       This function handles USB-HID Class callback
 *
 *    @param       request  :  request type
 *    @param       value    :  give report type and id
 *    @param       data     :  pointer to the data
 *    @param       size     :  size of the transfer
 *
 *    @return      status
 *                  USB_OK  :  if successful
 *                  else return error
 *
 *****************************************************************************
 * This function is called whenever a HID class request is received. This
 * function handles these class requests.
 *****************************************************************************/
uint8_t USB_App_Class_Callback
(
    uint8_t request,
    uint16_t value,
    uint8_t ** data,
    uint32_t* size,
    void* arg
    )
{
    uint8_t error = USB_OK;

    uint8_t index = (uint8_t)((request - 2) & USB_HID_REQUEST_TYPE_MASK);
    if ((request == USB_DEV_EVENT_SEND_COMPLETE) && (value == USB_REQ_VAL_INVALID))
    {
        if ((g_keyboard.keyboard_init) && (arg != NULL))
        {
#if COMPLIANCE_TESTING
            uint32_t g_compliance_delay = 0x009FFFFF;
            while(g_compliance_delay--);
#endif

            //if(shouldWrite)
            	KeyBoard_Events_Process();/* run the cursor movement code */
        }
        return error;
    }

    /* index == 0 for get/set idle, index == 1 for get/set protocol */
    *size = 0;
    /* handle the class request */
    switch(request)
    {
    case USB_HID_GET_REPORT_REQUEST:
        *data = &g_keyboard.rpt_buf[0]; /* point to the report to send */
        *size = KEYBOARD_BUFF_SIZE; /* report size */
        break;

    case USB_HID_SET_REPORT_REQUEST:
        for (index = 0; index < KEYBOARD_BUFF_SIZE; index++)
        { /* copy the report sent by the host */
            //            g_keyboard.rpt_buf[index] = *(*data + index);
        }
        break;

    case USB_HID_GET_IDLE_REQUEST:
        /* point to the current idle rate */
        *data = &g_keyboard.app_request_params[index];
        *size = REQ_DATA_SIZE;
        break;

    case USB_HID_SET_IDLE_REQUEST:
        /* set the idle rate sent by the host */
        g_keyboard.app_request_params[index] = (uint8_t)((value & MSB_MASK) >>
        HIGH_BYTE_SHIFT);
        break;

    case USB_HID_GET_PROTOCOL_REQUEST:
        /* point to the current protocol code
         0 = Boot Protocol
         1 = Report Protocol*/
        *data = &g_keyboard.app_request_params[index];
        *size = REQ_DATA_SIZE;
        break;

    case USB_HID_SET_PROTOCOL_REQUEST:
        /* set the protocol sent by the host
         0 = Boot Protocol
         1 = Report Protocol*/
        g_keyboard.app_request_params[index] = (uint8_t)(value);
        break;
    }
    return error;
}

/******************************************************************************
 *
 *   @name        APP_init
 *
 *   @brief       This function is the entry for Keyboard Application
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * This function starts the keyboard application
 *****************************************************************************/
void APP_init(void)
{
    // GPIO Init
    //GPIO_DRV_Init(NULL, ledPins);
    //GPIO_DRV_Init(hhkbInputPins, hhkbOutputPins);
	GPIO_DRV_OutputPinInit(&hhkbOutputPins[0]);
	GPIO_DRV_OutputPinInit(&hhkbOutputPins[1]);
	GPIO_DRV_OutputPinInit(&hhkbOutputPins[2]);
	GPIO_DRV_OutputPinInit(&hhkbOutputPins[3]);
	GPIO_DRV_OutputPinInit(&hhkbOutputPins[4]);
	GPIO_DRV_OutputPinInit(&hhkbOutputPins[5]);
	GPIO_DRV_OutputPinInit(&hhkbOutputPins[6]);
	GPIO_DRV_InputPinInit(&hhkbInputPins[0]);
	GPIO_DRV_InputPinInit(&hhkbInputPins[1]);
	GPIO_DRV_ClearPinOutput(hhkbRowA);
	GPIO_DRV_ClearPinOutput(hhkbRowB);
	GPIO_DRV_ClearPinOutput(hhkbRowC);
	GPIO_DRV_ClearPinOutput(hhkbColA);
	GPIO_DRV_ClearPinOutput(hhkbColB);
	GPIO_DRV_ClearPinOutput(hhkbColC);
	GPIO_DRV_SetPinOutput(hhkbStrobe);
	//GPIO_DRV_SetPinOutput(kGpioLED1);
	scanCounter = 0;
	LED1_EN;

    hid_config_struct_t config_struct;
    OS_Mem_zero(&g_keyboard, sizeof(keyboard_global_variable_struct_t));
    OS_Mem_zero(&config_struct, sizeof(hid_config_struct_t));

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    g_keyboard.rpt_buf = (uint8_t*) OS_Mem_alloc_uncached_align(KEYBOARD_BUFF_SIZE, 32);
    if (NULL == g_keyboard.rpt_buf)
    {
        USB_PRINTF("\nMalloc error in APP_init\n");
        return;
    }
    OS_Mem_zero(g_keyboard.rpt_buf, KEYBOARD_BUFF_SIZE);
#endif
    USB_PRINTF("\nbegin to test keyboard\n");
    config_struct.hid_application_callback.callback = USB_App_Device_Callback;
    config_struct.hid_application_callback.arg = &g_keyboard.app_handle;
    config_struct.class_specific_callback.callback = USB_App_Class_Callback;
    config_struct.class_specific_callback.arg = &g_keyboard.app_handle;
    config_struct.desc_callback_ptr = &g_desc_callback;

    g_keyboard.app_speed = USB_SPEED_FULL;
    USB_Class_HID_Init(CONTROLLER_ID, &config_struct, &g_keyboard.app_handle);

    // Configure the timer and enable it
    LPTMR_DRV_Init(LPTMR_INSTANCE, &lptmrState, &lptmr0Config);
    LPTMR_DRV_InstallCallback(LPTMR_INSTANCE, lptmr_isr_callback);
    LPTMR_DRV_SetTimerPeriodUs(LPTMR_INSTANCE, 100);
    LPTMR_DRV_Start(LPTMR_INSTANCE);
}

/******************************************************************************
 *
 *   @name        APP_task
 *
 *   @brief
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * This function starts the keyboard application
 *****************************************************************************/
void APP_task()
{
    USB_HID_Periodic_Task();
}

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)

/*FUNCTION*----------------------------------------------------------------
 *
 * Function Name  : Main_Task
 * Returned Value : None
 * Comments       :
 *     First function called.  Calls Test_App
 *     callback functions.
 *
 *END*--------------------------------------------------------------------*/
void Main_Task(uint32_t param)
{
    UNUSED_ARGUMENT (param)
    APP_init();
}
#endif

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)

#if defined(FSL_RTOS_MQX)
void Main_Task(uint32_t param);
TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
    {   1L, Main_Task, 2500L, MQX_MAIN_TASK_PRIORITY, "Main", MQX_AUTO_START_TASK},
    {   0L, 0L, 0L, 0L, 0L, 0L}
};
#endif

#if (USE_RTOS)
static void Task_Start(void *arg)
{
    APP_init();
    for (;; )
    {
        ;
    }
}
#endif

#if defined(FSL_RTOS_MQX)
void Main_Task(uint32_t param)
#else

#if defined(__CC_ARM) || defined(__GNUC__)
int main(void)
#else
void main(void)
#endif

#endif
{
    hardware_init();
    OSA_Init();
    dbg_uart_init();

#if !(USE_RTOS)
    APP_init();
#else
    OS_Task_create(Task_Start, NULL, 9L, 1000L, "task_start", NULL);
#endif

    OSA_Start();
#if (!defined(FSL_RTOS_MQX))&(defined(__CC_ARM) || defined(__GNUC__))
    return 1;
#endif
}
#endif
/* EOF */
