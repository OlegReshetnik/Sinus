//*****************************************************************************
#ifndef LCD_LIB
#define LCD_LIB

#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define LCD_CLR             0	//DB0: clear display
#define LCD_HOME            1	//DB1: return to home position
#define LCD_ENTRY_MODE      2	//DB2: set entry mode
#define LCD_ENTRY_INC       1	//DB1: increment
#define LCD_ENTRY_SHIFT     0	//DB2: shift
#define LCD_ON_CTRL         3	//DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2	//DB2: turn display on
#define LCD_ON_CURSOR       1	//DB1: turn cursor on
#define LCD_ON_BLINK        0	//DB0: blinking cursor
#define LCD_MOVE            4	//DB4: move cursor/display
#define LCD_MOVE_DISP       3	//DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2	//DB2: move right (0-> left)
#define LCD_FUNCTION        5	//DB5: function set
#define LCD_FUNCTION_8BIT   4	//DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3	//DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2	//DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6	//DB6: set CG RAM address
#define LCD_DDRAM           7	//DB7: set DD RAM address

//******** LCD connection & parametrs *******
#define LCD_Y_SIZE		2
#define LCD_X_SIZE		16

#define LCD_RS_PIN		0		//define MCU pin connected to LCD RS
#define LCD_RS_PORT		PORTB
#define LCD_RS_DDR		DDRB

#define LCD_E_PIN		1		//define MCU pin connected to LCD E
#define LCD_E_PORT		PORTB
#define LCD_E_DDR		DDRB

#define LCD_D4_PIN		4		//define MCU pin connected to LCD D4
#define LCD_D4_PORT		PORTD
#define LCD_D4_DDR		DDRD

#define LCD_D5_PIN		5		//define MCU pin connected to LCD D5
#define LCD_D5_PORT		PORTD
#define LCD_D5_DDR		DDRD

#define LCD_D6_PIN		6		//define MCU pin connected to LCD D6
#define LCD_D6_PORT		PORTD
#define LCD_D6_DDR		DDRD

#define LCD_D7_PIN		7		//define MCU pin connected to LCD D7
#define LCD_D7_PORT		PORTD
#define LCD_D7_DDR		DDRD
//********************************************

#define lcd_cursor_on() _command(0x0E)

#define lcd_cursor_blink() _command(0x0F)

#define lcd_cursor_off() _command(0x0C)

#define lcd_blank() _command(0x08)

#define lcd_visible() _command(0x0C)

void lcd_init( void );

void lcd_write( uint8_t ch );

void lcd_clear(void);

void lcd_home( void );

void lcd_gotoxy( uint8_t x_col, uint8_t y_row );

void lcd_create_char( uint8_t char_code, uint8_t * map ); // pointer *map to PROGMEM

void lcd_print_int( uint16_t value, uint8_t n_razr );

void lcd_print_string( uint8_t * str );

void lcd_print_time( uint16_t n_second, uint8_t x, uint8_t y );

#endif

