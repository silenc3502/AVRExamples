
#define F_CPU                   16000000UL
#include "uart.h"

#define sbi(PORTX, BITX)        (PORTX |= (1 << BITX))
#define cbi(PORTX, BITX)        (PORTX &= ~(1 << BITX))

#define UART_BUF                10

void uart_init (void)
{
    sbi(UCSR0A, U2X0);

    UBRR0H = 0x00;
    UBRR0L = 207;

    UCSR0C |= 0x06;

    sbi(UCSR0B, RXEN0);
    sbi(UCSR0B, TXEN0);
}

unsigned char uart_receive (void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
        ;
    }

    return UDR0;
}

void uart_transmit (char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
        ;
    }

    UDR0 = data;
}

void uart_string_transmit (char *string)
{
    while (*string != '\0')
    {
        uart_transmit(*string);
        string++;
    }
}

void uart_print (char *name, long val)
{
    char debug_buffer[UART_BUF] = {'\0'};

    uart_string_transmit(name);
    uart_string_transmit(" = ");

    itoa((val), debug_buffer, UART_BUF);
    uart_string_transmit(debug_buffer);
    uart_string_transmit("\n");
}

int usart_tx_char (char ch, FILE *fp)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
        ;
    }

    UDR0 = ch;

    return 0;
}

void uart_print_8bit_num (uint8_t no)
{
    char num_string[4] = "0";
    int i, index = 0;

    if (no > 0)
    {
        for (i = 0; no != 0; i++)
        {
            num_string[i] = no % 10 + '0';
            no = no / 10;
        }

        num_string[i] = '\0';
        index = i - 1;
    }

    for (i = index; i >= 0; i--)
    {
        uart_transmit(num_string[i]);
    }
}

void uart_print_16bit_num (uint16_t no)
{
    char num_string[6] = "0";
    int i, index = 0;

    if (no > 0)
    {
        for (i = 0; no != 0; i++)
        {
            num_string[i] = no % 10 + '0';
            no = no / 10;
        }

        num_string[i] = '\0';
        index = i - 1;
    }

    for (i = index; i >= 0; i--)
    {
        uart_transmit(num_string[i]);
    }
}

void uart_print_32bit_num (uint32_t no)
{
    char num_string[11] = "0";
    int i, index = 0;

    if (no > 0)
    {
        for (i = 0; no != 0; i++)
        {
            num_string[i] = no % 10 + '0';
            no = no / 10;
        }

        num_string[i] = '\0';
        index = i - 1;
    }

    for (i = index; i >= 0; i--)
    {
        uart_transmit(num_string[i]);
    }
}
