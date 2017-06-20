#include "eeprom_prog.h"

float get_eeprom_freq( uint8_t i_prog )
{
  uint8_t b4, b3, b2, b1;
  uint8_t * ep = ( uint8_t * )( i_prog * 6 + 2 + 2 );

  b4 = eeprom_read_byte( ep++ );
  b3 = eeprom_read_byte( ep++ );
  b2 = eeprom_read_byte( ep++ );
  b1 = eeprom_read_byte( ep++ );

  return ( ( (uint32_t)b4 << 24 ) | ( (uint32_t)b3 << 16 ) | ( (uint32_t) b2 << 8 ) + (uint32_t)b1 ) / 100.0;
}

uint16_t get_eeprom_i_time( uint8_t i_prog )
{
  uint8_t * ep = ( uint8_t * )( i_prog * 6 + 2 );
  return ( ( ( (uint16_t)eeprom_read_byte( ep ) << 8) ) | (uint16_t)eeprom_read_byte( ep + 1 ) );
}

uint8_t get_eeprom_num_reps()
{
  return eeprom_read_byte( (uint8_t * )1 );
}

uint8_t get_eeprom_num_progs()
{
  return eeprom_read_byte( (uint8_t * )0 );
}

void get_eeprom_prog_name( uint8_t * p_name )
{
  uint8_t * ep = ( uint8_t * )( get_eeprom_num_progs() * 6 + 2 );

  while( *p_name++ = eeprom_read_byte( ep++ ) );
}

uint16_t get_eeprom_prog_time()
{
  uint16_t all_time = 0;
  uint8_t i_prog = 0, num_progs = get_eeprom_num_progs();

  while( i_prog < num_progs ) all_time += get_eeprom_i_time( i_prog++ ); // calculate all time
  all_time *= get_eeprom_num_reps();
  return all_time;
}

uint8_t * eeprom_p = ( uint8_t * )0;
void set_eeprom_next_byte( uint8_t next_byte )
{
  eeprom_write_byte( eeprom_p++, next_byte );
}
