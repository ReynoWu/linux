obj-m += hello_kernel.o
KERNEL := /usr/src/linux-headers-5.10.103+/
all:
	make -C $(KERNEL) M=$(shell pwd) modules
clean:
	make -C $(KERNEL) M=$(shell pwd) clean
install:
	insmod hello_kernel.ko
uninstall:
	rmmod hello_kernel