/* Raspberry pi GPIO interrupt processing example
  * Light on LED with BUTTON press
  */
 
 #include <linux/init.h>
 #include <linux/module.h>
 #include <linux/gpio.h>
 #include <linux/interrupt.h>
 
 #define BUTTON_PIN 25    /* GPIO 25 */
 #define LED_PIN 8    /* GPIO 8 */
 
 int flag = 0;
 
 static irqreturn_t irq_handler(int irq, void *dev)
 {
     gpio_set_value(LED_PIN, !gpio_get_value(LED_PIN));
     return IRQ_HANDLED;
 }
 
 static int led_init(void)
 {
     int err;
     
     printk(KERN_INFO "LED init");
     
     err = gpio_request_one(BUTTON_PIN, GPIOF_IN, "Light Button");
     if (err) return err;
 
     err = gpio_request_one(LED_PIN, GPIOF_OUT_INIT_LOW, "LED light");
     if (err) return err;
 
     enable_irq(gpio_to_irq(BUTTON_PIN));
     err = request_irq(gpio_to_irq(BUTTON_PIN), irq_handler, 
             IRQF_TRIGGER_FALLING, "LED Test", NULL);
     if (err < 0) {
         printk("irq_request failed!");
         return err;
     }
     flag = 1;
     return 0;
 }
 
 static void led_exit(void)
 {
     printk(KERN_INFO "LED exit");
     if(flag) free_irq(gpio_to_irq(BUTTON_PIN), NULL);
     gpio_free(BUTTON_PIN);
     gpio_free(LED_PIN);
 }
 
 
 module_init(led_init);
 module_exit(led_exit);
 
 MODULE_LICENSE("Dual BSD/GPL");
