#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x367398b6, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x426b950b, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x59bfb68c, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xdfefb820, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x5e9805a4, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xce7a6828, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0xd29e0a01, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x5b744154, __VMLINUX_SYMBOL_STR(napi_complete_done) },
	{ 0x6128b5fc, __VMLINUX_SYMBOL_STR(__printk_ratelimit) },
	{ 0x880156d0, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x92986bf1, __VMLINUX_SYMBOL_STR(netif_receive_skb) },
	{ 0x4a054469, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0x71ca80b1, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x8ad2f2db, __VMLINUX_SYMBOL_STR(netif_napi_add) },
	{ 0x38bec498, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x7a9f42fb, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x7f9f07e3, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x25e74eb2, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xd3bdd4f2, __VMLINUX_SYMBOL_STR(__napi_schedule) },
	{ 0x844324ed, __VMLINUX_SYMBOL_STR(napi_schedule_prep) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x578eca1f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xc6ad451a, __VMLINUX_SYMBOL_STR(netif_tx_wake_queue) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "74F1060E1132AD76376E720");
