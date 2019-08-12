#ifndef __GPIO__
#define __GPIO__
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

enum {
    GPIO_BASE    = 0x3F200000,           // GPIO Base Address
    GPPUD        = (GPIO_BASE + 0x94),   // GPIO Pin Pull Up/Down Enable
    GPPUDCLK0    = (GPIO_BASE + 0x98),   // GPIO Pin Pull Up/Down Enable Clock 0
    GPFSEL0      = GPIO_BASE,
};

uint8_t assert_clock(uint8_t gpio_pin, uint8_t val);
void set_pud(uint32_t pudclk_reg, uint8_t gpio_pin, uint8_t pud_val);
#endif