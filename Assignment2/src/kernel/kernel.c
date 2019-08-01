#include "kernel.h"
#define MODE_READ 0
#define MODE_WRITE 1
#define MAX_LEN 32

uint16_t clk_div = 2500 ;
uint8_t slave_address = 0x00;
uint32_t len = 0;
uint8_t *data;
unsigned char wbuf[MAX_LEN];
int i;

void kernel_main()
{
    register unsigned int r;
    wbuf[0] = 0x00;
    wbuf[1] = 0x55;
    unsigned char buff[7];
    char khung[2] = {0x00,0x00};
    slave_address = 0x68;
    len = 7;
    uart_init();
    puts("Thao day\n");
    bcm2835_init();

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(slave_address);
    bcm2835_i2c_setClockDivider(clk_div);
    *data = bcm2835_i2c_write(&khung, 2);
    for (i=0; i<7; i++) buff[i] = 'n';
    bcm2835_i2c_read(buff, len);
    puts("\n");
    // puts(data);
    for (i=0; i<7; i++) {
            if(buff[i] != 'n') 
            {
                puts("Read Buf[] =");
                puts(itoa(bcd_to_decimal(buff[i])));
            }
    }
}