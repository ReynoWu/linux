#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
static int hello_kernel_init(void)
{
 printk("hello kernel init\n");
 return 0;
}
static void hello_kernel_exit(void)
{
 printk("hello kernel exit\n");
}
module_init(hello_kernel_init);
module_exit(hello_kernel_exit);
MODULE_LICENSE("GPL");