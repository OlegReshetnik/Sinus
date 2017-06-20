#ifndef progmem_prog_h
#define progmem_prog_h

#include <avr/pgmspace.h>

#define NUM_PROGMEM_PROG 18

float get_progmem_freq( uint8_t prog_number, uint8_t i_prog );

uint16_t get_progmem_i_time( uint8_t prog_number, uint8_t i_prog );

uint8_t get_progmem_num_reps( uint8_t prog_number );

uint8_t get_progmem_num_progs( uint8_t prog_number );

void get_progmem_prog_name( uint8_t prog_number, uint8_t * p_name );

uint16_t get_progmem_prog_time( uint8_t prog_number );

#endif

