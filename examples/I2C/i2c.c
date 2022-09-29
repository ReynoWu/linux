#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/mod_devicetable.h>
#include <linux/log2.h>
#include <linux/bitops.h>
#include <linux/jiffies.h>
#include <linux/of.h>
#include <linux/acpi.h>
#include <linux/i2c.h>
#include <asm/uaccess.h>


static int bme280_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	return 0;
}

static int bme280_remove(struct i2c_client *client)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static const struct of_device_id bme280_of_match[] = {
	{.compatible = "pgg,bme280"},
	{}
};


static struct i2c_driver bme280_drv = {
	.driver = {
		.name = "mybme280_drv",
		.of_match_table	 = bme280_of_match,
	},
	.probe = bme280_probe,
	.remove = bme280_remove,
};

static int bme280_init(void)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	return i2c_add_driver(&bme280_drv);;
}

static void bme280_exit(void)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	i2c_del_driver(&bme280_drv);
}

module_init(bme280_init);
module_exit(bme280_exit);

MODULE_LICENSE("GPL");

