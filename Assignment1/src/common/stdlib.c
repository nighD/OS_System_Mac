#include "stdlib.h"

#define true 1;
#define false 0;

void bzero(void* dest, int bytes){
    char* d = dest;
    while (bytes--)
        *d++ = 0;
}

// The delay function is used to delay short amount of time after a function's execution
void delay(uint32_t count){
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n": "=r"(count) : [count] "0" (count) : "cc");
}

//Function to convert an integer to C string
char* itoa(int i){
    int isNegativeNum = false;
    int size = 0;
    int num = i;    //store the integer value
    char* arg;

    //If the integer value is negative
    if (i < 0) { 
        i = -i;                 //Convert to positive integer
        isNegativeNum = true; 
        size++;                 //Increase the value of size by 1 for the character '-' in the C string
    }

    // Convert integer value 0 to character '0'
    if (i == 0) {
        size += 2; 
        char buffer[size];      //Create an array of char with the corresponding size value
        arg = buffer;           //Char pointer arg is assigned the address of the first element in array buffer
        *(arg+size-1) = '\0';   //Store the null terminated character to the index 1
        *arg = i + '0';         //Convert to character '0' using ASCII value of '0'
        delay(1);               //Delay the function for short amount of time 
    }

    //This chunk of code is used for integer value is positive and negative integer value
    //that has been converted to positive value from line 25
    if (i > 0){
        while(num != 0){    //While loop for counting number of digits in the integer value.
            num /= 10;  
            size++;
        }
        char buffer[size];  //Declare an array with the respective size of the number of digits that is counted from while loop above
        arg = buffer;       //Pointer point to the address of the first element of the array buffer
        *(arg+size) = '\0'; //Set the last index of the array buffer to a null terminated character
        
        /*Looping through all digits and converting all digits to character with respective ASCII value
          Get the last digit in an integer value by using modulus operator. Then add to the ASCII value of character '0' 
          which is 48 in decimal form to get the correct decimal value of that digit. Subsequently, assign that value to 
          to the index of buffer array using char pointer *arg. The value of index is in corresponding with the position of
          that digit in the integer value of i*/
        while(size != 0){   
            *(arg+size-1) = (i % 10) + '0'; 
            i /= 10;    //Get the new integer value without the digit that has been converted to character
            size--;     
        }
        //After converting, if the integer value is negative. Assign the character '-'
        if(isNegativeNum == 1) { arg[size] = '-'; }
    }

    return arg;
}

//Function to convert a C string to integer value
int atoi (char *str){
    int num = 0, i = 0, sign = 1;

    if (*str == '\0') { return 1; }

    //Check if the string has the prefix negative sign at index 0 of the C string
    if (str[0] == '-') { 
        sign = -1;
        i++;    //Increase value of i by 1 in order to start converting the C string at index 1 
                //of the normal character from '0'..'9'
    }

    //Looping through the C string to convert to integer value
    for (; str[i] != '\0'; i++){
        if(str[i] < '0' || str[i] > '9') { return 1; }  //Check if the character has the ASCII value is not in range of '0' to '9'
        num = num * 10 + str[i] - '0';                  //Convert the character to integer by substracting with the ASCII value of '0'
    }
    num *= sign;    //If the C string has the prefix '-' as mentioned at line 75. Convert the integer value to negative
    
    return num;
}

//Function to convert an integer value to hexadecima value
char* dectohex(int i){
    int num = i;
    int size = 0;
    char* hex;

    //While loop to count the necessary size for the array that will contain the converted hex value.
    while (num != 0){
        num /= 16;
        size++;
    }

    char hexvalue[size];
    hex = hexvalue;
    *(hex+size) = '\0';     //Assign null character to the end of the array

    while ( i != 0){        
        if ((i % 16) < 10){                 //Check for the convertible values are in range from 0 to 9
            *(hex+size-1) = (i % 16) + '0'; //Get the ASCII value of an number by adding with the ASCII value of '0' which is 48
        } else {                            //The convertible values are greater than 10 which is from 'A' to 'F' in hexadecimal form
            *(hex+size-1) = (i % 16) + '7'; //Get the ASCII value starting from character 'A' by adding with the ASCII value of '7' which is 55
        }
        size--;
        i /= 16;
    }
    delay(1);   //Delay for a short amount of time after executing the function.
    return hex;
}
