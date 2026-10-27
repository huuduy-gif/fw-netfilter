#include <linux/module.h>
#include <linux/kernel.h>

static int __init fw_init(void)
{
    pr_info("fw: module loaded\n");
    return 0;
}

static void __exit fw_exit(void)
{
    pr_info("fw: module unloaded\n");
}

module_init(fw_init);
module_exit(fw_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Netfilter firewall module");
