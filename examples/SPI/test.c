#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "string.h"

static const char *device = "/dev/spidev0.0";
static uint8_t mode = 0; /* SPI通信使用全双工，设置CPOL＝0，CPHA＝0。 */
static uint8_t bits = 8; /* ８ｂiｔｓ读写，MSB first。*/
static uint32_t speed = 1 * 500 * 1000;/* 设置0.5M传输速度 */
static uint16_t delay = 500;
static int g_SPI_Fd = 0;

int SPI_Transfer(const uint8_t *TxBuf, uint8_t *RxBuf, int len)
{
    int ret;
    int fd = g_SPI_Fd;


    struct spi_ioc_transfer tr ;
    memset(&tr,0x00,sizeof(tr));
    tr.tx_buf = (unsigned long) TxBuf,
    tr.rx_buf = (unsigned long) RxBuf,
    tr.len =len,
    tr.delay_usecs = delay;
    tr.speed_hz=speed;
    tr.bits_per_word=bits;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
    {
        printf("can't send spi message");
    }
   else
   {
        //printf("Send spi message OK %d\n",RxBuf[0]);
   }
   return 1;
}

/**
* 功 能：关闭SPI模块
*/
int SPI_Close(void)
{
    int fd = g_SPI_Fd;


    if (fd == 0) /* SPI是否已经打开*/
    return 0;
    close(fd);
    g_SPI_Fd = 0;


    return 0;
}
int SPI_Write(uint8_t *TxBuf, int len)
{
    int ret;
    int fd = g_SPI_Fd;

    printf("fd : %d\n",fd);
    ret = write(fd, TxBuf, len);
    if (ret < 0)
    printf("SPI Write errorn");



    return ret;
}
int SPI_Open(void)
{
    int fd;
    int ret = 0;

    fd = open(device, O_RDWR);
    if (fd < 0)
        printf("can't open device");
    else
        printf("SPI - Open Succeed. Start Init SPI...n");

    /*
    * spi mode
    */
    ret = ioctl(fd, SPI_IOC_WR_MODE32, &mode);
    if (ret == -1)
    printf("can't set spi mode");


    ret = ioctl(fd, SPI_IOC_RD_MODE32, &mode);
    if (ret == -1)
    printf("can't get spi mode");


    /*
    * bits per word
    */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
      printf("can't set bits per word");


    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
      printf("can't get bits per word");


    /*
    * max speed hz
    */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    printf("can't set max speed hz");


    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        printf("can't get max speed hz");
    printf("\n%d SPI Open Status\n",ret);
    g_SPI_Fd=fd;
    return ret;
}

int main()
{
  uint8_t tx_data[64]={0x1,0x2};
  uint8_t rx_data[64]={0};
  uint32_t i;
  
  memset(tx_data,0xAA,64);
  SPI_Open();
  for (i = 0; i < 10; i++)
  {
    SPI_Transfer(tx_data,rx_data,64);
    printf("Send spi message OK %d\n",rx_data[0]);
    rx_data[0]=0x01;
    printf("Spi message Init %d\n",rx_data[0]);
  }
  return 0;
}
