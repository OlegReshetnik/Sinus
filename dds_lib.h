#ifndef dds_lib_h
#define dds_lib_h

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define REFCLK (F_CPU/256) // 16 000 000 / 256 = 62500.0
#define POW_2_32 4294967296.0 // pow(2,32)

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

uint8_t is_dds_1sec( void );

void dds_clear_1sec( void );

void dds_clear_1sec(void);

void dds_start( void );

void dds_stop( void );

void dds_set_freq( float freq );

#endif
