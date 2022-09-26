/* after build*/
1. insmod

2. cat /proc/devices
will find my_dev_nr, the major number is 90

3. mknod /dev/mydevices c 90 0

4. ls /dev/mydevices
will show the devices
