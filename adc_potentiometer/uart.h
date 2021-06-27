#ifndef __UART_H__
#define __UART_H__

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uart_init (void);
unsigned char uart_receive (void);
void uart_transmit (char data);
void uart_string_transmit (char *string);
void uart_print (char *name, long val);
int usart_tx_char (char ch, FILE *fp);

#endif
