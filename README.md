# linux_OLED

linux上的IIC OLED的屏幕驱动，本项目在SP6818实现，基于平台设备驱动模型

![](https://files.catbox.moe/nkqn77.png)

文件说明：

oled_dev.c  OLED设备文件

OLED.c  OLED.h  OLED功能函数文件

oled_main  OLED主驱动文件，与OLED.c编译成oled_dev.o

oledfont.h  OLED字库

test.c  驱动测试程序

test.h  测试程序的图片动画库

test  编译好的测试应用程序

Makefile  驱动模块与测试应用程序的编译脚本

oled_dev.ko  编译好的内核设备模块

oled_drv.ko  编译好的内核驱动模块



使用说明：

加载oled_dev.ko和oled_drv.ko后，可执行test测试程序，进行OLED显示动画播放测试
