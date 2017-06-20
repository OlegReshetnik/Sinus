#ifndef eeprom_prom_h
#define eeprom_prom_h

#include <avr/eeprom.h>

float get_eeprom_freq( uint8_t i_prog );

uint16_t get_eeprom_i_time( uint8_t i_prog );

uint8_t get_eeprom_num_reps();

uint8_t get_eeprom_num_progs();

void get_eeprom_prog_name( uint8_t *p_name );

uint16_t get_eeprom_prog_time();

void set_eeprom_next_byte( uint8_t next_byte );

#endif
