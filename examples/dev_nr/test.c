#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int dev = open("/dev/mydevices", O_RDONLY);
    if (dev == -1){
        printf("Opening was not possible!\n");
        return -1;
    }

    printf("Opening wa successful!\n");
    close(dev);

    return 0;
}
