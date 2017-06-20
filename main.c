#include "lcd_lib.h"
#include "lcd_rus_lib.h"
#include "dds_lib.h"

#include "prog_serial.h"
#include "user_menu.h"


void print_percent( uint8_t pp )
{
	lcd_gotoxy( 0, 1 );
	lcd_print_int( pp, 2 );
	lcd_write( '%' );
}

void stop_programm( void )
{
	dds_stop();
	lcd_rus_clear();
	lcd_rus_print_string( " ŒÕ≈÷ œ–Œ√–¿ÃÃ€." );
	for(;;);
}

int main( void )
{
	uint8_t choice, i_prog = 0, num_progs;
	uint16_t i_time = 0, n_time, all_time, tick = 0;

	lcd_init();

	read_program_from_serial();
	choice = get_user_choice();

	if( choice == 255 ) // eeprom
	{
		num_progs = get_eeprom_num_progs();
		all_time = get_eeprom_prog_time();

		n_time = get_eeprom_i_time( i_prog );
		print_percent( tick * 100 / all_time );

		dds_set_freq( get_eeprom_freq( i_prog ) );
	}
	else // progmem
	{
		num_progs = get_progmem_num_progs( choice );
		all_time = get_progmem_prog_time( choice );

		n_time = get_progmem_i_time( choice, i_prog );
		print_percent( tick * 100 / all_time );

		dds_set_freq( get_progmem_freq( choice, i_prog ) );
	}

	lcd_print_time( all_time, 8, 1 );
	dds_start();

	for(;;)
	{
		if( is_dds_1sec() ) // timer / wait for a second
		{
			dds_clear_1sec();

			if( ++tick == all_time ) stop_programm();

			lcd_print_time( all_time - tick, 8, 1 );

			print_percent( (uint8_t)( (uint32_t)tick * 100 / (uint32_t)all_time ) );

			if( ++i_time == n_time )
			{
				i_time = 0;
				if( ++i_prog == num_progs) i_prog = 0;

				if( choice == 255 ) // eeprom
				{
					n_time = get_eeprom_i_time( i_prog );
					dds_set_freq( get_eeprom_freq( i_prog ) );
				}
				else // progmem
				{
					n_time = get_progmem_i_time( choice, i_prog );
					dds_set_freq( get_progmem_freq( choice, i_prog ) );
				}

			}
		}
	}

}
