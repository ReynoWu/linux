obj-m += spin_lock_deadlock.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules clean
install:
	insmod spin_lock_deadlock.ko
uninstall:
	rmmod spin_lock_deadlock