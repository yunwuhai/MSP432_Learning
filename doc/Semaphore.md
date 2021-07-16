# Semaphore的使用

## 介绍

信号量功能，没有出现在手册里面，也没有单独的例程（我没看到），所以这里大概讲一下它的使用。一般而言可以把这个功能理解成一个布尔值，用于对工作时序进行调整，例如防止两个线程同时操作同一个外设导致出问题等。当然它的使用很广泛，像是SPI示例里面那个同步好像也可以使用这个东西。

## 使用

Semaphore信号量的库函数引用是：`#include <ti/drivers/dpl/SemaphoreP.h>`，可以发现它也是TI-Drivers的东西。所以它的配置也和其它外设配置很像。

1.  SemaphoreP_Params_init
2.  细调：
    1.  mode：模式，二进制信号量或统计信号量
    2.  callback：回调
3.  SemaphoreP_create：创建信号量
4.  SemaphoreP_pend：等待信号量，阻塞直到有信号发出或到了超时时间
5.  SemaphoreP_post：发出信号，将会激活等待信号的pend函数

## 其它

其它还有一些函数，因为时间原因我就不去看了，如果有需要可以去自行查看一下。

