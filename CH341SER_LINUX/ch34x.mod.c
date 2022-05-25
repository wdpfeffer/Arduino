#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x11c92bdf, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x5dfbf333, __VMLINUX_SYMBOL_STR(usb_serial_deregister_drivers) },
	{ 0x6090ef8a, __VMLINUX_SYMBOL_STR(usb_serial_register_drivers) },
	{ 0x372e1581, __VMLINUX_SYMBOL_STR(usb_serial_port_softint) },
	{ 0x2e60bace, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb8a418f6, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x68dfc59f, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xd3813bef, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x7f457a3b, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xe4c09712, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0x47c95322, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0x43e1b78f, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_flags) },
	{ 0x35284a06, __VMLINUX_SYMBOL_STR(tty_buffer_request_room) },
	{ 0xe45f60d8, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x8ad77d0f, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x6191a065, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xe7980e5f, __VMLINUX_SYMBOL_STR(usb_clear_halt) },
	{ 0x1657a590, __VMLINUX_SYMBOL_STR(tty_encode_baud_rate) },
	{ 0xf2997713, __VMLINUX_SYMBOL_STR(tty_termios_hw_change) },
	{ 0x67b27ec1, __VMLINUX_SYMBOL_STR(tty_std_termios) },
	{ 0xf49f78f, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x9c55cec, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0x3a013b7d, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{        0, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0xd7bd3af2, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0xffd5a395, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xb3bbe024, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x62cb4cee, __VMLINUX_SYMBOL_STR(interruptible_sleep_on) },
	{ 0x601909b6, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xf97456ea, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x21fb443e, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xe43fc9a7, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v1A86p7523d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p5523d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "967742AA1078DB0FB0548DB");
