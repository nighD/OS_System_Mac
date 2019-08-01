#ifndef __STDIO__
#define __STDIO__
#include "uart.h"

char getc(void);
void putc(char c);
void gets(char* buffer, int bufferLength);
void puts(const char* buffer);

#endif