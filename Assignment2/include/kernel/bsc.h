#ifndef __BSC__
#define __BSC__
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "uart.h"
#include "rtc.h"
#include "gpio.h"

#define ADDR_RTC 0x68
#define BSC1_FIFO_SIZE 16
#define BSC1_S_TA 1
#define BSC1_S_RXD 0x20
#define BSC1_C_READ 1
#define BSC1_C_WRITE 0

enum {
    //BSC0 master inside BCM
    BSC1_BASE   = 0x3F804000,
    BSC1_C      = (BSC1_BASE + 0x0),
    BSC1_S      = (BSC1_BASE + 0x4),
    BSC1_DLEN   = (BSC1_BASE + 0x8),
    BSC1_A      = (BSC1_BASE + 0xC),
    BSC1_FIFO   = (BSC1_BASE + 0x10),
    BSC1_DIV    = (BSC1_BASE + 0x14),
    BSC1_DEL    = (BSC1_BASE + 0x18),
    BSC1_CLKT   = (BSC1_BASE + 0x1C),

    // //GPIO Function Select 0
    // GPFSEL0 = 0x3F200000,
};

typedef union bsc_control {
    struct {
        uint8_t read : 1;
        uint8_t reserved_0 : 3;
        uint8_t clear : 2;
        uint8_t reserved_1 : 1;
        uint8_t start_transfer : 1;
        uint8_t interrupt_on_done : 1;
        uint8_t interrupt_on_tx : 1;
        uint8_t interrupt_on_rx: 1;
        uint8_t reserved_2 : 4;
        uint8_t i2c_enable : 1;
        uint16_t reserved_3 : 16;
    };
    uint32_t as_int;
} bsc_control_t;

typedef union bsc_status {
    struct {
        uint8_t transfer_active : 1;
        uint8_t transfer_done : 1;
        uint8_t txw_fifo_needs_writing : 1;
        uint8_t rxr_fifo_needs_reading : 1;
        uint8_t txd_fifo_accept_data : 1;
        uint8_t rxd_fifo_contains_data : 1;
        uint8_t txe_fifo_empty : 1;
        uint8_t rxf_fifo_full : 1;
        uint8_t acknowledge_error : 1;
        uint8_t clock_stretch_timeout : 1;
        uint32_t reserved_bits : 22;
    };
    uint32_t as_int;
} bsc_status_t;

typedef union bsc_clock_div {
    struct {
        uint16_t clock_div : 16;
        uint16_t reserved_bits : 16;
    };
    uint32_t as_int;
} bsc_cdiv_t;

typedef union bsc_dlen {
    struct {
        uint16_t data_length : 16;
        uint16_t reserved_bits : 16;
    };
    uint32_t as_int;
} bsc_dlen_t;

typedef union bsc_slave_address {
    struct {
        uint8_t address : 7;
        uint32_t reserved_bits : 25;
    };
    uint32_t as_int;
} bsc_slave_addr_t;

typedef union bsc_fifo {
    struct {
        uint8_t data : 8;
        uint32_t reserved_bits : 24;
    };
    uint32_t as_int;
} bsc_fifo_t;

void clear_status(void);
void start_tx(uint8_t mode);
void stop_tx(void);
void clear_fifo(void);
void write_fifo(uint8_t* data, uint32_t len);
void read_fifo(uint8_t* data, uint32_t len);
void i2c_init(void);
void i2c_setSlaveAddress(uint8_t addr);
void i2c_read(uint8_t* buf, uint32_t len);
void i2c_write(uint8_t* buf, uint32_t len);
#endif
