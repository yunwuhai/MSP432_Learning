# TI-MSP432学习笔记

*注意，本笔记主要针对的是MSP432P401R的芯片，但因为其中也使用了TI-Drivers，该驱动库根据TI官方描述拥有较高的可移植性，故可一定程度上作为其它TI单片机的参考。本笔记为个人学习笔记，不具有官方效力，可能会有遗漏错误，不应作为权威使用手册看待，如有问题欢迎指正。*

## 注意

**因为是笔记，写得比较随性，故有些操作请将上下文看完后再进行操作，否则我有时候举得例子是为了作反例使用，可能造成未知的不良后果。另外请严格按照顺序进行阅读，虽然从总体上我笔记的顺序是按照功能模块进行分类的，但是有一些不直属于功能的关键知识我在前面说过后可能就不会在后面重述了。**

## 目录

[CCS安装和使用](./doc/START.md)

[UART](./doc/UART.md)

[GPIO](./doc/GPIO.md)

[PWM](./doc/PWM.md)

[TIMER](./doc/TIMER.md)

[WATCHDOG](./doc/WATCHDOG.md)

[SPI](./doc/SPI.md)

[I2C](./doc/I2C.md)

[SD](./doc/SD.md)

[ADC](./doc/ADC.md)

[Capture](./doc/Capture.md)

[Semaphore](./doc/Semaphore.md)

[RTOS](./doc/RTOS.md)

[后续](./doc/More.md)

## Code文件夹

下面放了一个我封装好的针对MSP432P401R的工程模板，针对CCS平台。如果要使用只需将该模板导入即可，导入前注意保留副本。

或将其中的main、mainThread、Standard.syscfg导入自己工程，并把对应内容替换，同时将BSP文件夹也放到自己工程的根目录下即可。

针对该模板的自定义步骤（实现自己的功能）我已经标好了，修改完成后即可添加设计自己的功能即可。

##### 协议

本项目遵守GPL协议

##### 作者：云雾海

##### 联系方式：872712633@qq.com

