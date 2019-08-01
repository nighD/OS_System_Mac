#ifndef __BSC__
#define __BSC__
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "uart.h"

#define ADDR_RTC 0x68;

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

    //BSC slave
    SLV_BASE    = 0x3F214000,
    SLV_DR      = (SLV_BASE + 0x0),
    SLV_RSR     = (SLV_BASE + 0x4),
    SLV_SLV     = (SLV_BASE + 0x8),
    SLV_CR      = (SLV_BASE + 0xC),
    SLV_FR      = (SLV_BASE + 0x10),
    SLV_IFLS    = (SLV_BASE + 0x14),
    SLV_IMSC    = (SLV_BASE + 0x18),
    SLV_RIS     = (SLV_BASE + 0x1C),
    SLV_MIS     = (SLV_BASE + 0x20),
    SLV_ICR     = (SLV_BASE + 0x24),
    SLV_DMACR   = (SLV_BASE + 0x28),
    SLV_TDR     = (SLV_BASE + 0x2C),
    SLV_GPUSTAT = (SLV_BASE + 0x30),
    SLV_HCTRL   = (SLV_BASE + 0x34),
    SLV_DEBUG1  = (SLV_BASE + 0x38),
    SLV_DEBUG2  = (SLV_BASE + 0x3C),

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
        uint8_t err_acknowledge_error : 1;
        uint8_t clock_stretch_timeout : 1;
        uint32_t reserved_bits : 22;
    };
    uint32_t as_int;
} bsc_status_t;

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

typedef union slv_data {
    struct {
        uint8_t data : 8;
        uint8_t overrun_error : 1;
        uint8_t underrun_error : 1;
        uint16_t reserved_0 : 6;
        uint8_t transmit_busy : 1;
        uint8_t rx_fifo_empty : 1;
        uint8_t tx_fifo_full : 1;
        uint8_t rx_fifo_full : 1;
        uint8_t tx_fifo_empty : 1;
        uint8_t rx_busy : 1;
        uint8_t tx_fifo_level : 5;
        uint8_t rx_fifo_level : 5;
    };
    uint32_t as_int;
} slv_data_t;

typedef union slv_addr {
    struct {
        uint8_t address : 7;
        uint32_t reserved_bits: 25;
    };
    uint32_t as_int;
} slv_addr_t;

typedef union slv_control {
    struct {
        uint8_t device_enable : 1;
        uint8_t spi_mode_enable : 1;
        uint8_t i2c_mode_enable : 1;
        uint8_t clock_phase : 1;
        uint8_t clock_polarity : 1;
        uint8_t status_enable : 1;
        uint8_t control_enable : 1;
        uint8_t break_current_operation : 1;
        uint8_t transmit_enable : 1;
        uint8_t receive_enable : 1;
        uint8_t inverse_rx_status_flags : 1;
        uint8_t test_fifo : 1;
        uint8_t enable_host_control : 1;
        uint8_t inverse_tx_status_flags : 1;
        uint32_t reserved_bits : 18;
    };
    uint32_t as_int;
} slv_contorl_t;

typedef union slv_flags {
    struct {
        uint8_t transmit_busy : 1;
        uint8_t rx_fifo_empty : 1;
        uint8_t tx_fifo_full : 1;
        uint8_t rx_fifo_full : 1;
        uint8_t tx_fifo_empty : 1;
        uint8_t rx_busy : 1;
        uint8_t tx_fifo_level : 5;
        uint8_t rx_fifo_level : 5;
        uint16_t reserved_bits : 16;
    };
    uint32_t as_int;
} slv_flags_t;

void bsc_master_init(void);
void bsc_slave_init(void);

#endif