# Capture的使用

## 介绍

这个是一个高速的边沿捕获器，在介绍里面说它可以用于检测GPIO上的边沿触发事件，不过这个文档说得很笼统，根本看不懂，所以这个功能需要看一下主程序，最好运行一下，否则确实很难理解。总体来说可以直接把它当作一个普通的GPIO中断，但是这个中断会给出时间周期间隔。简单点讲，如果我们设置一个5KHz的PWM信号，使用Capture且设置了单位为Hz后，去检测这个PWM，将会得到5000的数据。

## 使用

1.  Capture_init
2.  Capture_Params_init
3.  细调
    1.  mode：检测模式，即边沿触发模式，上升、下降或两者或上升开始下降停止或相反。
    2.  CallbackFxn：回调函数，第一个参数是句柄，第二个是回调时周期内检测到的电平数
    3.  PeriodUnits：周期单位，微秒、赫兹、计时器数、纳秒
4.  Capture_open
5.  Capture_start
6.  Capture_stop
7.  Capture_close

## 注意

为了保证Capture的高速和稳定，请不要在中断中使用长时间中断的函数，最好以信号量通知和全局变量的方式将数据传到外面去处理。详情可以参考例程，关于其中信号量的部分我在后面稍微讲一下，主要是没找到手册，要依靠看库函数来讲。

