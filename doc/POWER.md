# POWER的使用

## 介绍

TI的低功耗挺厉害的，当年MSP430的低功耗一骑绝尘，虽然MSP432作为32位机功耗变高了，但是在低功耗MCU中还是属于比较厉害的一种。

根据不同的需求有不同的设计内容，我们将分类阐述。请注意，在设计低功耗的时候需要考虑具体的设备具体拥有的功能性能等。

## 启动

Power_init：这个函数一般不用管，在初始化的时候（syscfg）的时候，只要你配置了Power，那么就会自动生成到Board_init中。

## 策略启动和关闭

Power_enablePolicy和Power_disablePolicy



