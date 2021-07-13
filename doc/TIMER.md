# TIMER的使用

## 介绍

TIMER计时器主要用于和时间有关的操作，一般来说PWM是通过TIMER计时器实现的，不过TI-Drivers把PWM这块单独拿出来了。

## 例程

打开timerled.c

```c

/*
 *  ======== timerled.c ========
 */

#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Board Header file */
#include "ti_drivers_config.h"

/* Callback used for toggling the LED. */
void timerCallback(Timer_Handle myHandle);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    Timer_Handle timer0;
    Timer_Params params;

    /* Call driver init functions */
    GPIO_init();
    Timer_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn off user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);

    /* Setting up the timer in continuous callback mode that calls the callback
     * function every 1,000,000 microseconds, or 1 second.
     */
    Timer_Params_init(&params);
    params.period = 1000000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    if (timer0 == NULL) {
        /* Failed to initialized timer */
        while (1) {}
    }

    if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        while (1) {}
    }

    return (NULL);
}

/*
 * This callback is called every 1,000,000 microseconds, or 1 second. Because
 * the LED is toggled each time this function is called, the LED will blink at
 * a rate of once every 2 seconds.
 * */
void timerCallback(Timer_Handle myHandle)
{
    GPIO_toggle(CONFIG_GPIO_LED_0);
}
```

注意定时器是可以触发中断的，一般称为定时中断，例程中给出了示例。

## 用法

1.  Timer_init()

2.  Timer_Params_init(Timer_Params* params)

3.  细化配置params

    1.  timerMode：时间模式

        命名规则

        -   开头：Timer_
        -   运行方法：
            -   ONESHOT_：单次运行，定时器结束后不会自动重启
            -   CONTINUOUS_：持续运行，会自动重启
            -   FREE_：不阻塞不中断，仅作计时不定时
        -   阻塞：
            -   CALLBACK：非阻塞回调运行
            -   BLOCKING：阻塞运行
            -   RUNNING：不阻塞但也不会回调，仅作计时器

    2.  periodUnits：单位

        命名规则

        -   开头：Timer_PERIOD_
        -   单位：
            -   US：微秒
            -   HZ：赫兹
            -   COUNTS：使用滴答计时器或指定的周期，因不同板定

    3.  timerCallback：回调函数

    4.  period：周期，以periodUnits为单位。

4.  Timer_Handle handle = Timer_open(index, &params)

5.  Timer_start(handle)启动

## 例子外

还可以使用Timer_end(handle)的方式终止计时

## 测试

尝试写一个定时串口发送的程序，也许可以尝试通过串口中断或按键控制发送周期。