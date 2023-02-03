#include "OLED.h"

struct i2c_client *this_client;

/*************************************************
*控制函数
*cmd  命令
*args 结构体参数
*************************************************/
static long myoled_ioctl(struct file *file, unsigned int  cmd, unsigned long args)
{
	struct oled_format oled;
	int ret = 0;
	void __user *argp = (void __user *)args;

	if(_IOC_TYPE(cmd) != 'O' || _IOC_DIR(cmd) != _IOC_WRITE)
		return -ENOIOCTLCMD;

	ret=copy_from_user(&oled,argp,sizeof(struct oled_format));
	if(ret)
		return - EFAULT;

	switch(cmd){
		case CMD_OLED_INIT:
			OLED_Init();
			printk(KERN_INFO"OLED_Init\n");
			break;
		case CMD_OLED_CLEAR:
			OLED_Clear();
			printk(KERN_INFO"OLED_Clear\n");
			break;
		case CMD_OLED_SHOW_STRING:
			OLED_ShowString(oled.x, oled.y, oled.str, oled.font_size);
			break;
		case CMD_OLED_SHOW_PICTURE:
			OLED_DrawBMP(oled.x, oled.y, oled.pic_width, oled.pic_high/8, oled.pic);
			break;
		default:
			printk(KERN_ERR"the cmd is error\n"); 
			return -EINVAL;
			break;
	}
	return 0;
}

/*************************************************
*打开文件
*************************************************/
int myoled_open (struct inode *inode, struct file *file)
{
	printk(KERN_INFO"myoled_open\n");

	return 0;
}

/*************************************************
*关闭文件
*************************************************/
int myoled_release (struct inode *inode, struct file *file)
{
	printk(KERN_INFO"myoled_release\n");

	return 0;
}

/*************************************************
*文件操作集
*************************************************/
static const struct file_operations chrdev_fops = {
	.owner	= THIS_MODULE,
	.open =myoled_open,
	.release = myoled_release,
	.unlocked_ioctl = myoled_ioctl,
};

/*************************************************
*杂项设备
*************************************************/
static struct miscdevice myoled_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,	//MISC_DYNAMIC_MINOR,动态分配次设备号
	.name = DEVICE_NAME,			//设备名称,/dev/myoled
	.fops = &chrdev_fops,			//文件操作集
};

/*************************************************
*平台设备加载
*************************************************/
static int myoled_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int rt;
	//检查是否支持I2C功能
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) 
	{
		printk("i2c_check_functionality fail\n");
		
		return -ENODEV;
	}	
	
	//混杂设备的注册
	rt = misc_register(&myoled_miscdev);
	
	if (rt) 
	{
		printk("misc_register fail\n");
		return rt;
	}
	
	//保存client指针，里面有各种设备信息
	this_client = client;
	
	return 0;
}

/*************************************************
*平台设备卸载
*************************************************/
static int __devexit myoled_remove(struct i2c_client *client)
{
	misc_deregister(&myoled_miscdev);

	return 0;
}

//Linux I2C设备驱动中，是通过i2c device id名字进行i2c device和i2c driver匹配的。
static const struct i2c_device_id myoled_id[] = {
	{ DEVICE_NAME, 0 },	//参数1必须跟进行i2c device和i2c driver匹配的
								//参数2可以作为私有数据传递给myoled_probe的参数2
	{ }							//标识结束
};

//添加到i2c总线设备列表，告诉内核当前设备支持热插拔功能
MODULE_DEVICE_TABLE(i2c, myoled_id);

static struct i2c_driver myoled_driver = {
	.driver = 
	{
		.name = DEVICE_NAME,						//用于匹配设备
		.owner = THIS_MODULE,
	},
	.probe 		= myoled_probe,					//驱动初始化
	.remove 	= __devexit_p(myoled_remove),	//驱动删除
	.id_table 	= myoled_id,					//添加支持的设备表					
														
};


/********************************************************************
*驱动的初始化函数
********************************************************************/
static int __init gec6818_oled_init(void) 
{
	//添加I2C设备
	return i2c_add_driver(&myoled_driver);
}

/*****************************************************************
*驱动退出函数
*****************************************************************/
static void __exit gec6818_oled_exit(void)            
{
	//删除I2C设备
	i2c_del_driver(&myoled_driver);
}

module_init(gec6818_oled_init);             //驱动的入口函数会调用一个用户的初始化函数
module_exit(gec6818_oled_exit);             //驱动的出口函数会调用一个用户的退出函数




