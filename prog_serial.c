#include "prog_serial.h"

#define CD '\n'

uint8_t bb( void )
{
  uint8_t b1,b2;
  
  while( serial_rx_ready() == 0 );
  b1 = serial_read() & 0x0F;
  serial_write( CD );
  
  while( serial_rx_ready() == 0 );
  b2 = serial_read() & 0x0F;
  serial_write( CD );

  return (uint8_t)( b1<<4 | b2 );
}

void _one_element( uint8_t i, uint8_t num )
{
    lcd_gotoxy( 0, 1 );
	lcd_print_int( i + 1, 3 );
	lcd_print_string(" of ");
	lcd_print_int( num, 3 );

    set_eeprom_next_byte( bb() );
    set_eeprom_next_byte( bb() ); // Get Time of current prog

    set_eeprom_next_byte( bb() );
    set_eeprom_next_byte( bb() );
    set_eeprom_next_byte( bb() );
    set_eeprom_next_byte( bb() ); // Get Freq of current prog
}

void read_program_from_serial()
{
  uint8_t i, num;

  serial_init();

  lcd_clear();
  
  serial_write(CD); // ask server n progs
  _delay_ms( 500 );

  if( serial_rx_ready() == 0 ) return;
  
  num = bb(); // Get N prog elements
  if( num == 0 || num > 250 ) { set_eeprom_next_byte( 0 ); return; }

  lcd_print_string("Get programm:");
 
  set_eeprom_next_byte( num ); // N progs
  set_eeprom_next_byte( bb() ); // Get N repeates
  
  for( i = 0; i < num; i++ ) _one_element( i, num );

  do { set_eeprom_next_byte( num = bb() ); } while( num );
  
  lcd_gotoxy( 0, 0 );
  lcd_print_string("Ok get programm!");
  _delay_ms( 3000 );
}
