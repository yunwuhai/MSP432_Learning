/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSP_EXP432P401R
 *  by the SysConfig tool.
 */

#include <stddef.h>

#ifndef DeviceFamily_MSP432P401x
#define DeviceFamily_MSP432P401x
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"

/*
 *  ============================= Display =============================
 */

#include <ti/display/Display.h>
#include <ti/display/DisplayUart.h>

#define Display_UARTBUFFERSIZE 1024
static char displayUARTBuffer[Display_UARTBUFFERSIZE];

DisplayUart_Object displayUartObject;

const DisplayUart_HWAttrs displayUartHWAttrs = {
    .uartIdx      = PC_UART,
    .baudRate     = 115200,
    .mutexTimeout = (unsigned int)(-1),
    .strBuf       = displayUARTBuffer,
    .strBufLen    = Display_UARTBUFFERSIZE
};

const Display_Config Display_config[] = {
    /* PC_UART_Display */
    /* XDS110 UART */
    {
        .fxnTablePtr = &DisplayUartMin_fxnTable,
        .object      = &displayUartObject,
        .hwAttrs     = &displayUartHWAttrs
    },
};

const uint_least8_t Display_count = 1;


/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOMSP432.h>

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* BUTTON_LEFT_GPIO : LaunchPad Button S1 (Left) */
    GPIOMSP432_P1_1 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING,
    /* BUTTON_RIGHT_GPIO : LaunchPad Button S2 (Right) */
    GPIOMSP432_P1_4 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING,
    /* SINGLE_RED_GPIO : LaunchPad LED 1 Red */
    GPIOMSP432_P1_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *
 *  NOTE: Unused callback entries can be omitted from the callbacks array to
 *  reduce memory usage by enabling callback table optimization
 *  (GPIO.optimizeCallbackTableSize = true)
 */
extern void LeftButtonCallback(uint_least8_t index);
extern void RightButtonCallback(uint_least8_t index);

GPIO_CallbackFxn gpioCallbackFunctions[] = {
    /* BUTTON_LEFT_GPIO : LaunchPad Button S1 (Left) */
    LeftButtonCallback,
    /* BUTTON_RIGHT_GPIO : LaunchPad Button S2 (Right) */
    RightButtonCallback,
    /* SINGLE_RED_GPIO : LaunchPad LED 1 Red */
    NULL,
};

/*
 *  ======== GPIOMSP432_config ========
 */
const GPIOMSP432_Config GPIOMSP432_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = 3,
    .numberOfCallbacks = 3,
    .intPriority = (~0)
};


/*
 *  =============================== PWM ===============================
 */

#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerMSP432.h>

/* include MSP432 driverlib definitions */
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/timer_a.h>

#define CONFIG_PWM_COUNT 3

/*
 *  ======== pwmMSP432Objects ========
 */
PWMTimerMSP432_Object pwmTimerMSP432Objects[CONFIG_PWM_COUNT];

/*
 *  ======== pwmMSP432HWAttrs ========
 */
const PWMTimerMSP432_HWAttrsV2 pwmTimerMSP432HWAttrs[CONFIG_PWM_COUNT] = {
    /* RGB_RED_PWM */
    /* LaunchPad LED 2 Red */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P2_0_TA1CCR3A, /* P2_0 */
    },
    /* RGB_GREEN_PWM */
    /* LaunchPad LED 2 Green */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P2_1_TA1CCR2A, /* P2_1 */
    },
    /* RGB_BLUE_PWM */
    /* LaunchPad LED 2 Blue */
    {
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .pwmPin = PWMTimerMSP432_P2_2_TA1CCR1A, /* P2_2 */
    },
};

/*
 *  ======== PWM_config ========
 */
const PWM_Config PWM_config[CONFIG_PWM_COUNT] = {
    /* RGB_RED_PWM */
    /* LaunchPad LED 2 Red */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[RGB_RED_PWM],
        .hwAttrs = &pwmTimerMSP432HWAttrs[RGB_RED_PWM]
    },
    /* RGB_GREEN_PWM */
    /* LaunchPad LED 2 Green */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[RGB_GREEN_PWM],
        .hwAttrs = &pwmTimerMSP432HWAttrs[RGB_GREEN_PWM]
    },
    /* RGB_BLUE_PWM */
    /* LaunchPad LED 2 Blue */
    {
        .fxnTablePtr = &PWMTimerMSP432_fxnTable,
        .object = &pwmTimerMSP432Objects[RGB_BLUE_PWM],
        .hwAttrs = &pwmTimerMSP432HWAttrs[RGB_BLUE_PWM]
    },
};

const uint_least8_t PWM_count = CONFIG_PWM_COUNT;


/*
 *  =============================== Power ===============================
 */

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerMSP432.h>
extern void PowerMSP432_initPolicy(void);
extern void PowerMSP432_sleepPolicy(void);

const PowerMSP432_ConfigV1 PowerMSP432_config = {
    .policyInitFxn         = PowerMSP432_initPolicy,
    .policyFxn             = PowerMSP432_sleepPolicy,
    .initialPerfLevel      = 2,
    .enablePolicy          = true,
    .enablePerf            = true,
    .enableParking         = false,
    .resumeShutdownHookFxn = NULL,
    .customPerfLevels      = NULL,
    .numCustom             = 0,
    .useExtendedPerf       = false,
    .configurePinHFXT      = false,
    .HFXTFREQ              = 0,
    .bypassHFXT            = false,
    .configurePinLFXT      = false,
    .bypassLFXT            = false,
    .LFXTDRIVE             = 0,
    .enableInterruptsCS    = false,
    .priorityInterruptsCS  = (~0),
    .isrCS                 = NULL
};


/*
 *  =============================== UART ===============================
 */

#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTMSP432.h>
#include <ti/devices/msp432p4xx/driverlib/interrupt.h>
#include <ti/devices/msp432p4xx/driverlib/uart.h>

#define CONFIG_UART_COUNT 1

UARTMSP432_Object uartMSP432Objects[CONFIG_UART_COUNT];

static const UARTMSP432_BaudrateConfig uartMSP432Baudrates[] = {
    /* {baudrate, input clock, prescalar, UCBRFx, UCBRSx, oversampling} */
    { 115200, 3000000, 1, 10, 0, 1 },
    { 115200, 6000000, 3, 4, 2, 1 },
    { 115200, 12000000, 6, 8, 32, 1 },
    { 115200, 24000000, 13, 0, 37, 1 },
};

static unsigned char uartMSP432RingBuffer0[32];


static const UARTMSP432_HWAttrsV1 uartMSP432HWAttrs[CONFIG_UART_COUNT] = {
  {
    .baseAddr           = EUSCI_A0_BASE,
    .intNum             = INT_EUSCIA0,
    .intPriority        = (~0),
    .clockSource        = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
    .bitOrder           = EUSCI_A_UART_LSB_FIRST,
    .numBaudrateEntries = sizeof(uartMSP432Baudrates) /
                          sizeof(UARTMSP432_BaudrateConfig),
    .baudrateLUT        = uartMSP432Baudrates,
    .ringBufPtr         = uartMSP432RingBuffer0,
    .ringBufSize        = sizeof(uartMSP432RingBuffer0),
    .rxPin              = UARTMSP432_P1_2_UCA0RXD,
    .txPin              = UARTMSP432_P1_3_UCA0TXD,
    .errorFxn           = NULL
  },
};

const UART_Config UART_config[CONFIG_UART_COUNT] = {
    {   /* PC_UART */
        .fxnTablePtr = &UARTMSP432_fxnTable,
        .object      = &uartMSP432Objects[0],
        .hwAttrs     = &uartMSP432HWAttrs[0]
    },
};

const uint_least8_t UART_count = CONFIG_UART_COUNT;


/*
 *  =============================== Button ===============================
 */
#include <ti/drivers/apps/Button.h>

Button_Object ButtonObjects[2];

static const Button_HWAttrs ButtonHWAttrs[2] = {
    /* BUTTON_LEFT */
    /* LaunchPad Button S1 (Left) */
    {
        .gpioIndex = BUTTON_LEFT_GPIO
    },
    /* BUTTON_RIGHT */
    /* LaunchPad Button S2 (Right) */
    {
        .gpioIndex = BUTTON_RIGHT_GPIO
    },
};

const Button_Config Button_config[2] = {
    /* BUTTON_LEFT */
    /* LaunchPad Button S1 (Left) */
    {
        .object = &ButtonObjects[BUTTON_LEFT],
        .hwAttrs = &ButtonHWAttrs[BUTTON_LEFT]
    },
    /* BUTTON_RIGHT */
    /* LaunchPad Button S2 (Right) */
    {
        .object = &ButtonObjects[BUTTON_RIGHT],
        .hwAttrs = &ButtonHWAttrs[BUTTON_RIGHT]
    },
};

const uint_least8_t Button_count = 2;


/*
 *  =============================== LED ===============================
 */
#include <ti/drivers/apps/LED.h>

LED_Object LEDObjects[4];

static const LED_HWAttrs LEDHWAttrs[4] = {
    /* SINGLE_RED */
    /* LaunchPad LED 1 Red */
    {
        .type = LED_GPIO_CONTROLLED,
        .index = SINGLE_RED_GPIO,
    },
    /* RGB_RED */
    /* LaunchPad LED 2 Red */
    {
        .type = LED_PWM_CONTROLLED,
        .index = RGB_RED_PWM,
    },
    /* RGB_GREEN */
    /* LaunchPad LED 2 Green */
    {
        .type = LED_PWM_CONTROLLED,
        .index = RGB_GREEN_PWM,
    },
    /* RGB_BLUE */
    /* LaunchPad LED 2 Blue */
    {
        .type = LED_PWM_CONTROLLED,
        .index = RGB_BLUE_PWM,
    },
};

const LED_Config LED_config[4] = {
    /* SINGLE_RED */
    /* LaunchPad LED 1 Red */
    {
        .object = &LEDObjects[SINGLE_RED],
        .hwAttrs = &LEDHWAttrs[SINGLE_RED]
    },
    /* RGB_RED */
    /* LaunchPad LED 2 Red */
    {
        .object = &LEDObjects[RGB_RED],
        .hwAttrs = &LEDHWAttrs[RGB_RED]
    },
    /* RGB_GREEN */
    /* LaunchPad LED 2 Green */
    {
        .object = &LEDObjects[RGB_GREEN],
        .hwAttrs = &LEDHWAttrs[RGB_GREEN]
    },
    /* RGB_BLUE */
    /* LaunchPad LED 2 Blue */
    {
        .object = &LEDObjects[RGB_BLUE],
        .hwAttrs = &LEDHWAttrs[RGB_BLUE]
    },
};

const uint_least8_t LED_count = 4;


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    Board_initHook();
}
