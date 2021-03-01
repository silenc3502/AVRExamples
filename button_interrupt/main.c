/*
 */

#include <avr/io.h>

#define F_CPU       16000000L
#include <util/delay.h>
#include <avr/interrupt.h>

#include <util/atomic.h>
#include <stdbool.h>

#define Use_IE0_Interrupt   (EIMSK |= (1 << INT0))
#define IE0_Detect_Falling  (EICRA = (1 << ISC01))
#define IE0_Detect_Rising   (EICRA = (1 << ISC01) | (1 << ISC00))

#define USART_BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode 선택

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity 비트 선택

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop 비트 선택

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART 데이터 비트 선택

volatile bool update = false;

ISR(INT0_vect)
{
    if (PINB & _BV(PB0))
        update = true;

    //_delay_ms(500);
}

int main(void)
{
    DDRB = 0x20;
    PORTB = 0x00;

    PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT0);

    sei();

	while (1)
	{
		ATOMIC_BLOCK(ATOMIC_FORCEON) {

			// If the ISR has indicated we need to update the state
			// then run this block.
			if (update) {

				// Toggle the pins on PORTB on/off.
				PORTB ^= 0x20;

				/*
				 * We reset the update flag to false to indicate that
				 * we are done.  This ensures that this block will not
				 * be executed until update is set to true again, which
				 * is only done by the interrupt service routine.
				 */
				update = false;
			}

		}
	}

    return 0;
}
