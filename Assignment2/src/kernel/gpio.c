#include "gpio.h"

uint8_t assert_clock(uint8_t gpio_pin, uint8_t val){
    return val << gpio_pin;
}

void set_pud(uint32_t pudclk_reg, uint8_t gpio_pin, uint8_t pud_val){
    mmio_write(GPPUD, 0x00000000);
    // This provides the required set-up time for the control signal
    delay(150);
    // Enable clock for pull-ups/ pull-downs on Pin 14 and 15
    mmio_write(pudclk_reg, assert_clock(gpio_pin, pud_val));
    // This provides the required set-up time for the control signal
    delay(150);
    // Flush the GPIO setup
    mmio_write(pudclk_reg, 0x00000000);
}

