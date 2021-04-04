/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU       16000000L
#include <util/delay.h>

int main(void)
{
    DDRB &= ~(1 << DDB5);     // Clear the PB0 pin
    // PB0 (PCINT0 pin) is now an input

    PORTB |= (1 << PORTB4);    // turn On the Pull-up
    // PB0 is now an input with pull-up enabled

    PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT5);  // set PCINT0 to trigger an interrupt on state change

    sei();                    // turn on interrupts

    while(1)
        ;
}

ISR (PCINT0_vect)
{
    PORTB ^= 0x10;

    //_delay_ms(100);
}
