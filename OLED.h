#ifndef __OLED_H
#define __OLED_H			
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <cfg_type.h>
#include <linux/hid.h>  
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>	

#define DEVICE_NAME     "myoled"             //设备名字

#define OLED_MODE 1
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC端口定义----------------  					   
#define  SDA_GPIO    (PAD_GPIO_B + 28)       //管脚号
#define  SCK_GPIO    (PAD_GPIO_B + 29)       //管脚号

#define OLED_SCLK_Clr() gpio_set_value(SCK_GPIO, 0)//SCL
#define OLED_SCLK_Set() gpio_set_value(SCK_GPIO, 1)

#define OLED_SDIN_Clr() gpio_set_value(SDA_GPIO, 0)//SDA
#define OLED_SDIN_Set() gpio_set_value(SDA_GPIO, 1)

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//命令
#define CMD_OLED_INIT           _IOW('O',0,struct oled_format) 
#define CMD_OLED_SHOW_STRING    _IOW('O',1,struct oled_format) 
#define CMD_OLED_SHOW_PICTURE   _IOW('O',2,struct oled_format) 
#define CMD_OLED_CLEAR          _IOW('O',10,struct oled_format)
#define OLED_BUF_SIZE (128*64)

//命令结构体
struct oled_format 
{ 
    unsigned char x; 
    unsigned char y; 
    unsigned char font_size; 
    unsigned char *str; 
    unsigned char *pic; 
    unsigned char pic_width; 
    unsigned char pic_high; 
};


//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

void fill_picture(unsigned char fill_Data);
//void Picture(void);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);

void IIC_Wait_Ack(void);

//void OLED_Printf(u8 x , u8 y , u8 Char_Size, char *p,... );	//OLED 格式化输出

//驱动的描述信息： #modinfo  *.ko , 驱动的描述信息并不是必需的。
MODULE_AUTHOR("BH-0@qq.com");                   //驱动的作者
MODULE_DESCRIPTION("oled of driver");       //驱动的描述
MODULE_LICENSE("GPL");                        //遵循的协议
#endif  


