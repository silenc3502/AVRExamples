/*
 */
#define F_CPU               16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
    unsigned char data;

    uart_init();

    while(1)
    {
        data = uart_receive();
        uart_transmit(data);
    }

    return 0;
}
