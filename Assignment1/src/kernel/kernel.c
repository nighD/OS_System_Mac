#include "kernel.h"

void kernel_main(){
    uart_init();
    
    puts("EEET2490: Embedded Systems - Operating Systems & Interfacing \n");
    puts("------------------------------------------------------------ \n");
    puts("Assessment Group: 12 \n");
    puts("s3678436: Khoa Dang Le \n");
    puts("s3595082: Bao Gia Le \n");
    puts("s3695424: Anh Duy Ngo \n");

    // puts("------------------------------------------------------------ \n");
    // puts("Implementation of all functions in deliverable 4 \n");
    // puts("------------------------------------------------------------ \n");
    // puts("Function itoa(): ");
    // puts(itoa(-12318474));
    // putc('\n');
    // puts("Function itoa(): ");
    // puts(itoa(0));
    // putc('\n');
    // puts("Function dextohex(): ");
    // puts(dectohex(999));
    // putc('\n');
    // puts("Function atoi(): ");
    // puts(itoa(atoi("-199972")));
    // putc('\n');

    char buffer[BUFFERLENGTH];
    while(1){
        gets(buffer, BUFFERLENGTH);
    }
}