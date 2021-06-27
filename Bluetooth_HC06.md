# HC06

## Putty Serial Configuration

```make
1. Buad Rate : 9600
2. AT 명령 전송 -> 응답 OK
3. AT+NAMEatmega328blue 전송 -> 모듈 이름 atmega328blue로 변경
4. AT+PIN1234 전송 -> 비밀 번호를 1234로 변경
5. AT+BAUD4 전송 -> 전송 속도 9600으로 변경
```

## Cell Phone Configuration

```make
1. 휴대폰 블루투스 활성화
2. atmega328blue 검색 확인
3. 페어링 시도 -> 비밀번호 입력
4. Bluetooth spp tools를 다운로드
5. atmega328blue 선택후 Connect
6. 통신 모드 - Byte Stream Mode 선택
7. 데이터를 보내서 결과를 확인한다.
```
