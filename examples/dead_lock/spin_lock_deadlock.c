#include <linux/module.h>
#include <linux/kernel.h>
 
static spinlock_t hack_spinA;
static spinlock_t hack_spinB;
 
void hack_spinAB(void)
{
  printk("hack_lockdep:A->B\n");
  spin_lock(&hack_spinA);
  spin_lock(&hack_spinB);
}
 
void hack_spinBA(void)
{
  printk("hack_lockdep:B->A\n");
  spin_lock(&hack_spinB);
  spin_lock(&hack_spinA);
}
 
static int __init lockdep_test_init(void)
{
  printk("al: lockdep error test init\n");
  spin_lock_init(&hack_spinA);
  spin_lock_init(&hack_spinB);
 
  hack_spinAB();
  hack_spinBA();
  return 0;
}
 
module_init(lockdep_test_init);

