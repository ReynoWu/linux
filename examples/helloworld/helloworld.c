/*
readme on how to run the example
sudo apt-get update
sudo apt-get install raspberrypi-kernel-headers
reboot
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHER("Reyno Wu");
MODULE_DESCRIPTION("A HELLO WORLD LKM");

static init __init ModuleInit(void){
    printk("Hello, Kernel!\n");
    return 0;
}

static void __exit ModuleExit(void){
    printk("Goodbye, Kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
