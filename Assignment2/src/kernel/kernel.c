// #include "kernel.h"
// #define MODE_READ 0
// #define MODE_WRITE 1
// #define MAX_LEN 32

// uint16_t clk_div = 2500 ;
// uint8_t slave_address = 0x00;
// uint32_t len = 0;
// uint8_t *data;
// unsigned char wbuf[MAX_LEN];
// int i;

// void kernel_main()
// {
//     register unsigned int r;
//     wbuf[0] = 0x00;
//     wbuf[1] = 0x55;
//     unsigned char buff[7];
//     char khung[2] = {0x00,0x00};
//     slave_address = 0x68;
//     len = 7;
//     uart_init();
//     puts("DS1307 Real Time Clock Data\n");
//     puts("---------------------------\n");
//     bcm2835_init();

//     bcm2835_i2c_begin();
//     bcm2835_i2c_setSlaveAddress(slave_address);
//     bcm2835_i2c_setClockDivider(clk_div);
//     *data = bcm2835_i2c_write(&khung, 2);
//     // unsigned char* buttonPressed = 'a';
//     // puts(data);
//     int condition = 1;
//     while(1)
//     {   
//         while(getc() == 0x00){
//             puts("1");
//             // puts(itoa((getc()==0x00)));
//             // if (getc() == 0x70)
//             // {
//                 // condition = 0;
//             // }
//         }

//         // puts("0");
//         // if (getc() == 0x72)
//         // {
//         //     condition = 1;
//         // }
        
//         // if(){
//         //     putc(getc());
//         //     bcm2835_i2c_write(&khung,1);
//         //     for (i=0; i<7; i++) buff[i] = 'n';
//         //     bcm2835_i2c_read(buff, len);
//         //     switch(bcd_to_decimal(buff[3])){
//         //         case 1:
//         //             puts("Sunday ");
//         //             break;
//         //         case 2:
//         //             puts("Monday ");
//         //             break;            
//         //         case 3:
//         //             puts("Tuesday ");
//         //             break;
//         //         case 4:
//         //             puts("Wednesday ");
//         //             break;
//         //         case 5:
//         //             puts("Thursday ");
//         //             break;
//         //         case 6:
//         //             puts("Friday ");
//         //             break;
//         //         case 7:
//         //             puts("Saturday ");
//         //             break;
//         //         default:
//         //             puts("wrong");

//         //     }
//         //     puts(itoa(bcd_to_decimal(buff[2])));
//         //     puts(":");
//         //     puts(itoa(bcd_to_decimal(buff[1])));
//         //     puts(":");
//         //     puts(itoa(bcd_to_decimal(buff[0])));
//         //     puts("  ");
//         //     puts(itoa(bcd_to_decimal(buff[4])));
//         //     puts("/");
//         //     puts(itoa(bcd_to_decimal(buff[5])));
//         //     puts("/");
//         //     puts(itoa(bcd_to_decimal(buff[6])));
//         //     puts("\n");
//         //     bcm2835_delay(1000);
//         // } 
//         // else{
//         //     puts("Im do nothing");
//         // }
//     }
// }

#include "kernel.h"
// #include "uart.h"
// #include "mpu6050.h"
// #include "stdio.h"

struct Time {
   unsigned int second;
   unsigned int minute;
   unsigned int hour;
   unsigned int mday;
   unsigned int wday;
   unsigned int month;
   unsigned int year;
};

char uart_time(unsigned char * khung, unsigned char* buff, unsigned int b) {
    char r;
    /* wait un til something is in the buffer */
    do{
        if (b == 1)
        {
            bcm2835_i2c_write(&khung,1);
            for (int i=0; i<7; i++) buff[i] = 'n';
            bcm2835_i2c_read(buff, 7);
            switch(bcd_to_decimal(buff[3])){
                case 1:
                    uart_puts("Sunday ");
                    break;
                case 2:
                    uart_puts("Monday ");
                    break;            
                case 3:
                    uart_puts("Tuesday ");
                    break;
                case 4:
                    uart_puts("Wednesday ");
                    break;
                case 5:
                    uart_puts("Thursday ");
                    break;
                case 6:
                    uart_puts("Friday ");
                    break;
                case 7:
                    uart_puts("Saturday ");
                    break;
                default:
                    uart_puts("wrong");
            }
            uart_puts(itoa2(bcd_to_decimal(buff[2])));
            uart_puts(":");
            uart_puts(itoa2(bcd_to_decimal(buff[1])));
            uart_puts(":");
            uart_puts(itoa2(bcd_to_decimal(buff[0])));
            uart_puts("  ");
            uart_puts(itoa2(bcd_to_decimal(buff[4])));
            uart_puts("/");
            uart_puts(itoa2(bcd_to_decimal(buff[5])));
            uart_puts("/");
            uart_puts(itoa2(bcd_to_decimal(buff[6])));
            uart_puts("\n");
        }
    } while(!(*AUX_MU_LSR&0x01));
    /* read it and return */
    r=(char)(*AUX_MU_IO);
    /* convert carrige return to newline */
    bcm2835_delay(1000);
    return r=='\r'?'\n':r;
}

typedef enum
{
	BCM2835_I2C_CLOCK_DIVIDER_2500   = 2500,      ///< 2500 = 10us = 100 kHz
	BCM2835_I2C_CLOCK_DIVIDER_626    = 626,       ///< 622 = 2.504us = 399.3610 kHz
	BCM2835_I2C_CLOCK_DIVIDER_150    = 150,       ///< 150 = 60ns = 1.666 MHz (default at reset)
	BCM2835_I2C_CLOCK_DIVIDER_148    = 148,       ///< 148 = 59ns = 1.689 MHz
} bcm2835I2CClockDivider;

#define MODE_READ 0
#define MODE_WRITE 1
#define MAX_LEN 32

uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_2500 ;
uint8_t slave_address = 0x00;
uint32_t len = 0;
uint8_t *data;
unsigned char wbuf[MAX_LEN];
int i;
unsigned char buf[MAX_LEN];
void kernel_main()
{
    register unsigned int r;
    wbuf[0] = 0x00;
    wbuf[1] = 0x55;
    unsigned char buff[7];
    char khung[8]= {0x00,decimal_to_bcd(0),decimal_to_bcd(20),
    decimal_to_bcd(18),decimal_to_bcd(5),decimal_to_bcd(1),decimal_to_bcd(8),
    decimal_to_bcd(19)};
    char khung1[2] = {0x00,0x00};
    char second[2] = {0x00,decimal_to_bcd(0)};
    char minute[2] = {0x01,decimal_to_bcd(50)};
    char hour[2] = {0x02,decimal_to_bcd(17)};
    char weekday[2] = {0x03,decimal_to_bcd(5)};
    char day[2] = {0x04,decimal_to_bcd(8)};
    char month[2] = {0x05,decimal_to_bcd(1)};
    char year[2] = {0x06,decimal_to_bcd(19)};
    slave_address = 0x68;
    len = 7;
    uart_puts("DS1307 Real Time Clock Data\n");
    uart_puts("---------------------------\n");
    uart_init();
    // uart_puts("Thao day\n");
    if (!bcm2835_init())
    {
        uart_puts("bcm2835 init failed");
        return 1;
    }
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(slave_address);
    bcm2835_i2c_setClockDivider(clk_div);
    *data = bcm2835_i2c_write(&khung, 8);
    unsigned int b = 1;
    unsigned int count = 0;
    while (1)
    {
        char r;
        /* wait un til something is in the buffer */
        do{
            if (b == 1 && count == 100)
            {
                bcm2835_i2c_write(&khung,1);
                for (i=0; i<7; i++) buff[i] = 'n';
                bcm2835_i2c_read(buff, 7);
                switch(bcd_to_decimal(buff[3])){
                    case 1:
                        uart_puts("Sunday ");
                        break;
                    case 2:
                        uart_puts("Monday ");
                        break;            
                    case 3:
                        uart_puts("Tuesday ");
                        break;
                    case 4:
                        uart_puts("Wednesday ");
                        break;
                    case 5:
                        uart_puts("Thursday ");
                        break;
                    case 6:
                        uart_puts("Friday ");
                        break;
                    case 7:
                        uart_puts("Saturday ");
                        break;
                    default:
                        uart_puts("wrong");
                }
                uart_puts(itoa2(bcd_to_decimal(buff[2])));
                uart_puts(":");
                uart_puts(itoa2(bcd_to_decimal(buff[1])));
                uart_puts(":");
                uart_puts(itoa2(bcd_to_decimal(buff[0])));
                uart_puts("  ");
                uart_puts(itoa2(bcd_to_decimal(buff[4])));
                uart_puts("/");
                uart_puts(itoa2(bcd_to_decimal(buff[5])));
                uart_puts("/");
                uart_puts(itoa2(bcd_to_decimal(buff[6])));
                uart_puts("\n");
                count = 0;
            } else if (b==0) {
                count = 100;
            } else if (b==1){
                if (count >= 100){
                    count = 100;
                } else count++;
            }
            bcm2835_delay(10);
        } while(!(*AUX_MU_LSR&0x01));
        /* read it and return */
        r=(char)(*AUX_MU_IO);
        /* convert carrige return to newline */
        r=='\r'?'\n':r;
        if ((r == 'r') | (r == 'R'))
        {
            b = 1;
        }
        if ((r == 'p') | (r == 'P'))
        {
            b = 0;
        }
    }
}
