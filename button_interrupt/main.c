/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRA = 0x01;
    DDRC = 0xff;
    DDRF = 0x0f;

    PORTA = 0x01;
    PORTC = 0x77;
    PORTF = 0x01;

    while(1)
        ;
}
