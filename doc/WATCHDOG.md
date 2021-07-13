# WATCHDOG的使用

## 介绍

WatchDog，也被称为看门狗，本质上是一个计数器或定时器，功能是保障系统正常运行，运行方式为看门狗计数器不断计数自增或自减，当达到一定值后就会重启整个系统，我们将此称之为看门狗饿死，如果为了不重启系统，我们就需要经常重置计数器防止达到指定的重启值，这个过程也被称为喂狗。如果我们的系统进入了某种死循环，或者出错了，我们的喂狗程序可能就无法启动，那么系统就会判断我们的程序出问题了，接着就会触发看门狗中断重启系统，这就是看门狗用于保障系统正常运行的方式。

## 例程

打开watchdog程序：

```c
/*
 *  ======== watchdog.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/Watchdog.h>

/* Driver configuration */
#include "ti_drivers_config.h"

#define TIMEOUT_MS      1000
#define SLEEP_US        500000

/*
 *  ======== watchdogCallback ========
 */
void watchdogCallback(uintptr_t watchdogHandle)
{
    /*
     * If the Watchdog Non-Maskable Interrupt (NMI) is called,
     * loop until the device resets. Some devices will invoke
     * this callback upon watchdog expiration while others will
     * reset. See the device specific watchdog driver documentation
     * for your device.
     */
    while (1) {}
}

/*
 *  ======== gpioButtonIsr ========
 */
void gpioButtonIsr(uint_least8_t index)
{
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /*
     * Simulate the application being stuck in an ISR. This ISR can be
     * preempted by the watchdog Non-Maskable Interrupt (NMI).
     */
    while (1) {}
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    Watchdog_Handle watchdogHandle;
    Watchdog_Params params;
    uint32_t        reloadValue;

    /* Call driver init functions */
    GPIO_init();
    Watchdog_init();

    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonIsr);

    /* Open a Watchdog driver instance */
    Watchdog_Params_init(&params);
    params.callbackFxn = (Watchdog_Callback) watchdogCallback;
    params.debugStallMode = Watchdog_DEBUG_STALL_ON;
    params.resetMode = Watchdog_RESET_ON;

    watchdogHandle = Watchdog_open(CONFIG_WATCHDOG_0, &params);
    if (watchdogHandle == NULL) {
        /* Error opening Watchdog */
        while (1) {}
    }

    /*
     * The watchdog reload value is initialized during the
     * Watchdog_open() call. The reload value can also be
     * set dynamically during runtime.
     *
     * Converts TIMEOUT_MS to watchdog clock ticks.
     * This API is not applicable for all devices.
     * See the device specific watchdog driver documentation
     * for your device.
     */
    reloadValue = Watchdog_convertMsToTicks(watchdogHandle, TIMEOUT_MS);

    /*
     * A value of zero (0) indicates the converted value exceeds 32 bits
     * OR that the API is not applicable for this specific device.
     */
    if (reloadValue != 0) {
        Watchdog_setReload(watchdogHandle, reloadValue);
    }

    /* Turn on CONFIG_GPIO_LED_0 and enable CONFIG_GPIO_BUTTON_0 interrupt */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    while (1) {

        /*
         * Disabling power policy will prevent the device from entering
         * low power state. The device will stay awake when the CPU is
         * idle.
         */
        Power_disablePolicy();

        /* Sleep for SLEEP_US before clearing the watchdog */
        usleep(SLEEP_US);
        Watchdog_clear(watchdogHandle);
        GPIO_toggle(CONFIG_GPIO_LED_0);

        /*
         * Enabling power policy will allow the device to enter a low
         * power state when the CPU is idle. How the watchdog peripheral
         * behaves in a low power state is device specific.
         */
        Power_enablePolicy();

        /* Sleep for SLEEP_US before clearing the watchdog */
        usleep(SLEEP_US);
        Watchdog_clear(watchdogHandle);
        GPIO_toggle(CONFIG_GPIO_LED_0);
    }
}
```

### 使用

1.  Watchdog_init()
2.  Watchdog_Params_init()
3.  参数配置
    1.  resetMode：是否启用复位，MSP432可以使用非复位的看门狗
    2.  debugStallMode:调试断点处停止看门狗，如果不开启可能导致看门狗一直开启而在调试断点时自动复位，而无法调试
    3.  callbackFxn：回调函数，看门狗饿死前会执行该函数
    4.  custom：自定义，不管
4.  Watchdog_open()
5.  Watchdog_convertMsToTicks()：一个计算函数，计算内容为毫秒与tick的转换（这样我们就不用去算看门狗的tick了，而直接通过这个函数来计算就行）
6.  Watchdog_setReload()：设置重装值，当看门狗超过了此处设置的重装值的tick后还没有被喂狗，那么就会饿死，这个重装值Ticks可以通过前面那个Watchdog_convertMsToTick来算
7.  Watchdog_clear()：清空看门狗计数器，也就是喂狗程序

一般而言我们可以把一些不能弥补的错误发生后写入一个死循环，那么一旦触发了这个错误，死循环中我们不喂狗就可以把狗饿死从而重启系统。不过需要注意，当你决定用看门狗之后，一定不要忘了喂它，且不要用于长阻塞程序，不然稍微多一点的阻塞都可能导致看门狗饿死。

## 测试

开启一条狗，然后喂喂它吧，当然你也可以尝试使用看门狗中断看看会发生什么。

