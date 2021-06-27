#define F_CPU     16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"

void adc_init (unsigned char channel)
{
  // AVCC를 기준 전압으로 선택
  ADMUX |= 0x40;
  
  // 분주비 설정
  ADCSRA |= 0x07;
  // ADC 활성화
  ADCSRA |= (1 << ADEN);
  // 자동 트리거 모드
  ADCSRA |= (1 << ADATE);
  
  // 채널 선택
  ADMUX |= ((ADMUX & 0xE0) | channel);
  // 변환 시작
  ADCSRA |= (1 << ADSC);
}

int read_adc (void)
{
  while (!(ADCSRA & (1 << ADIF)))
  {
    ;
  }
  
  return ADC;
}

void int_to_string (int n, char *buffer)
{
  sprintf(buffer, "%04d", n);
  buffer[4] = '\0';
}

int main (void)
{
  int read;
  char buffer[5];
  
  uart_init();
  adc_init(0);
  
  while (1)
  {
    read = read_adc();
    int_to_string(read, buffer);
    uart_print_string(buffer);
    uart_print_string("\n");
    
    _delay_ms(1000);
  }
}
