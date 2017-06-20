#ifndef lcd_rus_lib_h
#define lcd_rus_lib_h

#include <avr/pgmspace.h>
#include <stdint.h>
#include "lcd_lib.h"



void lcd_rus_clear( void );  // для корректной работы вывода русских символов

void lcd_rus_write( uint8_t ch );

void lcd_rus_print_string( uint8_t * str );

#endif
