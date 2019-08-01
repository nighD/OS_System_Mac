#include "bsc.h"

void bsc_master_init(void){
    bsc_control_t bsc_control_reg;
    bsc_dlen_t bsc_dlen_reg;
    bsc_slave_addr_t bsc_slave_addr_reg;
    bsc_status_t bsc_status_reg;

    bzero(&bsc_control_reg, 4);
    bzero(&bsc_dlen_reg, 4);
    bzero(&bsc_slave_addr_reg, 4);
    bzero(&bsc_status_reg, 4);

    mmio_write(BSC1_C, bsc_control_reg.as_int);
    mmio_write(BSC1_DLEN, bsc_dlen_reg.as_int);
    mmio_write(BSC1_A, bsc_slave_addr_reg.as_int);
    mmio_write(BSC1_S, bsc_status_reg.as_int);

    //Enable Pin 2 and 3
    mmio_write(GPPUD, 0x00000000);
    //delay 150 cycles to provide the required set-up time for control signal
    delay(150);
    mmio_write(GPPUDCLK0, (1 << 2) | (1 << 3));
    delay(150);
    mmio_write(GPPUDCLK0, 0x00000000);
    bsc_control_reg.i2c_enable = 1;
    mmio_write(BSC1_C, bsc_control_reg.as_int);
    bsc_dlen_reg.data_length &= ~(0xFFFFul);
    mmio_write(BSC1_DLEN, bsc_dlen_reg.as_int);
    bsc_dlen_reg.data_length |= (0xFF << 0);
    mmio_write(BSC1_DLEN, bsc_dlen_reg.as_int);
    bsc_slave_addr_reg.address = ADDR_RTC;
    mmio_write(BSC1_A, bsc_slave_addr_reg.as_int);
    bsc_control_reg.read = 0;
    mmio_write(BSC1_C, bsc_control_reg.as_int);
    bsc_control_reg.start_transfer = 1;
    mmio_write(BSC1_C, bsc_control_reg.as_int);

    do {
        bsc_status_reg.as_int = mmio_read(BSC1_S);
    } while (!(bsc_status_reg.transfer_active & 1));
    // bsc_dlen_reg.data_length = (0x0F << 0);
    bsc_control_reg.read = 1;
    mmio_write(BSC1_C, bsc_control_reg.as_int);
    bsc_control_reg.start_transfer = 1;
    mmio_write(BSC1_C, bsc_control_reg.as_int);

}