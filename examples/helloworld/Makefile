obj-m += hello_kernel.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules clean
install:
	insmod hello_kernel.ko
uninstall:
	rmmod hello_kernel