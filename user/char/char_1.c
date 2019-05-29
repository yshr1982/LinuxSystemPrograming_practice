#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <linux/types.h>

#define SPI_SPEED_HZ    1000000
#define SPI_DELAY_USECS 0
#define SPI_BITS        8

void main(int argc, char* argv[])
{
    int fd;
    char *data = 'test';
    int size;
    loff_t ppos = 0;

    if(argc <= 1){
        printf("Error loss of argment. /n")
        return 0;
    }
    // system call openを使って/dev/my_device3にアクセスする
    fd = open(argv[1], O_RDWR);
    
    ioctl(fd, 1, &data);

    size = 9;

    read(fd,'my sample',size);

    write(fd,'my sample2',size);

    close(fd);

}        

