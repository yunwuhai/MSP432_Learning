/*
 *  ======== mainThread.c ========
 */

/*
 *  ======== STEP1：配置Standard.syscfg的内容，如无必要请误删改现有的配置 ========
 */

/* 标准库 */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* 板级必须库 */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/apps/Button.h>
#include <ti/drivers/apps/LED.h>
#include <ti/display/Display.h>

#include "ti_drivers_config.h"
#include "BSP/MSP432P401R/BSP_init.h"
/*
 * 在BSP_init中存在LED、Button和Display的实例句柄，其中Button和LED以数组的形式存在，下标可以使用宏定义进行访问
 * 如果需要添加其它Button、LED或Display，请另外命名。
 * 下面是调用方法，也可以直接读源码查看：
 * Button =》 hButtons[2] == 下标宏定义 =》 BUTTON_LEFT、BUTTON_RIGHT
 * LED =》 hLEDs[4] == 下标宏定义 =》 SINGLE_RED、RGB_RED、RGB_GREEN、RGB_BLUE
 * Display =》 hDisplay
 */


/*
 *  ======== STEP2:使用Ctrl+/快捷键根据需求取消注释 ========
 */
//#include <ti/drivers/UART.h>
//#include <ti/drivers/I2C.h>
//#include <ti/drivers/SPI.h>
//#include <ti/drivers/Capture.h>
//#include <ti/drivers/ADC.h>
//#include <ti/drivers/ADCBuf.h>
//#include <ti/drivers/SD.h>
//#include <ti/drivers/SDFatFS.h>
//#include <ti/drivers/Timer.h>
//#include <ti/drivers/Watchdog.h>

/*
 *  ======== STEP3:根据需求添加其它库 ========
 */


/*
 * ======== STEP4:重定义初始化函数BSP_init_hook，该函数是Board_initHook的回调 ========
 */


// 下面是按键中断回调，使用方法请参考我的笔记中GPIO部分，请根据自己需求进行删改
void LeftButtonCallback(Button_Handle handle, Button_EventMask events)
{
    if(events &= Button_EV_LONGPRESSED)
    {
        Display_printf(hDisplay, 0, 0, "Left event happend!\n");
        LED_startBlinking(hLEDs[SINGLE_RED], 500, 10);
    }
}
void RightButtonCallback(Button_Handle handle, Button_EventMask events)
{
    if(events &= Button_EV_LONGPRESSED)
    {
        Display_printf(hDisplay, 0, 0, "Right event happend!\n");
    }
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{

    for(;;)
    {

    }
}
