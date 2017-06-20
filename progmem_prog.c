#include "progmem_prog.h"
#include "table_of_programs.h"

float get_progmem_freq( uint8_t prog_number, uint8_t i_prog )
{
  return pgm_read_float( (float *)pgm_read_word( &Freq[ prog_number ] ) + i_prog );
}

uint16_t get_progmem_i_time( uint8_t prog_number, uint8_t i_prog )
{
  return pgm_read_word( (uint16_t *)pgm_read_word( &Time[ prog_number ] ) + i_prog );
}

uint8_t get_progmem_num_reps( uint8_t prog_number )
{
  return pgm_read_byte( &Num_reps[ prog_number ] );
}

uint8_t get_progmem_num_progs( uint8_t prog_number )
{
  return pgm_read_byte( &Num_progs[ prog_number ] );
}

void get_progmem_prog_name( uint8_t prog_number, uint8_t * p_name )
{
  uint8_t * cp = (uint8_t *)pgm_read_word( &Name[ prog_number ] );

  while( *p_name++ = pgm_read_byte( cp++ ) );
}

uint16_t get_progmem_prog_time( uint8_t prog_number )
{
  uint16_t all_time = 0;
  uint8_t i_prog = 0, num_progs = get_progmem_num_progs( prog_number );

  while( i_prog < num_progs ) all_time += get_progmem_i_time( prog_number, i_prog++ ); // calculate all time
  all_time *= (uint16_t)get_progmem_num_reps( prog_number );
  return all_time;
}
