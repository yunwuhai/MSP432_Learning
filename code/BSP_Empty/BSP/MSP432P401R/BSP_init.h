/*************************************************************************************
 * @Description  : 板级支持包
 * @Version      : 
 * @Author       : YunWuHai
 * @Date         : 2021-07-16 18:30:07
 * @LastEditors  : YunWuHai
 * @LastEditTime : 2021-07-16 18:52:43
 * @FilePath     : \MyLib\BSP\MSP432P401R\BSP_init.h
 * @Copyright (C) 2021 YunWuHai. All rights reserved.
 *************************************************************************************/
#ifndef _BSP_INIT_H_
#define _BSP_INIT_H_

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/apps/Button.h>
#include <ti/drivers/apps/LED.h>
#include <ti/display/Display.h>

#include "ti_drivers_config.h"

Button_Handle    hButtons[2];
LED_Handle       hLEDs[4];
Display_Handle   hDisplay;

void LeftButtonCallback(Button_Handle handle, Button_EventMask events);
void RightButtonCallback(Button_Handle handle, Button_EventMask events);
void BSP_init_hook(void);   // 自定义初始化函数

#endif
