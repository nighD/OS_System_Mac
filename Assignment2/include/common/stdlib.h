#ifndef __STDLIB__
#define __STDLIB__
#include <stdint.h>
#include "stdio.h"

#define true 1
#define false 0

void bzero(void* dest, int bytes);
void delay(uint32_t count);
char* itoa(int i);
int atoi(char* arg);
char* dectohex(int i);


#endif