/*
 *  ======== mainThread.c ========
 */

/*
 *  ======== STEP1������Standard.syscfg�����ݣ����ޱ�Ҫ����ɾ�����е����� ========
 */

/* ��׼�� */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* �弶����� */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/apps/Button.h>
#include <ti/drivers/apps/LED.h>
#include <ti/display/Display.h>

#include "ti_drivers_config.h"
#include "BSP/MSP432P401R/BSP_init.h"
/*
 * ��BSP_init�д���LED��Button��Display��ʵ�����������Button��LED���������ʽ���ڣ��±����ʹ�ú궨����з���
 * �����Ҫ�������Button��LED��Display��������������
 * �����ǵ��÷�����Ҳ����ֱ�Ӷ�Դ��鿴��
 * Button =�� hButtons[2] == �±�궨�� =�� BUTTON_LEFT��BUTTON_RIGHT
 * LED =�� hLEDs[4] == �±�궨�� =�� SINGLE_RED��RGB_RED��RGB_GREEN��RGB_BLUE
 * Display =�� hDisplay
 */


/*
 *  ======== STEP2:ʹ��Ctrl+/��ݼ���������ȡ��ע�� ========
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
 *  ======== STEP3:����������������� ========
 */


/*
 * ======== STEP4:�ض����ʼ������BSP_init_hook���ú�����Board_initHook�Ļص� ========
 */


// �����ǰ����жϻص���ʹ�÷�����ο��ҵıʼ���GPIO���֣�������Լ��������ɾ��
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
