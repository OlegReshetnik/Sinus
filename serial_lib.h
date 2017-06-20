#ifndef serial_lib_h
#define serial_lib_h

#include <avr/io.h>
#include <avr/interrupt.h>

#define RX_BUFFER_SIZE 32
#define TX_BUFFER_SIZE 16
#define SERIAL_NO_DATA 0xff


#define BAUD 115200
#include <util/setbaud.h>

void serial_init();

uint8_t  serial_rx_ready(); // ����� ���� �� ������� �������

uint8_t  serial_tx_ready(); // ����� ���� � �������� �������

uint8_t serial_read(); // ������ ��������� ���� �� �������� �������, ���� ����� �� ������� SERIAL_NO_DATA

void serial_clear_read(); // �������� ������� ������

void serial_write(uint8_t data); // �������� ���� � �������� ������ � �������� ����������

void serial_print_string( uint8_t * str );

#endif
