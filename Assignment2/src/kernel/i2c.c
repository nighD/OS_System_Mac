#include "i2c.h"
#include "uart.h"
#include <stdint.h>


#define gpio GPIO_BASE
// #define INP_GPIO(g)   *(gpio + ((g)/10)) &= ~(7<<(((g)%10)*3))
// #define OUT_GPIO(g)   *(gpio + ((g)/10)) |=  (1<<(((g)%10)*3))
// #define SET_GPIO_ALT(g,a) *(gpio + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))

// #define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
// #define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0

#define GPFSEL0      ((volatile unsigned int*)(GPIO_BASE+ 0x0))
#define GPFSEL1      ((volatile unsigned int*)(GPIO_BASE+ 0x4))
#define GPFSEL2      ((volatile unsigned int*)(GPIO_BASE+ 0x8))
#define GPFSEL3      ((volatile unsigned int*)(GPIO_BASE+ 0xc))
#define GPSET0       ((volatile unsgined int*)(GPIO_BASE+ 0x1C))
#define GPSET1       ((volatile unsgined int*)(GPIO_BASE+ 0x1C))

// void i2c_init()
// {
//     INP_GPIO(0);
//     SET_GPIO_ALT(0,0);
//     INP_GPIO(1);
//     SET_GPIO_ALT(1,0);
// }

void i2c_init()
{
    // *GPFSEL2 &= ~(7 << 0);
    // *GPFSEL2 |= (1 << 4);
    // *GPFSEL3 &= ~(7 << 0);
    // *GPFSEL3 |= (1 << 4);
	*BSC0_C = BSC_C_I2CEN | BSC_C_CLEAR | (1<<5);
	*BSC0_S = CLEAR_STATUS;

    *GPFSEL0 &= ~(7 << 0);
    *GPFSEL0 |= (1 << 4);
    *GPFSEL1 &= ~(7 << 0);
    *GPFSEL1 |= (1 << 4);
	// Clear ERR flag, CLKT flag, DONE flag save to S Reg
	
	// // Enable I2C and clear buffer
	
	// *BSC0_DIV = 0x5dc;

	
	// Get the address of DS1307 
	// *BSC0_A = DS1307_ADDR;
	// *BSC0_DLEN = 1;
	// unsigned int i = 1;
	// *BSC0_C &= ~(BSC_C_READ);
	// *BSC0_C |= BSC_C_ST | BSC_C_CLEAR | (1 << 5);
	// *BSC0_FIFO = 0x50;
	// while(!((*BSC0_S) & BSC_S_DONE) && i)
	// {
	
	// *BSC0_DLEN = 1;    // one byte
    // *BSC0_FIFO = 0;    // value 2
    // *BSC0_S = CLEAR_STATUS; // Reset status bits (see #define)
    // *BSC0_C = START_WRITE;    // Start Write (see #define)

    // wait_i2c_done();

    //////
    // Start Read of RTC chip's time
    //////
    // *BSC0_DLEN = 3;
    // *BSC0_S = CLEAR_STATUS; // Reset status bits (see #define)
    // *BSC0_C = START_READ;    // Start Read after clearing FIFO (see #define)

    // wait_i2c_done();
	// unsigned char buffer[3];
    // // Store the values read in the tm structure, after masking unimplemented bits.
    // buffer[0] = bcd_to_decimal(*BSC0_FIFO & 0x7f);
    // buffer[1] = bcd_to_decimal(*BSC0_FIFO & 0x7f);
    // buffer[2] = bcd_to_decimal(*BSC0_FIFO & 0x3f);

	// 	if (*BSC0_S & BSC_S_ERR)
	// 	{
	// 		*BSC0_S |= BSC_S_ERR;
	// 		puts("Cannot get the address slave");
	// 	} else if (*BSC0_S & BSC_S_CLKT)
	// 	// Check if bit 9 CLKT is set ( 1 = Slave has held the SCL signal low (clock stretching) for longer
	// 	// and that specified in the ÌCCLKT register Cleared by writing 1 to the field
	// 	{
	// 		*BSC0_S |= BSC_S_CLKT;
	// 		puts("I2C Timeout or Clock Stretch Timeout");
	// 	} else
	// 	{
	// 		puts("Not finished writing yet!");
	// 	}
	// 	if (*BSC0_S & BSC_S_TXD)
	// 	{
	// 		i--;
	// 	}
		
	// }
	// *BSC0_S = CLEAR_STATUS;
	// puts("Writing Sucessfully!");
	// *BSC0_S |= BSC_S_DONE;
	// Check if bit 8 ERR is set (NACK)
	
}

	/// Set operation for DS1307
	// unsigned int a[2] = {0,0}; 
	// writingI2C(&a,2,DS1307_ADDR); //Set operation for DS1307 by CH bit control to 0
	// unsigned int buffer[3];
	// readingI2C(buffer,3,DS1307_ADDR);
	// puts("Vo roi nha");
	// puts(itoa(buffer[0]));
	// Set data length
	// *BSC0_DLEN = 1; //How many byte to write on it 

	// Now send all data bytes to FIFO until DONE 
	//Get S_REG Content
	
	/// After that we need a short delay 
	/// Going to the main loop
	// Get the datetime from DS1307 
	// *BSC0_A = DS1307_ADDR;

	/// Create a buffer or struct data to hold time 
	// buffer[7];
	
	// Delay a little bit before next transactions 
	// Delay_1ms();
	
	// Get the RPI Slave ADDRESS
	// *BSC0_A = RPI_SLAVE_ADDR;
	
	// Delay a little bit before next transactions 
	// Delay_1ms();
	





void wait_i2c_done()
{
    int timeout = 50;
	register unsigned int r;
    while ((!((*BSC0_S) & BSC_S_DONE)) && --timeout) {
        // delay(1000);
        // wait_milisec(1);
		puts(itoa(bcd_to_decimal(*BSC0_S)));
		r=36000; while(r--) { asm volatile("nop"); }
    }
    if (timeout==0)
        puts("Error: wait_i2c_done() timeout.\n");
}
// Need the I2C slave address of device if you want to communicate with
// by using the BSC0_A address

//Write the quantity of bytes you want to send or receive by BSC0_DLEN

//Write to the slave, use BSC0_FIFO

//Clear the status register BSC0_S = CLEAR_STATUS

//Start to write or start to read by BSC0_C
// Command: BSC0_C = START_WRITE or BSC0_C = START_READ

//First writing the slave address to the bus, by writing address to BSC0_A

//Write the address of the RTC we want to read from the bus

unsigned int bcd_to_decimal(unsigned int bcd) 
{
    return (((bcd & 0xf0)>>4) * 10 + (bcd & 0x0f));
}

unsigned int decimal_to_bcd(unsigned int d)
{
    return (((d/10)<<4) + (d%10));
}


void readingI2C(unsigned int *readingBuffer,unsigned int DATA_LENGTH, unsigned int ADDR)
{
	*BSC0_DLEN = DATA_LENGTH;
	*BSC0_C |= BSC_C_READ; // Set the operation for reading
	*BSC0_C |= BSC_C_ST;
	// Check DONE bit if all data have been sent, or continue sending
	unsigned int i = 0;
	while (!(*BSC0_S & BSC_S_DONE) && DATA_LENGTH)
	{
		puts("In reading loop");
		// Check if bit 8 ERR is set (NACK)
		if (*BSC0_S & BSC_S_ERR)
		{
			*BSC0_S |= BSC_S_ERR;
			puts("Cannot get the address slave");
		}
		// Check if bit 9 CLKT is set ( 1 = Slave has held the SCL signal low (clock stretching) for longer
		// and that specified in the ÌCCLKT register Cleared by writing 1 to the field
		if (*BSC0_S & BSC_S_CLKT)
		{
			*BSC0_S |= BSC_S_CLKT;
			puts("I2C Timeout");
		}
		while (!(*BSC0_S & BSC_S_RXD)); //Wait until FIFO is empty or more byte to be received
		DATA_LENGTH--;
		puts("Get data from Slave: ");
		puts(itoa(i));
		readingBuffer[i++] = bcd_to_decimal(*BSC0_FIFO & 0x7f); //Get the new bytes and increase the pointer // going to next byte
		
	}	
	*BSC0_S |= BSC_S_DONE;
}

void writingI2C(unsigned int* writingBuffer,unsigned int DATA_LENGTH,unsigned int ADDR)
{
	//Set the address to write to slave
	*BSC0_A = ADDR;
	//Set the data length for writing to slave
	*BSC0_DLEN = DATA_LENGTH;
	*BSC0_C |= BSC_C_CLEAR | (1 << 5);
	*BSC0_FIFO = 0xAA;
	*BSC0_S = CLEAR_STATUS;
	// Configure write transaction by writing 0 to READ
	*BSC0_C &= ~BSC_C_READ;
	// Clear FIFO before transmit and set start bit by ST (starting transfer)
	*BSC0_C |= BSC_C_ST;
	unsigned int i=0;

	// Check DONE bit if all data have been sent, or continue sending
	// while (!(*BSC0_S & BSC_S_DONE) && DATA_LENGTH)
	// {	
	// 	puts("In wrting loop");
	// 	// Check if bit 8 ERR is set (NACK)
	// 	if (*BSC0_S & BSC_S_ERR)
	// 	{
	// 		*BSC0_S |= BSC_S_ERR;
	// 		puts("Cannot get the address slave");
	// 	}
	// 	// Check if bit 9 CLKT is set ( 1 = Slave has held the SCL signal low (clock stretching) for longer
	// 	// and that specified in the ÌCCLKT register Cleared by writing 1 to the field
	// 	if (*BSC0_S & BSC_S_CLKT)
	// 	{
	// 		*BSC0_S |= BSC_S_CLKT;
	// 		puts("I2C Timeout");
	// 	}
	// 	while (!(*BSC0_S & BSC_S_TXE)); //Wait until FIFO is full or cannot accept data for transmisison
	// 	DATA_LENGTH--;
	// 	puts("Send data to Slave: ");
	// 	puts(itoa(i));
	// 	*BSC0_FIFO = decimal_to_bcd(writingBuffer[i++]);//Get the new bytes and increase the pointer // going to next byte
	// }
	// *BSC0_S |= BSC_S_DONE;
}

// void writingI2C(unsigned int* writingBuffer,unsigned int DATA_LENGTH,unsigned int ADDR)
// {
// 	//Set the address to write to slave
// 	// *BSC0_A = ADDR & 0x7f;
// 	*BSC0_A = DS1307_ADDR;

// 	//Set the data length for writing to slave
// 	*BSC0_DLEN = DATA_LENGTH;
// 	// Configure write transaction by writing 0 to READ
// 	*BSC0_C &= ~BSC_C_READ;
// 	*BSC0_C |= BSC_C_CLEAR | (1<<5);

// 	puts("Status C:\n");
// 	puts(itoa(bcd_to_decimal(*BSC0_C)));
// 	puts("Status C1:\n");
// 	puts(itoa(bcd_to_decimal(*BSC0_C>>8)));
// 	puts("Status S:\n");
// 	puts(itoa(bcd_to_decimal(*BSC0_S)));
// 	unsigned int i=0;
// 	*BSC0_FIFO = 0;
// 	*BSC0_C |= BSC_C_ST;
// 	// wait_i2c_done();
// 	// Check DONE bit if all data have been sent, or continue sending
// 	while (!(*BSC0_S & BSC_S_DONE))
// 	{	
// 		// puts("In wrting loop");
// 			puts("Status S:\n");
// 	puts(itoa(bcd_to_decimal(*BSC0_S)));
// 		// puts(itoa((*BSC0_S & BSC_S_TXD)));
// 		// puts(itoa((*BSC0_S & BSC_S_TXE)));
// 		// puts(itoa((*BSC0_S & BSC_S_RXD)));
// 		// while(!(*BSC0_S & BSC_S_TXD) && DATA_LENGTH);
// 		// {
// 		// 	puts("Send data to Slave: ");
// 		// 	puts(itoa(i));
// 			*BSC0_FIFO = decimal_to_bcd(writingBuffer[i++]); //Get the new bytes and increase the pointer // going to next byte
// 			DATA_LENGTH--;
// 		// }
// 	}
// // Check if bit 8 ERR is set (NACK)
// 	if (*BSC0_S & BSC_S_ERR)
// 	{
// 		*BSC0_S |= BSC_S_ERR;
// 		puts("Cannot get the address slave");
// 	} else if (*BSC0_S & BSC_S_CLKT)
// 	// Check if bit 9 CLKT is set ( 1 = Slave has held the SCL signal low (clock stretching) for longer
// 	// and that specified in the ÌCCLKT register Cleared by writing 1 to the field
// 	{
// 		*BSC0_S |= BSC_S_CLKT;
// 		puts("I2C Timeout or Clock Stretch Timeout");
// 	} else if (DATA_LENGTH)
// 	{
// 		puts("BSC signal done but data still remained");
// 	} else 
// 	{
// 		puts("Write successfully");
// 	}
// 	*BSC0_S |= BSC_S_DONE;
// }


#define GPFSEL0      ((volatile unsigned int*)(GPIO_BASE+ 0x0))
#define GPFSEL1      ((volatile unsigned int*)(GPIO_BASE+ 0x4))
#define GPFSEL2      ((volatile unsigned int*)(GPIO_BASE+ 0x8))
#define GPFSEL3      ((volatile unsigned int*)(GPIO_BASE+ 0xc))
#define GPSET0       ((volatile unsgined int*)(GPIO_BASE+ 0x1C))
#define GPSET1       ((volatile unsgined int*)(GPIO_BASE+ 0x1C))
#define GPPUD           ((volatile unsigned int*)(MMIO_BASE+0x00200094))
#define GPPUDCLK0       ((volatile unsigned int*)(MMIO_BASE+0x00200098))
#define BCM2835_PERI_BASE               0x3F000000

#define BCM2835_GPFSEL0                      0x0000 ///< GPIO Function Select 0
#define MAP_FAILED	((void *) -1)
#define BCM2835_BSC1_BASE				(BCM2835_PERI_BASE + 0x804000)

#define BCM2835_CORE_CLK_HZ				250000000	///< 250 MHz

// Physical addresses for various peripheral register sets
/// Base Physical Address of the BCM 2835 peripheral registers
/// Base Physical Address of the System Timer registers
#define BCM2835_ST_BASE					(BCM2835_PERI_BASE + 0x3000)
/// Base Physical Address of the Pads registers
#define BCM2835_GPIO_PADS               (BCM2835_PERI_BASE + 0x100000)
/// Base Physical Address of the Clock/timer registers
#define BCM2835_CLOCK_BASE              (BCM2835_PERI_BASE + 0x101000)
/// Base Physical Address of the GPIO registers
#define BCM2835_GPIO_BASE               (BCM2835_PERI_BASE + 0x200000)
/// Base Physical Address of the SPI0 registers
#define BCM2835_SPI0_BASE               (BCM2835_PERI_BASE + 0x204000)
/// Base Physical Address of the BSC0 registers
#define BCM2835_BSC0_BASE 				(BCM2835_PERI_BASE + 0x205000)
/// Base Physical Address of the PWM registers
#define BCM2835_GPIO_PWM                (BCM2835_PERI_BASE + 0x20C000)
/// Base Physical Address of the BSC1 registers
#define BCM2835_BSC1_BASE				(BCM2835_PERI_BASE + 0x804000)
/// Base Physical Address of the AUX registers
#define BCM2835_AUX_BASE				(BCM2835_PERI_BASE + 0x215000)
/// Base Physical Address of the mailbox and framebuffer registers
#define BCM2835_MAIL0_BASE				(BCM2835_PERI_BASE + 0xB880)

#define BCM2835_BSC_C 							0x0000 ///< BSC Master Control
#define BCM2835_BSC_S 							0x0004 ///< BSC Master Status
#define BCM2835_BSC_DLEN						0x0008 ///< BSC Master Data Length
#define BCM2835_BSC_A 							0x000c ///< BSC Master Slave Address
#define BCM2835_BSC_FIFO						0x0010 ///< BSC Master Data FIFO
#define BCM2835_BSC_DIV							0x0014 ///< BSC Master Clock Divider
#define BCM2835_BSC_DEL							0x0018 ///< BSC Master Data Delay
#define BCM2835_BSC_CLKT						0x001c ///< BSC Master Clock Stretch Timeout

// Register masks for BSC_C
#define BCM2835_BSC_C_I2CEN 					0x00008000 ///< I2C Enable, 0 = disabled, 1 = enabled
#define BCM2835_BSC_C_INTR 						0x00000400 ///< Interrupt on RX
#define BCM2835_BSC_C_INTT 						0x00000200 ///< Interrupt on TX
#define BCM2835_BSC_C_INTD 						0x00000100 ///< Interrupt on DONE
#define BCM2835_BSC_C_ST 						0x00000080 ///< Start transfer, 1 = Start a new transfer
#define BCM2835_BSC_C_CLEAR_1 					0x00000020 ///< Clear FIFO Clear
#define BCM2835_BSC_C_CLEAR_2 					0x00000010 ///< Clear FIFO Clear
#define BCM2835_BSC_C_READ 						0x00000001 ///<	Read transfer

// Register masks for BSC_S
#define BCM2835_BSC_S_CLKT 						0x00000200 ///< Clock stretch timeout
#define BCM2835_BSC_S_ERR 						0x00000100 ///< ACK error
#define BCM2835_BSC_S_RXF 						0x00000080 ///< RXF FIFO full, 0 = FIFO is not full, 1 = FIFO is full
#define BCM2835_BSC_S_TXE 						0x00000040 ///< TXE FIFO full, 0 = FIFO is not full, 1 = FIFO is full
#define BCM2835_BSC_S_RXD 						0x00000020 ///< RXD FIFO contains data
#define BCM2835_BSC_S_TXD 						0x00000010 ///< TXD FIFO can accept data
#define BCM2835_BSC_S_RXR 						0x00000008 ///< RXR FIFO needs reading (full)
#define BCM2835_BSC_S_TXW 						0x00000004 ///< TXW FIFO needs writing (full)
#define BCM2835_BSC_S_DONE 						0x00000002 ///< Transfer DONE
#define BCM2835_BSC_S_TA 						0x00000001 ///< Transfer Active
#define BCM2835_BSC_FIFO_SIZE   				16 ///< BSC FIFO size

// Pointers to the hardware register bases
volatile uint32_t *bcm2835_gpio = (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_pwm  = (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_clk  = (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_pads = (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_spi0 = (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_bsc0 = (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_bsc1 = (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_st	= (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_aux	= (volatile uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_mail	= (volatile uint32_t *)MAP_FAILED;

typedef enum
{
	BCM2835_GPIO_FSEL_INPT  = 0b000,   ///< Input
	BCM2835_GPIO_FSEL_OUTP  = 0b001,   ///< Output
	BCM2835_GPIO_FSEL_ALT0  = 0b100,   ///< Alternate function 0
	BCM2835_GPIO_FSEL_ALT1  = 0b101,   ///< Alternate function 1
	BCM2835_GPIO_FSEL_ALT2  = 0b110,   ///< Alternate function 2
	BCM2835_GPIO_FSEL_ALT3  = 0b111,   ///< Alternate function 3
	BCM2835_GPIO_FSEL_ALT4  = 0b011,   ///< Alternate function 4
	BCM2835_GPIO_FSEL_ALT5  = 0b010,   ///< Alternate function 5
	BCM2835_GPIO_FSEL_MASK  = 0b111    ///< Function select bits mask
} bcm2835FunctionSelect;

typedef enum
{
	BCM2835_I2C_CLOCK_DIVIDER_2500   = 2500,      ///< 2500 = 10us = 100 kHz
	BCM2835_I2C_CLOCK_DIVIDER_626    = 626,       ///< 622 = 2.504us = 399.3610 kHz
	BCM2835_I2C_CLOCK_DIVIDER_150    = 150,       ///< 150 = 60ns = 1.666 MHz (default at reset)
	BCM2835_I2C_CLOCK_DIVIDER_148    = 148,       ///< 148 = 59ns = 1.689 MHz
} bcm2835I2CClockDivider;

typedef enum
{
	BCM2835_I2C_REASON_OK   	     = 0x00,      ///< Success
	BCM2835_I2C_REASON_ERROR_NACK    = 0x01,      ///< Received a NACK
	BCM2835_I2C_REASON_ERROR_CLKT    = 0x02,      ///< Received Clock Stretch Timeout
	BCM2835_I2C_REASON_ERROR_DATA    = 0x04,      ///< Not all data is sent / received
} bcm2835I2CReasonCodes;

typedef enum
{
	RPI_GPIO_P1_03        =  0,  ///< Version 1, Pin P1-03
	RPI_GPIO_P1_05        =  1,  ///< Version 1, Pin P1-05
	RPI_GPIO_P1_07        =  4,  ///< Version 1, Pin P1-07
	RPI_GPIO_P1_08        = 14,  ///< Version 1, Pin P1-08, defaults to alt function 0 UART0_TXD
	RPI_GPIO_P1_10        = 15,  ///< Version 1, Pin P1-10, defaults to alt function 0 UART0_RXD
	RPI_GPIO_P1_11        = 17,  ///< Version 1, Pin P1-11
	RPI_GPIO_P1_12        = 18,  ///< Version 1, Pin P1-12, can be PWM channel 0 in ALT FUN 5
	RPI_GPIO_P1_13        = 21,  ///< Version 1, Pin P1-13
	RPI_GPIO_P1_15        = 22,  ///< Version 1, Pin P1-15
	RPI_GPIO_P1_16        = 23,  ///< Version 1, Pin P1-16
	RPI_GPIO_P1_18        = 24,  ///< Version 1, Pin P1-18
	RPI_GPIO_P1_19        = 10,  ///< Version 1, Pin P1-19, MOSI when SPI0 in use
	RPI_GPIO_P1_21        =  9,  ///< Version 1, Pin P1-21, MISO when SPI0 in use
	RPI_GPIO_P1_22        = 25,  ///< Version 1, Pin P1-22
	RPI_GPIO_P1_23        = 11,  ///< Version 1, Pin P1-23, CLK when SPI0 in use
	RPI_GPIO_P1_24        =  8,  ///< Version 1, Pin P1-24, CE0 when SPI0 in use
	RPI_GPIO_P1_26        =  7,  ///< Version 1, Pin P1-26, CE1 when SPI0 in use

	// RPi Version 2
	RPI_V2_GPIO_P1_03     =  2,  ///< Version 2, Pin P1-03
	RPI_V2_GPIO_P1_05     =  3,  ///< Version 2, Pin P1-05
	RPI_V2_GPIO_P1_07     =  4,  ///< Version 2, Pin P1-07
	RPI_V2_GPIO_P1_08     = 14,  ///< Version 2, Pin P1-08, defaults to alt function 0 UART0_TXD
	RPI_V2_GPIO_P1_10     = 15,  ///< Version 2, Pin P1-10, defaults to alt function 0 UART0_RXD
	RPI_V2_GPIO_P1_11     = 17,  ///< Version 2, Pin P1-11
	RPI_V2_GPIO_P1_12     = 18,  ///< Version 2, Pin P1-12, can be PWM channel 0 in ALT FUN 5
	RPI_V2_GPIO_P1_13     = 27,  ///< Version 2, Pin P1-13
	RPI_V2_GPIO_P1_15     = 22,  ///< Version 2, Pin P1-15
	RPI_V2_GPIO_P1_16     = 23,  ///< Version 2, Pin P1-16
	RPI_V2_GPIO_P1_18     = 24,  ///< Version 2, Pin P1-18
	RPI_V2_GPIO_P1_19     = 10,  ///< Version 2, Pin P1-19, MOSI when SPI0 in use
	RPI_V2_GPIO_P1_21     =  9,  ///< Version 2, Pin P1-21, MISO when SPI0 in use
	RPI_V2_GPIO_P1_22     = 25,  ///< Version 2, Pin P1-22
	RPI_V2_GPIO_P1_23     = 11,  ///< Version 2, Pin P1-23, CLK when SPI0 in use
	RPI_V2_GPIO_P1_24     =  8,  ///< Version 2, Pin P1-24, CE0 when SPI0 in use
	RPI_V2_GPIO_P1_26     =  7,  ///< Version 2, Pin P1-26, CE1 when SPI0 in use

	// RPi Version 2, new plug P5
	RPI_V2_GPIO_P5_03     = 28,  ///< Version 2, Pin P5-03
	RPI_V2_GPIO_P5_04     = 29,  ///< Version 2, Pin P5-04
	RPI_V2_GPIO_P5_05     = 30,  ///< Version 2, Pin P5-05
	RPI_V2_GPIO_P5_06     = 31,  ///< Version 2, Pin P5-06

} RPiGPIOPin;

static int i2c_byte_wait_us = 0;

uint32_t bcm2835_peri_read(volatile uint32_t* paddr)
{
	// Make sure we dont return the _last_ read which might get lost
	// if subsequent code changes to a different peripheral
	uint32_t ret = *paddr;
	*paddr; // Read without assigneing to an unused variable
	return ret;
}

// read from peripheral without the read barrier
uint32_t bcm2835_peri_read_nb(volatile uint32_t* paddr)
{
	return *paddr;
}

void bcm2835_peri_write(volatile uint32_t* paddr, uint32_t value)
{
	// Make sure we don't rely on the first write, which may get
	// lost if the previous access was to a different peripheral.
	*paddr = value;
	*paddr = value;
}

void bcm2835_peri_write_nb(volatile uint32_t* paddr, uint32_t value)
{
	*paddr = value;
}

void bcm2835_peri_set_bits(volatile uint32_t* paddr, uint32_t value, uint32_t mask)
{
	uint32_t v = bcm2835_peri_read(paddr);
	v = (v & ~mask) | (value & mask);
	bcm2835_peri_write(paddr, v);
}

void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode)
{
	// Function selects are 10 pins per 32 bit word, 3 bits per pin
	volatile uint32_t* paddr = bcm2835_gpio + BCM2835_GPFSEL0/4 + (pin/10);
	uint8_t   shift = (pin % 10) * 3;
	uint32_t  mask = BCM2835_GPIO_FSEL_MASK << shift;
	uint32_t  value = mode << shift;
	bcm2835_peri_set_bits(paddr, value, mask);
}

void bcm2835_i2c_begin(void)
{

	volatile uint32_t* paddr = bcm2835_bsc1 + BCM2835_BSC_DIV/4;
	// Set the I2C/BSC1 pins to the Alt 0 function to enable I2C access on them
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_03, BCM2835_GPIO_FSEL_ALT0); // SDA
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_05, BCM2835_GPIO_FSEL_ALT0); // SCL
	// Read the clock divider register
	uint16_t cdiv = bcm2835_peri_read(paddr);
	// Calculate time for transmitting one byte
	// 1000000 = micros seconds in a second
	// 9 = Clocks per byte : 8 bits + ACK
	i2c_byte_wait_us = ((float)cdiv / BCM2835_CORE_CLK_HZ) * 1000000 * 9;
}

void bcm2835_i2c_setSlaveAddress(uint8_t addr)
{
	// Set I2C Device Address
	volatile uint32_t* paddr = bcm2835_bsc1 + BCM2835_BSC_A/4;
	bcm2835_peri_write(paddr, addr);
}


// Writes an number of bytes to I2C
uint8_t bcm2835_i2c_write(const char * buf, uint32_t len)
{
	volatile uint32_t* dlen    = bcm2835_bsc1 + BCM2835_BSC_DLEN/4;
	volatile uint32_t* fifo    = bcm2835_bsc1 + BCM2835_BSC_FIFO/4;
	volatile uint32_t* status  = bcm2835_bsc1 + BCM2835_BSC_S/4;
	volatile uint32_t* control = bcm2835_bsc1 + BCM2835_BSC_C/4;

	uint32_t remaining = len;
	uint32_t i = 0;
	uint8_t reason = BCM2835_I2C_REASON_OK;

	// Clear FIFO
	bcm2835_peri_set_bits(control, BCM2835_BSC_C_CLEAR_1 , BCM2835_BSC_C_CLEAR_1 );
	// Clear Status
	bcm2835_peri_write_nb(status, BCM2835_BSC_S_CLKT | BCM2835_BSC_S_ERR | BCM2835_BSC_S_DONE);
	// Set Data Length
	bcm2835_peri_write_nb(dlen, len);
	// pre populate FIFO with max buffer
	while( remaining && ( i < BCM2835_BSC_FIFO_SIZE ) )
	{
		bcm2835_peri_write_nb(fifo, buf[i]);
		i++;
		remaining--;
	}

	// Enable device and start transfer
	bcm2835_peri_write_nb(control, BCM2835_BSC_C_I2CEN | BCM2835_BSC_C_ST);

	// Transfer is over when BCM2835_BSC_S_DONE
	while(!(bcm2835_peri_read_nb(status) & BCM2835_BSC_S_DONE ))
	{
		while ( remaining && (bcm2835_peri_read_nb(status) & BCM2835_BSC_S_TXD ))
		{
			// Write to FIFO, no barrier
			bcm2835_peri_write_nb(fifo, buf[i]);
			i++;
			remaining--;
		}
	}

	// Received a NACK
	if (bcm2835_peri_read(status) & BCM2835_BSC_S_ERR)
	{
		reason = BCM2835_I2C_REASON_ERROR_NACK;
	}

	// Received Clock Stretch Timeout
	else if (bcm2835_peri_read(status) & BCM2835_BSC_S_CLKT)
	{
		reason = BCM2835_I2C_REASON_ERROR_CLKT;
	}

	// Not all data is sent
	else if (remaining)
	{
		reason = BCM2835_I2C_REASON_ERROR_DATA;
	}

	bcm2835_peri_set_bits(control, BCM2835_BSC_S_DONE , BCM2835_BSC_S_DONE);
	puts(itoa(reason));
	return reason;
	
}

uint8_t bcm2835_i2c_read(char* buf, uint32_t len)
{

	volatile uint32_t* dlen    = bcm2835_bsc1 + BCM2835_BSC_DLEN/4;
	volatile uint32_t* fifo    = bcm2835_bsc1 + BCM2835_BSC_FIFO/4;
	volatile uint32_t* status  = bcm2835_bsc1 + BCM2835_BSC_S/4;
	volatile uint32_t* control = bcm2835_bsc1 + BCM2835_BSC_C/4; 

	uint32_t remaining = len;
	uint32_t i = 0;
	uint8_t reason = BCM2835_I2C_REASON_OK;

	// Clear FIFO
	bcm2835_peri_set_bits(control, BCM2835_BSC_C_CLEAR_1 , BCM2835_BSC_C_CLEAR_1 );
	// Clear Status
	bcm2835_peri_write_nb(status, BCM2835_BSC_S_CLKT | BCM2835_BSC_S_ERR | BCM2835_BSC_S_DONE);
	// Set Data Length
	bcm2835_peri_write_nb(dlen, len);
	// Start read
	bcm2835_peri_write_nb(control, BCM2835_BSC_C_I2CEN | BCM2835_BSC_C_ST | BCM2835_BSC_C_READ);

	// wait for transfer to complete
	while (!(bcm2835_peri_read_nb(status) & BCM2835_BSC_S_DONE))
	{
		// we must empty the FIFO as it is populated and not use any delay
		while (bcm2835_peri_read_nb(status) & BCM2835_BSC_S_RXD)
		{
			// Read from FIFO, no barrier
			buf[i] = bcm2835_peri_read_nb(fifo);
			i++;
			remaining--;
		}
	}

	// transfer has finished - grab any remaining stuff in FIFO
	while (remaining && (bcm2835_peri_read_nb(status) & BCM2835_BSC_S_RXD))
	{
		// Read from FIFO, no barrier
		buf[i] = bcm2835_peri_read_nb(fifo);
		i++;
		remaining--;
	}

	// Received a NACK
	if (bcm2835_peri_read(status) & BCM2835_BSC_S_ERR)
	{
		reason = BCM2835_I2C_REASON_ERROR_NACK;
	}

	// Received Clock Stretch Timeout
	else if (bcm2835_peri_read(status) & BCM2835_BSC_S_CLKT)
	{
		reason = BCM2835_I2C_REASON_ERROR_CLKT;
	}

	// Not all data is received
	else if (remaining)
	{
		reason = BCM2835_I2C_REASON_ERROR_DATA;
	}

	bcm2835_peri_set_bits(control, BCM2835_BSC_S_DONE , BCM2835_BSC_S_DONE);

	return reason;
}

int bcm2835_init(void)
{
	bcm2835_pads = (uint32_t*)BCM2835_GPIO_PADS;
	bcm2835_clk  = (uint32_t*)BCM2835_CLOCK_BASE;
	bcm2835_gpio = (uint32_t*)BCM2835_GPIO_BASE;
	bcm2835_pwm  = (uint32_t*)BCM2835_GPIO_PWM;
	bcm2835_spi0 = (uint32_t*)BCM2835_SPI0_BASE;
	bcm2835_bsc0 = (uint32_t*)BCM2835_BSC0_BASE;
	bcm2835_bsc1 = (uint32_t*)BCM2835_BSC1_BASE;
	bcm2835_st   = (uint32_t*)BCM2835_ST_BASE;
	bcm2835_aux  = (uint32_t*)BCM2835_AUX_BASE;
	bcm2835_mail = (uint32_t*)BCM2835_MAIL0_BASE;
	return 1; // Success
}

void bcm2835_i2c_setClockDivider(uint16_t divider)
{
	volatile uint32_t* paddr = bcm2835_bsc1 + BCM2835_BSC_DIV/4;
	bcm2835_peri_write(paddr, divider);
	// Calculate time for transmitting one byte
	// 1000000 = micros seconds in a second
	// 9 = Clocks per byte : 8 bits + ACK
	i2c_byte_wait_us = ((float)divider / BCM2835_CORE_CLK_HZ) * 1000000 * 9;
}