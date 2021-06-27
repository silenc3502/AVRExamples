#include "25lc010.h"

void spi_init (void)
{
    // SS핀을 출력으로 설정
    DDRB |= (1 << SPI_SS);
    // SS핀은 HIGH로 설정하여 EEPROM이 선택되지 않은 상태로 시작
    PORTB |= (1 << SPI_SS);
    // MOSI핀 출력 설정
    DDRB |= (1 << SPI_MOSI);
    // MISO핀 입력 설정
    DDRB &= ~(1 << SPI_MISO);
    // SCK핀 출력 설정
    DDRB |= (1 << SPI_SCK);
    // 마스터 모드
    SPCR |= (1 << MSTR);
    // SPI 활성화
    SPCR |= (1 << SPE);
}

void eeprom_change_byte(uint8_t byte)
{
    // 데이터 전송 시작
    SPDR = byte;
    // 전송 완료 대기
    loop_until_bit_is_set(SPSR, SPIF);
}

void eeprom_send_address (uint8_t address)
{
    eeprom_change_byte(address);
}

uint8_t eeprom_read_byte (uint8_t address)
{
    // EEPROM 선택
    EEPROM_SELECT();
    // 읽기 명령어 전송
    eeprom_change_byte(EEPROM_READ);
    // 메모리 주소 전송
    eeprom_send_address(address);
    // 마스터에서 바이트 값을 전송하여야 슬레이브로부터 바이트 값을 받을 수 있고
    // 전송하는 값은 의미가 없으므로 0을 전송한다.
    eeprom_change_byte(0);
    // EEPROM 선택 해제
    EEPROM_DESELECT();

    return SPDR;
}

void eeprom_write_enable (void)
{
    // Slave Select를 LOW
    EEPROM_SELECT();
    // 쓰기 가능하도록 설정
    eeprom_change_byte(EEPROM_WREN);
    // Slave Select를 HIGH
    EEPROM_DESELECT();
}

void eeprom_write_byte (uint8_t address, uint8_t data)
{
    // 쓰기 가능 모드로 설정
    eeprom_write_enable();
    // EEPROM 선택
    EEPROM_SELECT();
    // 쓰기 명령 전송
    eeprom_change_byte(EEPROM_WRITE);
    // 주소 전송
    eeprom_send_address(address);
    // 데이터 전송
    eeprom_change_byte(data);
    // EEPROM 선택 해제
    EEPROM_DESELECT();

    // 쓰기가 완료될 때까지 대기
    while (eeprom_read_status() & _BV(EEPROM_WRITE_IN_PROGRESS))
    {
        ;
    }
}

uint8_t eeprom_read_status (void)
{
    // EEPROM 선택
    EEPROM_SELECT();
    // 상태 레지스터 읽기 명령 전송
    eeprom_change_byte(EEPROM_RDSR);
    // 상태 레지스터 값 읽기
    eeprom_change_byte(0);
    // EEPROM 선택 해제
    EEPROM_DESELECT();

    return SPDR;
}

void eeprom_erase_all (void)
{
    uint8_t i;
    uint16_t page_address = 0;

    while (page_address < EEPROM_TOTAL_BYTE)
    {
        // 쓰기 가능 모드 설정
        eeprom_write_enable();
        // EEPROM 선택
        EEPROM_SELECT();
        // 쓰기 명령 전송
        eeprom_change_byte(EEPROM_WRITE);
        // 페이지 시작 주소 전송
        eeprom_send_address(page_address);
        // 페이지 단위 데이터 전송
        for (i = 0; i < EEPROM_PAGE_SIZE; i++)
        {
            eeprom_change_byte(0);
        }
        // EEPROM 선택 해제
        EEPROM_DESELECT();
        // 페이지 변경
        page_address += EEPROM_PAGE_SIZE;
        // 쓰기 완료 대기
        while (eeprom_read_status() & _BV(EEPROM_WRITE_IN_PROGRESS))
        {
            ;
        }
    }
}
