# SD卡的使用

## 介绍

SD卡这个就不用介绍了，非常常见的储存设备，先介绍不带文件系统的，然后使用文件系统。

## 使用

1.  SD_init
2.  SD_open：打开卡
3.  SD_initialize：初始化卡
4.  SD_write：扇区写
5.  SD_read：扇区读
6.  SD_close关闭卡

## 其它

SD_getNumSectors：获取卡的扇区数

SD_getSectorSize：获取扇区大小

## 注意

需要注意，直接使用这种方法来读写SD卡肯定会损坏文件系统的，如果上面有啥重要的数据请慎重。

## 文件系统

使用的文件系统是FatFs系统。这个系统是嵌入式中很常见的，包括STM32这些单片机也经常会有使用这个系统的，不过TI把它封装了一下，弄成了SDFatFs，总体使用没啥区别，只是为了兼容性在初始化和开启关闭系统时有所区别，不用管细节直接用就好。

## SDFatFS使用

此部分为SDFatFS相较于直接的FatFs的区别，其它的没有变化。

-   SDFatFs_init：初始化
-   SDFatFS_open：开启
-   FatFS的文件操作
-   SDFatFs_close：关闭

## FatFS的使用

FatFs的具体应用可以直接去访问官网：

http://elm-chan.org/fsw/ff/00index_e.html

使用上面其实和在Windows上操作文件基本无异。

