/*************************************************************************************
 * @Description  : 
 * @Version      : 
 * @Author       : YunWuHai
 * @Date         : 2021-07-16 18:30:16
 * @LastEditors  : YunWuHai
 * @LastEditTime : 2021-07-16 18:53:45
 * @FilePath     : \MyLib\BSP\MSP432P401R\BSP_init.c
 * @Copyright (C) 2021 YunWuHai. All rights reserved.
 *************************************************************************************/
#include "BSP_init.h"

void Board_initHook(void)
{
    Display_init();
    hDisplay = Display_open(Display_Type_UART, NULL);
    
    GPIO_init();
    LED_init();
    hLEDs[SINGLE_RED] = LED_open(SINGLE_RED, NULL);
    hLEDs[RGB_RED] = LED_open(RGB_RED, NULL);
    hLEDs[RGB_GREEN] = LED_open(RGB_GREEN, NULL);
    hLEDs[RGB_BLUE] = LED_open(RGB_BLUE, NULL);

    Button_init();
    hButtons[BUTTON_LEFT] = Button_open(BUTTON_LEFT, LeftButtonCallback, NULL);
    hButtons[BUTTON_RIGHT] = Button_open(BUTTON_RIGHT, RightButtonCallback, NULL);

    BSP_init_hook();
}


void __attribute__((weak)) LeftButtonCallback(Button_Handle handle, Button_EventMask events)
{
    
}
void __attribute__((weak)) RightButtonCallback(Button_Handle handle, Button_EventMask events)
{

}

void __attribute__((weak)) BSP_init_hook(void)
{

}
