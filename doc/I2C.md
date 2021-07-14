# I2C的使用

## 注意

因为时间原因，从此章开始，我将不再以程序为基础进行介绍了，仅介绍这些功能的总体用法。不过相信有了前面几章的学习，你已经拥有了自己看懂这些程序的能力了。

## 介绍

I2C也是一种通信总线，和SPI一样，它在于元件通信方面有较多的应用，可以参考百度百科：

https://baike.baidu.com/item/I2C%E6%80%BB%E7%BA%BF?fromtitle=I2C&fromid=1727975

它通过一个时钟线和一个数据线进行连接，且虽然是两根线，但和UART不一样，它可以与多个设备相连。而在一条总线上有且应该只有一个主机。当然这是理论上的，如果是你设计的两个主机，你也可以把它们都放在一个总线上，只需要让他们在信息传输的过程中不冲突即可。

## 使用

-   I2C_init()
-   I2C_Params_init
-   细调参数
    -   I2C_TransferMode：传输模式，阻塞或回调
    -   CallbackFxn：传送回调
    -   bitRate：比特率：有专门的宏定义
    -   custom：自定义
-   open
-   设置I2C_Transaction，和SPI传输那个结构体同理
    -   writeBuf：发送缓存
    -   writeCount：发送帧数
    -   readBuf：接收缓存
    -   readCount：接收次数
    -   slaveAddress：从机地址
    -   arg：给回调的参数
-   I2C_transfer：通信，参考SPI即可
-   I2C_close：关闭



## I2CSlave.h

### 介绍

这个是一个补充库，应用于将设备设为I2C从机。

### 使用

-   I2CSlave_init
-   I2CSlave_Params_init
-   细调
    -   Transfer_Mode：阻塞或回调：默认阻塞
    -   CallbackFxn：回调函数
    -   custom：自定义
-   I2CSlave_open
-   I2CSlave_read：等待写入
-   I2CSlave_write：写入I2C设备
-   I2CSlave_close

### 理解

和I2C.h感觉起来没有什么本质上的差别，仅在于其把收发进行了拆分。

