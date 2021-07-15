# ADC的使用

## 介绍

模数转换器

## 使用

-   ADC_init
-   ADC_Params_init
-   参数细调
    -   isProtected：是否通过信号量保证线程安全，如果设为false，则需要用户手动确保ADC_convert的并行调用。简单理解就是当多个线程同时使用一个ADC的时候，需要防止它们因为同时调用ADC转换而致使出错。默认保护。
    -   custom：自定义
-   ADC_open
-   ADC_convert：读取数值采样
-   ADC_convertToMicroVolts：将样本值转换为微伏
-   ADC_close

## ADCBuf

模数转换缓冲器，如果连续采样可能使用这个更加方便。

### 介绍

ADCBuf允许以一定频率进行采样和转换，且生成的样本将放置到缓冲区中。驱动程序可以进行N采样或连续双缓冲采样并为每次结束缓冲区提供回调。

### 使用

1.  ADCBuf_init
2.  ADCBuf_Params_init
3.  细调
    1.  blockingTimeout：阻塞超时，仅在阻塞模式下针对ADCBuf_convert有效，如果需求采样样本数（等会说这个）已达到要求，则对ADCBuf_convert结束阻塞（否则将持续到超时时间），该值应该足够大
    2.  sampleingFrequency：采样频率，单位为Hz
    3.  returnMode：返回模式，阻塞或回调，阻塞终止或回调启动的时刻为完成需求采样样本数。
    4.  callbackFxn：回调函数
    5.  recurrenceMode：是否重复转换
    6.  custom：自定义
4.  ADCBuf_open
5.  设置ADCBuf_Conversion
    1.  samplesRequestedCount：需求采样样本数，也就是一次性要采几个
    2.  sampleBuffer：转换结果缓冲区，该缓冲区至少为两倍的需求采样样本数，单次转换（不重复）模式下仅使用此转换模式。
    3.  sampleBufferTwo：转换结果缓冲区，至少两字节，使用重复转换的时候这个缓冲区必须指向一个有效的缓冲区，猜测应该是用来做双缓冲的？
    4.  arg：回调参数
    5.  adcChannel：ADC的转换通道
6.  ADCBuf_convert
7.  ADCBuf_close

### 其它

-   ADCBuf_convertCancel：终止转换
-   ADCBuf_getResolution：返回指定ADCBuf实例的位分辨率
-   ADCBuf_adjustRawValues：就地调整原始ADCBuf实例
-   ADCBuf_convertAdjustedToMicroVolts：将调整后的ADCBuf转换为微伏



