#include <stdio.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <string.h>  
#include <linux/i2c.h>  
#include <linux/i2c-dev.h>   

#define SLAVE_ADDRESS 0x50 //FM24CL16芯片地址为0x50
#define I2C_DEV "/dev/i2c-1"//i2c_dev为i2c　adapter创建的别名  
//读操作先发Slaveaddr_W+Regaddr_H+Regaddr_L 3个字节来告诉设备操作器件及两个byte参数  
//然后发送Slaveaddr_R读数据  
static int iic_read(int fd, char buff[], int addr, int count)  
{  
    int res;  
    char sendbuffer1[2];  
    //sendbuffer1[0]=addr>>8;  
    //sendbuffer1[1]=addr;  
    sendbuffer1[0]=addr;

    write(fd,sendbuffer1,1);        
    res=read(fd,buff,count);  
    //printf("read %d byte at 0x%x\n", res, addr);  
    return res;  
} 

//在写之前，在数据前加两个byte的参数，根据需要解析  
static int iic_write(int fd, char buff[], int addr, int count)  
{  
    int res;
    int i,n;
    char sendbuffer[2048+3];  
    memcpy(sendbuffer+1, buff, count);  
    sendbuffer[0]=addr;  
    res=write(fd,sendbuffer,count+1);  
    //printf("write %d byte at 0x%x\n", res, addr);  
}  

unsigned char wbuf1[2048];
unsigned char wbuf2[2048];
unsigned char wbuf3[2048];
unsigned char wbuf4[2048];
unsigned char wbuf5[2048];
unsigned char wbuf6[2048];
unsigned char wbuf7[2048];
unsigned char wbuf8[2048];

unsigned char rbuf[2048];

int main(void){  
    int fd;  
    int res;  
    char ch;  
 
    char buf[50];  
    int regaddr,i,slaveaddr;  
    fd = open(I2C_DEV, O_RDWR);// I2C_DEV /dev/i2c-0  
    if(fd < 0){  
        printf("####i2c test device open failed####\n");  
        return -1;  
    }

    if(ioctl(fd,I2C_TENBIT,0)<0)
    {
        printf("---set i2c bit error---\r\n");
        return -1;
    }

    if(ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS)<0)
    {
        printf("--set i2c address error---\r\n");
        return -1;
    }
    
    /*write data as 512Bytes once*/
    for(i = 0 ; i < 256 ; i ++)
    {
        wbuf1[i] = i;   
        wbuf2[i] = 255-i;   
        wbuf3[i] = i%256;   
        wbuf4[i] = 255-i;   
        wbuf5[i] = i%256;   
        wbuf6[i] = 255-i;   
        wbuf7[i] = i%256;   
        wbuf8[i] = 255-i;   
    }

    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+0); 
    iic_write(fd,wbuf1,0,256); 
    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+1);
    iic_write(fd,wbuf2,0,256); 
    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+2);
    iic_write(fd,wbuf3,0,256); 
    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+3);
    iic_write(fd,wbuf4,0,256); 
    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+4);
    iic_write(fd,wbuf5,0,256); 
    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+5);
    iic_write(fd,wbuf6,0,256); 
    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+6);
    iic_write(fd,wbuf7,0,256); 
    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+7);
    iic_write(fd,wbuf8,0,256); 

    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS);
    iic_read(fd,rbuf,0,256); 
    printf("read page 0:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 


    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+1);
    iic_read(fd,rbuf,0,256); 
    printf("read page 1:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 


    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+2);
    iic_read(fd,rbuf,0,256); 
    printf("read page 2:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 

    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+3);
    iic_read(fd,rbuf,0,256); 
    printf("read page 3:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 


    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+4);
    iic_read(fd,rbuf,0,256); 
    printf("read page 4:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 

    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+5);
    iic_read(fd,rbuf,0,256); 
    printf("read page 5:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 

    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+6);
    iic_read(fd,rbuf,0,256); 
    printf("read page 6:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 

    ioctl(fd,I2C_SLAVE,SLAVE_ADDRESS+7);
    iic_read(fd,rbuf,0,256); 
    printf("read page 7:\r\n");
    for(i = 0 ; i <256 ; i ++)
    {
        printf("0x%0x ",rbuf[i]);
    }
    printf("\r\n"); 

    return 0;  
}  
