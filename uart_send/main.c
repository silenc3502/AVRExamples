/*
 */

#define F_CPU 16000000UL

#include <avr/io.h>      // 모든 I/O 레지스터 매크로가 포함됨
#include <util/delay.h>

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

void USART_Init()
{
	// Baud Rate 설정
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;

	// 프레임 포맷 결정
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;

	// 송수신 허용
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

void USART_TransmitPolling(uint8_t DataByte)
{
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // UDR 준비 전까지 진행하지 않음
	UDR0 = DataByte;
}

int main()
{
	USART_Init();
	while (1)
	{
		USART_TransmitPolling('A');
		USART_TransmitPolling('R');
		USART_TransmitPolling('N');
		USART_TransmitPolling('A');
		USART_TransmitPolling('B');
		USART_TransmitPolling('\r');
		USART_TransmitPolling('\n');
		USART_TransmitPolling('\0');
		_delay_ms(1000);
	}
	return 0;
}
