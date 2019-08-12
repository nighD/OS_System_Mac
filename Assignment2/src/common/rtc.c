#include "rtc.h"

unsigned int bcd_to_decimal(unsigned int bcd) 
{
    return (((bcd & 0xf0)>>4) * 10 + (bcd & 0x0f));
}

unsigned int decimal_to_bcd(unsigned int d)
{
    return (((d/10)<<4) + (d%10));
}
void convertMode(uint8_t is12,uint8_t data){
    bsc_dlen_t bsc_dlen_reg;
    bsc_fifo_t bsc_fifo_reg;
    bsc_status_t bsc_status_reg;
    if (is12 == true){
        if(data = 12){
            data = bcd_to_decimal(decimal_to_bcd(data)+(1<<6)+(1<<5));
        }
        else if (data > 12){
            data = bcd_to_decimal(decimal_to_bcd(data - 12)+(1<<6)+(1<<5));
        }
        else{
            data = bcd_to_decimal(decimal_to_bcd(data)+(1<<6));
        }
    }
    else{
        data = decimal_to_bcd(data);
        data &= ~(1<<6);
        if (data & (1<<5))
        {
            if (bcd_to_decimal(data)<=11){
                data &= ~(1<<5);
                data = (data & 0x1F) + 12;  
            }
            else{
                data = (data & 0x1F);
            }

        } else
        {
            data = (data & 0x1F);     
        }
    }
    puts("\n");
        //Clear FIFO
    clear_fifo();

    //Clear status of field CLKT, TA and DONE
    clear_status();
    //Set data length
    bsc_dlen_reg.as_int = mmio_read(BSC1_DLEN);
    bsc_dlen_reg.data_length = 2;
    mmio_write(BSC1_DLEN, bsc_dlen_reg.as_int);

    //pre populate FIFO with max buffer
    bsc_fifo_reg.as_int = mmio_read(BSC1_FIFO);

    bsc_fifo_reg.data = 0x02;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    bsc_fifo_reg.data = decimal_to_bcd(data);
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    start_tx(BSC1_C_WRITE);

    do {
        bsc_status_reg.as_int = mmio_read(BSC1_S);
    } while(!bsc_status_reg.transfer_done & BSC1_S_TA);

    stop_tx();
}
void setTimeForRTC(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year,uint8_t is12){
    bsc_dlen_t bsc_dlen_reg;
    bsc_fifo_t bsc_fifo_reg;
    bsc_status_t bsc_status_reg;
    if (is12 == true){
        if (bcd_to_decimal(hour) > 12){
            hour = decimal_to_bcd(bcd_to_decimal(hour)- 12)+(1<<6)+(1<<5);
        }
        else{
            hour = decimal_to_bcd(bcd_to_decimal(hour))+(1<<6)+(0<<5);
        }
    }
    else{
        hour = decimal_to_bcd(bcd_to_decimal(hour))+(0<<6);
    };
    //Clear FIFO
    clear_fifo();

    //Clear status of field CLKT, TA and DONE
    clear_status();
    
    //Set data length
    bsc_dlen_reg.as_int = mmio_read(BSC1_DLEN);
    bsc_dlen_reg.data_length = 8;
    mmio_write(BSC1_DLEN, bsc_dlen_reg.as_int);

    //pre populate FIFO with max buffer
    bsc_fifo_reg.as_int = mmio_read(BSC1_FIFO);

    //Set SECONDS
    bsc_fifo_reg.data = 0x00;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    bsc_fifo_reg.data = second;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    //Set MINUTES
    bsc_fifo_reg.data = minute;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    //Set HOURS
    bsc_fifo_reg.data = hour;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    //Set Day
    bsc_fifo_reg.data = day;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    //set DATE
    bsc_fifo_reg.data = date;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    //set MONTH
    bsc_fifo_reg.data = month;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);
    //set YEAR
    bsc_fifo_reg.data = year;
    mmio_write(BSC1_FIFO, bsc_fifo_reg.as_int);

    //Enable device and start transfers
    start_tx(BSC1_C_WRITE);

    do {
        bsc_status_reg.as_int = mmio_read(BSC1_S);
    } while(!bsc_status_reg.transfer_done & BSC1_S_TA);

    stop_tx();
}