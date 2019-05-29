#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define SPI_SPEED_HZ    1000000
#define SPI_DELAY_USECS 0
#define SPI_BITS        8

void main(void)
{
    int fd;
    uint8_t tx[4] = {0xff, 0xff, 0xff, 0xff};
    uint8_t rx[4] = {0,0,0,0};
    struct spi_ioc_transfer data;
    unsigned char mode = SPI_CPOL|SPI_CPHA;

    data.tx_buf        = (unsigned long)tx;
    data.rx_buf        = (unsigned long)rx;
    data.len           = 4; //tx char size.
    data.delay_usecs   = SPI_DELAY_USECS;
    data.speed_hz      = SPI_SPEED_HZ;
    data.bits_per_word = SPI_BITS;
	data.bits_per_word = 8;
    data.cs_change     = 0;

    // system call openを使って/dev/spidev0.0にアクセスする
    fd = open("/dev/spidev0.0", O_RDWR);
    // SPIモードセット
	if( ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0 ) {
		printf( "SPI_IOC_WR_MODE failed");
	}
    
    ioctl(fd, SPI_IOC_MESSAGE(1), &data);
    sleep(1);

    tx[0] = 0x0c;
    tx[1] = 0x80;
    data.tx_buf        = (unsigned long)tx;
    data.rx_buf        = (unsigned long)rx;
    data.len           = 2; //tx char size.
    ioctl(fd, SPI_IOC_MESSAGE(1), &data);

    printf("ret val = %x %x %x %x \n",rx[0],rx[1],rx[2],rx[3]);

    sleep(1);

    tx[0] = 0x54;
    data.tx_buf        = (unsigned long)tx;
    data.rx_buf        = (unsigned long)rx;
    data.len           = 2; //tx char size.
    ioctl(fd, SPI_IOC_MESSAGE(1), &data);

    printf("ret val = %x %x %x %x \n",rx[0],rx[1],rx[2],rx[3]);

    sleep(1);

    close(fd);

}        

