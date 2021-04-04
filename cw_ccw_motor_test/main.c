#define F_CPU               16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRD = 0xFF; //PORTB as Output
  DDRB = 0xFF; //PORTB as Output

  while(1)
  {
    //Rotates Motor in Antilockwise
    PORTD = 0x01; //00000001
    PORTB = 0x00;
    //PORTB = 0x08;
    _delay_ms(1000);

    //Stops Motor
    PORTD = 0x00; //00000000
    PORTB = 0x00;
    _delay_ms(1000);

    //Rotates Motor in Clockwise
    PORTD = 0x00; //00000010
    PORTB = 0x08;
    _delay_ms(1000);

    //Stops Motor
    PORTC = 0x00; //00000011
    PORTB = 0x00;
    _delay_ms(1000);
  }
}
