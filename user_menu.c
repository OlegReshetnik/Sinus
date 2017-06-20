#include "user_menu.h"

void print_info( uint8_t * nam, uint16_t tt )
{
  lcd_rus_clear();
  lcd_rus_print_string( nam );
  lcd_print_time( tt, 8, 1 );
  lcd_gotoxy( 1, 1 );
  lcd_rus_print_string( "Время" );
}

void print_ok( void )
{
	lcd_gotoxy( 1, 1 );
	lcd_rus_print_string("Ok   ");
	_delay_ms(500);
}

void print_eeprom_prog( void )
{
  uint8_t p_name[20];
  get_eeprom_prog_name( p_name );
  print_info( p_name, get_eeprom_prog_time() );
}

void print_progmem_prog( uint8_t prog_number )
{
  uint8_t p_name[20];
  get_progmem_prog_name( prog_number, p_name );
  print_info( p_name, get_progmem_prog_time( prog_number ) );
}

uint8_t get_user_choice( void )
{
  uint8_t i = 0, t_cnt = 0;

  DDRB &= ~ ( 1 << 3 ); // set 11 dio input
  PORTB |= 1 << 3; // PULL UP
  DDRD |= 1 << 3; // set 3 dio output
  PORTD &= ~ (1 << 3 ); // set to 0

  print_progmem_prog( 0 );

  for(;;)
  {
    _delay_ms(DEL_CLK);
    if( PINB & ( 1 << 3 ) ) // отжата
    {
      if( t_cnt > SHORT_CLK ) // короткое
      {
        if( ++i > NUM_PROGMEM_PROG ) i = 0;

		if( i == NUM_PROGMEM_PROG )
		{
		  if( get_eeprom_num_progs() > 0 ) print_eeprom_prog(); // программа EEPROM
		  else i--;
		}
		else print_progmem_prog( i );
      }
      t_cnt = 0;
    }
    else // нажата
    {
      if( t_cnt > LONG_CLK ) // длинное нажатие
	  {
        if( i == NUM_PROGMEM_PROG ) i = 255;
		print_ok();
		return i;
	  }
      t_cnt++;
    }
  }
}
