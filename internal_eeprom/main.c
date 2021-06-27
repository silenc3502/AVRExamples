/*
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include "uart.h"

int main(void)
{
    // eeprom에 쓸 데이터
    uint8_t data_byte = 1;
    uint16_t data_word = 2;
    uint32_t data_dword = 3;
    char data_string[] = "ABCDE";

    // eeprom 주소
    int address_byte = 0;
    int address_word = 10;
    int address_dword = 20;
    int address_string = 30;

    uart_init();

    // 데이터 쓰기
    eeprom_update_byte((uint8_t *)address_byte, data_byte * 10);
    eeprom_update_word((uint16_t *)address_word, data_word * 10);
    eeprom_update_dword((uint32_t *)address_dword, data_dword * 10);
    eeprom_update_block((void *)data_string, (void *)address_string, 5);

    // 데이터 일기
    data_byte = eeprom_read_byte((uint8_t *)address_byte);
    data_word = eeprom_read_word((uint16_t *)address_word);
    data_dword = eeprom_read_dword((uint32_t *)address_dword);
    eeprom_read_block((void *)data_string, (void *)address_string, 5);

    uart_string_transmit("byte: ");
    uart_print_8bit_num(data_byte);
    uart_string_transmit("\n");

    uart_string_transmit("word: ");
    uart_print_16bit_num(data_word);
    uart_string_transmit("\n");

    uart_string_transmit("dword: ");
    uart_print_32bit_num(data_dword);
    uart_string_transmit("\n");

    uart_string_transmit("string: ");
    uart_string_transmit(data_string);
    uart_string_transmit("\n");

    while(1)
    ;

    return 0;
}
