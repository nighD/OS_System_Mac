#include "stdio.h"

char getc(void){
    return uart_getc();
}

void putc(char c){
    uart_putc(c);
}

void gets(char* buffer, int bufferLength){
    char c;
    int i;
    for (i = 0; ((c = getc()) != '\r' && (bufferLength > 1)) || c == 127; i++, bufferLength--){ 
        //The variable of type char named c will get each character from console until the '\r' is detected from keyboard
        //which is the enter key.'\r' is the CR which will return a new line where the cursor will start at the beginning 
        //of the line on the console.
        putc(c);

        //The condition c == 127 in for loop help to detect when the backspace key on the keyboard is pressed.
        //In order to get the deletion of character on console, the if statement at line 22 is used
        //Increase the bufferLength by 2 because we want to compensate once time when we press the backspace key
        //to return back the initial bufferLength value if the whole line is deleted
        if(c == 127 && i > 0){
            bufferLength += 2;
            i -= 2;
            continue;
        }
        buffer[i] = c;  
    }
    putc('\n');
    if (c == '\r')    //This condition exist to put the null terminated character to the last index of buffer array
        buffer[i] = '\0';
    else  
        buffer[bufferLength - 1] = '\0';
}

void puts(const char* buffer){
    for (int i = 0; buffer[i] != '\0'; i++) { putc(buffer[i]); }
}

