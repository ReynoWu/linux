obj-m += kernel_thread.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules clean
install:
	insmod kernel_thread.ko
uninstall:
	rmmod kernel_thread
