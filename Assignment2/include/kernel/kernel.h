#ifndef __KERNEL__
#define __KERNEL__

#include "stdio.h"
#include "stdlib.h"
#include "uart.h"
#include "bsc.h"
#include "rtc.h"

#define BUFFERLENGTH 80
#define MODE_READ 0
#define MODE_WRITE 1
#define MAX_LEN 32
#define true 1
#define false 0
unsigned int bcd_to_decimal(unsigned int bcd);
unsigned int decimal_to_bcd(unsigned int d);
enum {
    Sunday = 1,
    Monday, 
    Tuesday, 
    Wednesday, 
    Thursday, 
    Friday, 
    Saturday,
};

#endif