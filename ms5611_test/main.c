/*
 * TWI_MS5611.c
 *
 * Created: 2020-05-09 오후 4:13:36
 * Author : user
 */

#define F_CPU 16000000UL
//#define F_CPU 8000000UL

#include "uart.h"
#include "twi.h"
#include "ms5611.h"

int main(void)
{
	FILE* fpStdio = fdevopen(usart_tx_char, NULL); // for printf
	int i;
	unsigned long D1;
	unsigned long D2;
	unsigned int C[8];

	uart_init();
	uart_string_transmit("uart init ok\n");

	i2c_init();
	uart_string_transmit("i2c init ok\n");

	ms5611_init();
	uart_string_transmit("ms5611 init ok\n");
	_delay_ms(1000);

    while (1)
    {
		ms5611_measure();
		printf("press : %u\n" , ms5611_getPress());
		printf("temp : %d\n" , ms5611_getTemp());
		printf("alt : %f\n" , ms5611_getAltitude());
		_delay_ms(1000);
    }
}
