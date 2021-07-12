# GPIO的使用

[TOC]

## 介绍

经过了前面两章的学习，其实你已经拥有了一定自学这些功能的能力了，故在本章及之后的章节，我的讲解可能会逐渐变得简洁。

GPIO的知识其实很简单，准确说应该是所有章节中最简单的，如果你学习过数电，那么应该对逻辑电平有所了解，GPIO可以说就是一个用来控制芯片引脚输出不同逻辑电平的外设。当然，我在这里不会太多讲这些基础知识，我的重点仍然是完成编程即可。

## 重点

GPIO常用的两种功能：输入、输出。其中输入，功能其实就是通过引脚去检测外部的电平，而输出则是改变自身引脚的电平。如果加上了时钟，我们就可以完成一些特殊的操作，例如如果我们把高电平理解为逻辑1，低电平理解为逻辑0，那么我们把一段时间进行均匀划分，并在每个划分区间内进行一次电平检测，即可得到一串有先后的1和0，从而完成了数据的传输。这也是之前我们串口的做法。而我们如果把电平的高低变化，以一定频率一定比例进行组合，即可完成对能量的控制，实现如调光、调声、调速等功能，这些则是完成了控制。因此我们知道了GPIO可以实现的功能主要为两个方向：一是通信，二是控制。事实上其它外设的功能基本也无非是做这两件事情，只不过它们把一些处理以硬件电路的方式进行搭建了，因而使用那些外设我们就可以得到更加简单于高效的使用效果。但是哪怕没有那些外设，只要我们知道这些通信或控制的物理原理，我们基本上都可以通过GPIO来完成这些效果。

## 硬件

事实上我们能看到MSP432P401R这块芯片的所有引脚本质上应该都有GPIO的功能，不过硬件已经设计好了，主要使用那些通过排针引出来的引脚就好了。TI这款红色的板子并没有完整地焊接所有的引出引脚，可以看到在最下面有两排洞，它们也是可以被焊接的引脚，你可以根据需要使用排针或者排母进行焊接，就像我这样：

<img src="../pic/GPIO/QQ图片20210712194212.jpg" style="zoom:25%;" />

关于电路焊接技巧的相关知识我不在此介绍，如果感兴趣可以在网上搜索，焊接不是简单的把锡糊在焊点上，多学习一些技巧对焊接效率以及焊点性能都会有很大提升。

## BSP

在上一章我们已经讲解了BSP的相关概念，在这里我们再重新关注一下我们这个开发板的板载资源，因为本章之后我们即会完成本开发板的完整BSP封装（并不是说学会了GPIO就可以完成完整BSP，只是因为这一个板子上拥有的资源仅需要GPIO和串口即可完成封装）

### 分析

#### 仿真器-单片机

如果我们要分析一下这个板子，第一步其实就是可以把这个板子划分为两个部分：仿真器部分和单片机部分。这两个部分的连接内容主要有四个：电源、复位、串口、仿真。

电源很好理解，即GND、5V、3.3V三个脚。

复位引脚是RST，这个引脚拉低了之后可以让芯片重新启动。

串口我们上一章讲过了，即RXD和TXD。

剩余的引脚就是仿真引脚了，通过它们的命名可以知道是JTAG引脚。

以上的功能中，在编程里我们需要设置的仅有串口（事实上还需要配置JTAG引脚的，不过那个好像不是在程序里配置的，所以不用管）。而电源和复位是硬件电路关注的东西，不用在编程中关注它们。

#### 按键

可以看到整个板子连接了三个按键，上面一个，左右各一个。其中上面那个是复位的按键，可以不用管，而左右的两个按键则是我们可以控制的了，等会我们会对其进行配置。

#### LED

LED也就是发光二极管，在这个板子上有两颗，其中一颗是红色单色LED，另一个是RGB三色LED，可以关注板子上中下方的那四个跳线帽，这四个LED通过跳线帽与单片机相连。等会我们也会对其进行配置。

## GPIO的参数

GPIO常用的参数有：

-   输入或输出
-   输出电平
-   上拉或下拉电阻
-   推挽输出或开漏输出

其中前两个从字面意思可以理解，第三个上拉或下拉电阻用于稳定电平，因为比如在如果某个引脚设为输入时，它在没有与任何物体进行连接的时候，它的电平是未知且不稳定的，我们此时应该为它添加上拉电阻或下拉电阻让它的电平稳定。主要功能差不多是如此，如果想要了解更多请自行百度。

而第四个推挽和开漏的区别在于两者对于外部电路的驱动力，具体原理有点复杂，建议百度一下。一般而言我们都是使用推挽输出，开漏输出主要用于需要较大电流的控制或者一些特殊线路（如I2C），另外需要注意，如果使用开漏输出则必须接外部上拉才能得到高电平（如果不接上拉而进行高电平输出的话，线路呈高阻态）。

## 例程

关于按键和LED的例程，我们应该可以找到两个，其中一个是gpiointerrupt，另一个是buttonled，在这一章里面我们暂时只讲gpiointerrupt，因为buttonled它用了一个TI-Drivers的更加高级的封装，这个我们在最后提一下。

关于TI RTOS的部分，都是一样的，而关于那块的分析我们暂时先不讲。

```c
/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0.
 */
void gpioButtonFxn0(uint_least8_t index)
{
    /* Clear the GPIO interrupt and toggle an LED */
    GPIO_toggle(CONFIG_GPIO_LED_0);
}

/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_1.
 *  This may not be used for all boards.
 */
void gpioButtonFxn1(uint_least8_t index)
{
    /* Clear the GPIO interrupt and toggle an LED */
    GPIO_toggle(CONFIG_GPIO_LED_1);
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();

    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* install Button callback */
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);

    /* Enable interrupts */
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on CONFIG_GPIO_BUTTON1.
     */
    if (CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1) {
        /* Configure BUTTON1 pin */
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        /* Install Button callback */
        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }

    return (NULL);
}
```

### GPIO_init

以上代码我们直接从mainThread开始看，首先是GPIO_init()，根据我们UART的经验，这个就是系统初始化，每次都要用，但是不用管它的具体内容。

### GPIO_setConfig

这个函数的功能从名字上就不难知道是设置GPIO的模式，相对于UART，它的地位类似于UART_Params_init和UART_Open的结合（其实只是Open部分，因为GPIO的配置不需要像UART那样一堆参数，所以它的参数是直接手动写的）。

而对于这个函数的参数，第一个是index，这个在ti_drivers_config中，之前我们说过这种写法了，第二个参数就是它的功能了。

