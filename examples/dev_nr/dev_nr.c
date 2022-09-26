#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#define MYMAJOR 90

/* Module Information */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Reyno Wu");
MODULE_DESCRIPTION("Regisger a device nr and impletement some call back functions");

static int driver_open(struct inode *device_file, struct file *instance)
{
    printk("dev_nr - open was called!\n");
    return 0;
}

static int driver_close(struct inode *device_file, struct file *instance)
{
    printk("dev_nr - close was called!\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close
};

static int __init hello_kernel_init(void)
{
    int retval;
    printk("hello kernel init\n");

    retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops);
    if (retval == 0){
        printk("dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
    } else if (retval >0){ 
        printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval>>20, retval & 0xfffff);
    } else {
        printk("could not register device number!\n");
        return -1;
    }
 return 0;
}
static void __init hello_kernel_exit(void)
{
    unregister_chrdev(MYMAJOR, "my_dev_nr");
    printk("hello kernel exit\n");
}
module_init(hello_kernel_init);
module_exit(hello_kernel_exit);
MODULE_LICENSE("GPL");
