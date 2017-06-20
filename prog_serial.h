#ifndef prog_serial_h
#define prog_serial_h

#include <util/delay.h>
#include "serial_lib.h"
#include "lcd_lib.h"
#include "lcd_rus_lib.h"
#include "eeprom_prog.h"

#define CD '\n'

uint8_t bb( void );

void read_program_from_serial();

#endif
