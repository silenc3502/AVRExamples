/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRB &= ~(1 << DDB0);     // Clear the PB0 pin
    // PB0 (PCINT0 pin) is now an input

    PORTB |= (1 << PORTB5);    // turn On the Pull-up
    // PB0 is now an input with pull-up enabled

    PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0);  // set PCINT0 to trigger an interrupt on state change

    sei();                    // turn on interrupts

    while(1)
    {
        /*main program loop here */
    }
}



ISR (PCINT0_vect)
{
    PORTB ^= 0x20;

    //_delay_ms(500);
}
