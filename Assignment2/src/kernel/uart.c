#include "uart.h"

void mmio_write(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t*)reg = data;
}

uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
}

uart_flags_t read_flags(void)
{
    uart_flags_t flags;
    flags.as_int = mmio_read(UART0_FR);
    return flags;
}

unsigned char uart_getc(void)
{
    uart_flags_t flags;
    do
    {
        flags = read_flags();
    } while (flags.receive_queue_empty);
    // Check if the transmit FIFO is full
    return mmio_read(UART0_DR);
}

void uart_putc(unsigned char c)
{
    uart_flags_t flags;
    do
    {
        flags = read_flags();
    } while (flags.transmit_queue_full);
    // Check if the receive FIFO is empty
    mmio_write(UART0_DR, c);
}

void uart_init(void)
{
    uart_control_t control;
    bzero(&control, 4);
    mmio_write(UART0_CR, control.as_int);
    //Disable UART
    // Enable Pin 14 and 15
    mmio_write(GPPUD, 0x00000000);
    // This provides the required set-up time for the control signal
    delay(150);
    // Enable clock for pull-ups/ pull-downs on Pin 14 and 15
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    // This provides the required set-up time for the control signal
    delay(150);
    // Flush the GPIO setup
    mmio_write(GPPUDCLK0, 0x00000000);
    // Clear all UART0 interrupts
    mmio_write(UART0_ICR, 0x7FF);
    // Set 8 bit word length
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
    // Disable all interrupts from the UART by writing a one to the relevent bits of the Interrupt Mask Set Clear register.
    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
                           (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
    // Enable Tx, Rx and FIFO
    control.uart_enabled = 1;
    control.transmit_enabled = 1;
    control.receive_enabled = 1;
    mmio_write(UART0_CR, control.as_int);
}
