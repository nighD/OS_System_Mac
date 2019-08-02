#include <stdint.h>
#include "uart.h"
#define MMIO_BASE	0x3F000000
#define BSC0_BASE	((volatile unsigned int*)(MMIO_BASE + 0x804000)) //I2C Controller
// #define BSC0_BASE ((volatile unsigned int*)(MMIO_BASE + 0x205000)) //I2C Controller
#define BSC0_C 	((volatile unsigned int*)(BSC0_BASE + 0x0)) // Control
#define BSC0_S 	((volatile unsigned int*)(BSC0_BASE + 0x4)) // Status
#define BSC0_DLEN 	((volatile unsigned int*)(BSC0_BASE + 0x8)) // Data Length
#define BSC0_A 	((volatile unsigned int*)(BSC0_BASE + 0xc)) // Slave Address
#define BSC0_FIFO 	((volatile unsigned int*)(BSC0_BASE + 0x10)) //Data FIFO
#define BSC0_DIV 	((volatile unsigned int*)(BSC0_BASE + 0x14)) // Clock Divider
#define BSC0_DEL 	((volatile unsigned int*)(BSC0_BASE + 0x18)) //Data Delay
#define BSC0_CLKT 	((volatile unsigned int*)(BSC0_BASE + 0x1c)) //Clock Stretch Timeout

#define BCM2835_ST_CS 							0x0000 ///< System Timer Control/Status
#define BCM2835_ST_CLO 							0x0004 ///< System Timer Counter Lower 32 bits
#define BCM2835_ST_CHI 							0x0008 ///< System Timer Counter Upper 32 bits

#define BSC_C_I2CEN     (1 << 15) // I2C Enable
#define BSC_C_INTR      (1 << 10) // Interrupt on RX
#define BSC_C_INTT      (1 << 9) // Interrupt on TX
#define BSC_C_INTD      (1 << 8) // Interrupt on Done
#define BSC_C_ST        (1 << 7) //Start Transfer
#define BSC_C_CLEAR     (1 << 4) // FIFO Clear
#define BSC_C_READ      1 // Read Transfer
#define DS1307_ADDR		0x68

#define START_READ      BSC_C_I2CEN|BSC_C_ST|BSC_C_CLEAR|BSC_C_READ
#define START_WRITE     BSC_C_I2CEN|BSC_C_ST

#define BSC_S_CLKT		      (1 << 9)
#define BSC_S_ERR       (1 << 8)
#define BSC_S_RXF       (1 << 7)
#define BSC_S_TXE       (1 << 6)
#define BSC_S_RXD       (1 << 5)
#define BSC_S_TXD       (1 << 4)
#define BSC_S_RXR       (1 << 3)
#define BSC_S_TXW       (1 << 2)
#define BSC_S_DONE       (1 << 1)
#define BSC_S_TA       (1 << 0)

#define CLEAR_STATUS BSC_S_CLKT|BSC_S_ERR|BSC_S_DONE

// I2C Function Prototypes
void i2c_init();
void wait_i2c_done();
void bzero(void *dest, int bytes);
unsigned int bcd_to_decimal(unsigned int bcd);
unsigned int decimal_to_bcd(unsigned int d);
void writingI2C(unsigned int* writingBuffer,unsigned int DATA_LENGTH,unsigned int ADDR);
void readingI2C(unsigned int *readingBuffer,unsigned int DATA_LENGTH, unsigned int ADDR);
int bcm2835_init(void);
uint32_t bcm2835_peri_read(volatile uint32_t* paddr);
uint32_t bcm2835_peri_read_nb(volatile uint32_t* paddr);
uint8_t bcm2835_i2c_read(char* buf, uint32_t len);
uint8_t bcm2835_i2c_write(const char * buf, uint32_t len);
void bcm2835_i2c_setSlaveAddress(uint8_t addr);
void bcm2835_i2c_begin(void);
void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode);
void bcm2835_peri_set_bits(volatile uint32_t* paddr, uint32_t value, uint32_t mask);
void bcm2835_peri_write_nb(volatile uint32_t* paddr, uint32_t value);
void bcm2835_peri_write(volatile uint32_t* paddr, uint32_t value);

void bcm2835_i2c_setClockDivider(uint16_t divider);
void bcm2835_delay(unsigned int millis);
// microseconds
void bcm2835_delayMicroseconds(uint64_t micros);

uint64_t bcm2835_st_read(void);
void bcm2835_st_delay(uint64_t offset_micros, uint64_t micros);