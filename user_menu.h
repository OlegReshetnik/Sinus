#ifndef user_menu_h
#define user_menu_h

#include <util/delay.h>
#include "progmem_prog.h"
#include "eeprom_prog.h"

#include "lcd_lib.h"
#include "lcd_rus_lib.h"


#define LONG_CLK 25
#define SHORT_CLK 3
#define DEL_CLK 50

void print_eeprom_prog( void );
void print_progmem_prog( uint8_t prog_number );
uint8_t get_user_choice( void );

#endif
