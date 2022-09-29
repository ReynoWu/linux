#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

static struct task_struct *kthread_1;
static struct task_struct *kthread_2;
static int t1 = 1, t2 = 2;

int thread_function(void *para)
{
    unsigned int i = 0;

    int local_parameter = *(int *)para;

    while(!kthread_should_stop())
    {
        printk("kthread - Thread %d is excuted! counter value : %d\n", local_parameter, i++);
        msleep(1000 * local_parameter);
    }

    printk("kthread - Thread %d finish excuted!\n", local_parameter);

    return 0;
}

static int __init ModuleInit(void)
{
	printk("kthread - Init threads\n");

	kthread_1 = kthread_create(thread_function, &t1, "kthread_1");
	if(kthread_1 != NULL){
		/* Let's start the thread */
		wake_up_process(kthread_1);
		printk("kthread - Thread 1 was created and is running now!\n");
	}
	else {
		printk("kthread - Thread 1 could not be created!\n");
		return -1;
	}
	kthread_2 = kthread_run(thread_function, &t2, "kthread_2");
	if(kthread_2 != NULL)
		printk("kthread - Thread 2 was created and is running now!\n");
	else {
		printk("kthread - Thread 2 could not be created!\n");
		kthread_stop(kthread_1);
		return -1;
	}
	printk("kthread - Both threads are running now!\n");

	return 0;

}

static void __exit ModuleExit(void) {
	printk("kthread - Stop both threads\n");
	kthread_stop(kthread_1);
	kthread_stop(kthread_2);
}

module_init(ModuleInit);
module_exit(ModuleExit);

