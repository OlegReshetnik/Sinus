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

uint8_t  serial_rx_ready(); // число байт во входном буффере

uint8_t  serial_tx_ready(); // число байт в выходном буффере

uint8_t serial_read(); // читать очередной байт из входного буффера, если пусто то вернуть SERIAL_NO_DATA

void serial_clear_read(); // очистить входной буффер

void serial_write(uint8_t data); // записать байт в выходной буффер и включить прерывания

void serial_print_string( uint8_t * str );

#endif
