/*
 */
#define F_CPU               16000000UL

#include <avr/io.h>
#include <string.h>
#include "uart.h"
#include "25lc010.h"

int main(void)
{
    uint8_t i;

    spi_init();
    uart_init();

    for (i = 0; i < 128; i++)
    {
        eeprom_write_byte(i, i);
    }

    for (i = 0; i < 128; i++)
    {
        uart_print_8bit_num(eeprom_read_byte(i));
        uart_transmit('\n');
    }

    while(1)
    {
        ;
    }

    return 0;
}
