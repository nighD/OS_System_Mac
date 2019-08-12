#include "kernel.h"

void kernel_main(){
    uint8_t buff[7];
    uint8_t sub_data_hour[2]={0x02};
    uint8_t sub_data[2] = {0x00};
    uint8_t clock_halt_addr = 0x00;
    uint8_t hour_addr = 0x02;
    uint32_t keyPressed = 'r';
    uint8_t isPaused = false;
    uart_flags_t flags;
    rtc_data_t rtc_data;
    uint8_t is12; 

    uart_init();
    i2c_init();

    i2c_write(&clock_halt_addr, 1);
    i2c_read(&sub_data[1], 1);
    i2c_write(sub_data, 2);
    // setTimeForRTC(decimal_to_bcd(50), decimal_to_bcd(59), decimal_to_bcd(11), decimal_to_bcd(3), decimal_to_bcd(6), decimal_to_bcd(8), decimal_to_bcd(19),is12);

    puts("EEET2490: Embedded Systems - Operating Systems & Interfacing \n");
    puts("------------------------------------------------------------ \n");
    puts("Assessment Group: 12 \n");
    puts("s3678436: Khoa Dang Le \n");
    puts("s3595082: Bao Gia Le \n");
    puts("s3695424: Anh Duy Ngo \n\n");
    puts("DS1307 Real Time Clock Data \n");
    puts("------------------------------ \n");

    while(1){
        //Set all addresses of struct members inside union variable named rtc_data to 0
        bzero(&rtc_data, 8);
        //Read key that is pressed from receive FIFO of UART
        flags = read_flags();
        while(!flags.receive_queue_empty){
            keyPressed = mmio_read(UART0_DR);
            if(keyPressed == 'p' || keyPressed == 'P'){
                isPaused = true;
                break;
            }
            if(keyPressed == 'r' || keyPressed == 'R'){
                isPaused = false;
                break;
            }
            if(keyPressed == 'c' || keyPressed == 'C'){
                i2c_write(&hour_addr, 1);
                i2c_read(&sub_data_hour[1], 1);
                if(sub_data_hour[1] & 0x40){
                    is12 = false;
                }
                else {
                    is12 = true;
                }
                // puts(itoa(sub_data_hour[1]) & 0x7F);
                convertMode(is12,bcd_to_decimal(sub_data_hour[1]& 0x7F));
                break;
            }
            flags = read_flags();
        }

        if(isPaused == false){
            i2c_write(&clock_halt_addr, 1);
            i2c_read(buff, 7);

            //Store data that is read from RTC to struct of RTC
            for(int i = 0; i < 7; i++){
                rtc_data.as_int |= ((uint64_t) buff[i] << (i * 8));
            }

            //Print Day 
            switch (atoi(dectohex(rtc_data.day))){
                case Sunday: 
                    puts("Sunday  ");
                    break;
                case Monday:
                    puts("Monday  ");
                    break;
                case Tuesday:
                    puts("Tuesday  ");
                    break;
                case Wednesday:
                    puts("Wednesday  ");
                    break;
                case Thursday:
                    puts("Thursday  ");
                    break;
                case Friday:
                    puts("Friday  ");
                    break;
                case Saturday:
                    puts("Saturday  ");
                    break;
                default:
                    puts("ERROR  ");
                    break;
            }

            //Print DD/MM/YYYY
            puts(dectohex(rtc_data.date));
            puts("/");
            puts(dectohex(rtc_data.month));
            puts("/");
            puts(dectohex(rtc_data.year));
            puts("  ");

            //Print hh:mm:ss
            if(rtc_data.hours & 0x40)
            {
                if(rtc_data.hours & 0x20)
                {
                    puts("PM ");
                }
                else 
                {
                    puts("AM ");
                }
                puts(dectohex(rtc_data.hours & 0x1F));
            } else
            {
                puts(dectohex(rtc_data.hours));
            }
            
            
            puts(":");
            puts(dectohex(rtc_data.minutes));
            puts(":");
            puts(dectohex(rtc_data.seconds));
            puts("\n");
        }
        delay(5671300);
    }
}