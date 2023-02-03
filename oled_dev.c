#include "OLED.h"

static struct i2c_board_info myoled_info = {
    // 如果地址是0x50,会跟内核自带的24c04地址冲突，所以内核必须卸载24c04驱动才行；
    I2C_BOARD_INFO(DEVICE_NAME, 0x3C),
};

static struct i2c_client *myoled_client ;

static int myoled_dev_init(void)
{
    struct i2c_adapter *i2c_adap;

    //获取设备号为2的adpter ,也就是adapter->nr == 2
    i2c_adap = i2c_get_adapter(2);

    //直接使用i2c_new device 创建client自动注册到i2c_bus_type 中
    //client->name== "myoled"
    //client->addr = 0x50
    myoled_client = i2c_new_device(i2c_adap, &myoled_info);
    //释放掉adapter
    i2c_put_adapter(i2c_adap);

    return 0;
}

static void myoled_dev_exit(void)
{
    i2c_unregister_device(myoled_client);
}

module_init(myoled_dev_init);             //驱动的入口函数会调用一个用户的初始化函数
module_exit(myoled_dev_exit);             //驱动的出口函数会调用一个用户的退出函数
//模块描述
MODULE_AUTHOR("Teacher.Wen");
MODULE_DESCRIPTION("This is led dev driver");
MODULE_LICENSE("GPL");



