#include "lcd_lib.h"

uint8_t _x = 0, _y = 0;

void _pulse(void)
{
  LCD_E_PORT &= ~( 1 << LCD_E_PIN );
  LCD_E_PORT |= 1 << LCD_E_PIN;
  _delay_us( 1 );
  LCD_E_PORT &= ~( 1 << LCD_E_PIN );
  _delay_us( 1 );
}

void _write4bits( uint8_t value )
{
  if( value & 1 ) LCD_D4_PORT |= ( 1 << LCD_D4_PIN ); else LCD_D4_PORT &= ~( 1 << LCD_D4_PIN );
  if( value & 2 ) LCD_D5_PORT |= ( 1 << LCD_D5_PIN ); else LCD_D5_PORT &= ~( 1 << LCD_D5_PIN );
  if( value & 4 ) LCD_D6_PORT |= ( 1 << LCD_D6_PIN ); else LCD_D6_PORT &= ~( 1 << LCD_D6_PIN );
  if( value & 8 ) LCD_D7_PORT |= ( 1 << LCD_D7_PIN ); else LCD_D7_PORT &= ~( 1 << LCD_D7_PIN );
  _pulse();
}

void _command(uint8_t cmd)
{
	_write4bits( cmd >> 4 );
	_write4bits( cmd );
	_delay_us( 50 );
}

void lcd_write( uint8_t ch )
{
	LCD_RS_PORT |= 1 << LCD_RS_PIN;
	_command( ch );
	LCD_RS_PORT &= ~( 1 << LCD_RS_PIN );
	_x++;
}

void lcd_init( void )
{
	LCD_D4_DDR |= 1 << LCD_D4_PIN; // set to output
	LCD_D5_DDR |= 1 << LCD_D5_PIN;
	LCD_D6_DDR |= 1 << LCD_D6_PIN;
	LCD_D7_DDR |= 1 << LCD_D7_PIN;
	
	LCD_RS_DDR |= 1 << LCD_RS_PIN;
	LCD_E_DDR |= 1 << LCD_E_PIN;

	_delay_ms(20); _write4bits(3); // 8 bit
	_delay_ms(5); _write4bits(3);
	_delay_us(150); _write4bits(3);

	_delay_ms(150); _write4bits(2); // 4 bit

	_command( 0x28 ); // 2 string
	_command( 0x0C ); // display on, cursor off
}			

void lcd_clear(void)
{
	_command( 1 << LCD_CLR );
	_delay_ms( 2 );
	_x = _y = 0;
}

void lcd_home( void )
{
	_command( 1 << LCD_HOME );
	_delay_ms( 2 );
	_x = _y = 0;
}

void lcd_gotoxy( uint8_t x_col, uint8_t y_row )
{
  uint8_t offset;
  
  x_col %= LCD_X_SIZE; y_row %= LCD_Y_SIZE;
  switch( y_row )
  {
	case 0: offset = 0x00; break;
	case 1: offset = 0x40; break;
	case 2: offset = LCD_X_SIZE; break;
	case 3: offset = 0x40 + LCD_X_SIZE; break;
	default: break;
  }
  _command( 1 << LCD_DDRAM | ( x_col + offset) );
  _x = x_col; _y = y_row;
}

void lcd_create_char( uint8_t char_code, uint8_t * map )
{
  _command( 0x40 | ( char_code & 7 ) << 3 );
  
  for( uint8_t i = 0; i < 8; i++ )
  {
	lcd_write( pgm_read_byte( map + i ) );
  }
  
  _x -= 8; lcd_gotoxy( _x, _y );
}

void lcd_print_int( uint16_t value, uint8_t n_razr )
{
  switch( n_razr )
  {
    case 5: lcd_write( value / 10000 + '0' );
    case 4: lcd_write( ( value / 1000 ) % 10 + '0' );
    case 3: lcd_write( ( value / 100 ) % 10 + '0' );
    case 2: lcd_write( ( value / 10 ) % 10 + '0' );
    case 1: lcd_write( value % 10 + '0' );
  }
}

void lcd_print_string( uint8_t * str )
{
	while( *str ) lcd_write( *str++ );
}

void lcd_print_time( uint16_t n_second, uint8_t x, uint8_t y )
{
  lcd_gotoxy( x, y );
  lcd_print_int( n_second / 3600, 2 );
  lcd_write( ':' );
  lcd_print_int( ( n_second / 60) % 60, 2 );
  lcd_write( ':' );
  lcd_print_int( n_second % 60, 2 );
}
