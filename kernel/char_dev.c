#include <linux/module.h>

MODULE_AUTHOR("Yasuhiro Yamamoto");
MODULE_LICENSE("GPL");
    
static int my_init(void)
{
    printk(KERN_INFO "Hello, World!\n");
    return 0;
}

static void my_exit(void)
{
    printk(KERN_INFO "Goodbye...\n");
}

module_init(hello_init);
module_exit(hello_exit);
