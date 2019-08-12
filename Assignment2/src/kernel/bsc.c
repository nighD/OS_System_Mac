#include "bsc.h"

void clear_status(){
    bsc_status_t bsc_status_reg;
    bsc_status_reg.as_int = mmio_read(BSC1_S);
    bsc_status_reg.clock_stretch_timeout = 1;
    bsc_status_reg.acknowledge_error = 1;
    bsc_status_reg.transfer_done = 1;
    mmio_write(BSC1_S, bsc_status_reg.as_int);
}

void i2c_setSlaveAddress(uint8_t addr){
    bsc_slave_addr_t bsc_slave_addr_reg;
    bsc_slave_addr_reg.as_int = mmio_read(BSC1_A);
    bsc_slave_addr_reg.address = addr;
    mmio_write(BSC1_A, bsc_slave_addr_reg.as_int);
}

void start_tx(uint8_t mode) {
    bsc_control_t bsc_control_reg;
    bsc_control_reg.as_int = mmio_read(BSC1_C);
    bsc_control_reg.read = mode;
    bsc_control_reg.start_transfer = 1;
    mmio_write(BSC1_C, bsc_control_reg.as_int);
}

void stop_tx(void) {
    bsc_status_t bsc_status_reg;
    bsc_status_reg.as_int = mmio_read(BSC1_S);
    bsc_status_reg.transfer_done = 1;
    mmio_write(BSC1_S, bsc_status_reg.as_int);
}

void clear_fifo(void) {
    bsc_control_t bsc_control_reg;
    bsc_control_reg.as_int = mmio_read(BSC1_C);
    bsc_control_reg.clear = 0b10;
    mmio_write(BSC1_C, bsc_control_reg.as_int);
}

void read_fifo(uint8_t* data, uint32_t len) {
    bsc_status_t bsc_status_reg;
    uint32_t i = 0;

    bsc_status_reg.as_int = mmio_read(BSC1_S);
    while(!(bsc_status_reg.transfer_done & BSC1_S_TA)){
        while(bsc_status_reg.as_int & BSC1_S_RXD && (i < len)){
            data[i] = mmio_read(BSC1_FIFO);
            i++;
            bsc_status_reg.as_int = mmio_read(BSC1_S);
        }
        bsc_status_reg.as_int = mmio_read(BSC1_S);
    }
}

void write_fifo(uint8_t* data, uint32_t len) {
    bsc_fifo_t bsc_fifo_reg;
    uint32_t i = 0;
    bsc_fifo_reg.as_int = mmio_read(BSC1_FIFO);
    while(i < len){
        bsc_fifo_reg.data = data[i];
        mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
        i++;
    }
}

void i2c_init(void){
    bsc_control_t bsc_control_reg;

    //Disable pull-up/pull-down control of Pin 2 and 3
    set_pud(GPPUDCLK0, 2, 1);
    set_pud(GPPUDCLK0, 3, 1);
    //GPFSEL0 for FSEL2 and FSEL3 (SDA1 and SCL1)
    mmio_write(GPFSEL0, (4 << 6) | (4 << 9));
    //Set slave address
    i2c_setSlaveAddress(ADDR_RTC);
    //enable transfer
    bsc_control_reg.as_int = mmio_read(BSC1_C);
    bsc_control_reg.i2c_enable = 1;
    mmio_write(BSC1_C, bsc_control_reg.as_int);
}

void i2c_read(uint8_t* buf, uint32_t len){
    bsc_dlen_t bsc_dlen_reg;

    clear_fifo();   //Clear FIFO
    
    //Set data length
    bsc_dlen_reg.as_int = mmio_read(BSC1_DLEN);
    bsc_dlen_reg.data_length = len;
    mmio_write(BSC1_DLEN, bsc_dlen_reg.as_int);

    start_tx(BSC1_C_READ);      //Start transfer
    read_fifo(buf, len);
    stop_tx();                  //Stop transfer
}

void i2c_write(uint8_t* buf, uint32_t len){
    bsc_dlen_t bsc_dlen_reg;
    bsc_status_t bsc_status_reg;

    clear_fifo();       //Clear FIFO
    clear_status();     //Clear status of field CLKT, TA and DONE

    //Set data length
    bsc_dlen_reg.as_int = mmio_read(BSC1_DLEN);
    bsc_dlen_reg.data_length = len;
    mmio_write(BSC1_DLEN, bsc_dlen_reg.as_int);

    write_fifo(buf, len);       //Write to fifo
    start_tx(BSC1_C_WRITE);     //Start transfers

    do {
        bsc_status_reg.as_int = mmio_read(BSC1_S);
    } while(!bsc_status_reg.transfer_done & BSC1_S_TA);

    stop_tx();                  //Stop transfer


}