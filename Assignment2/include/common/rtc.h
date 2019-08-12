#ifndef __RTC__
#define __RTC__
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "bsc.h"

typedef union rtc {
    struct {
        uint8_t seconds : 8;
        uint8_t minutes : 8;
        uint8_t hours : 8;
        uint8_t day : 8;
        uint8_t date : 8;
        uint8_t month : 8;
        uint8_t year : 8;
        uint8_t control : 8;
    };
    uint64_t as_int;
} rtc_data_t;
unsigned int bcd_to_decimal(unsigned int bcd);
unsigned int decimal_to_bcd(unsigned int d);
void setTimeForRTC(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year,uint8_t is12);
void convertMode(uint8_t is12,uint8_t data);
#endif