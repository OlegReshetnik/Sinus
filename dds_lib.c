#include "dds_lib.h"

// variables used inside interrupt service declared as voilatile
volatile uint8_t __c4ms = 0;     // counter incremented all 4ms
volatile uint32_t __phaccu = 0;  // pahse accumulator
volatile uint32_t __tword_m = 0; // dds tuning word m
volatile uint8_t __ic = 0;       // var inside interrupt: interrupt_counter

// table of 256 sine values / one sine period / stored in flash memory
const uint8_t __sine256[] PROGMEM = {
127,130,133,136,139,142,146,149,152,155,158,161,164,167,170,173,175,178,181,184,187,189,192,195,197,200,202,205,207,210,212,214,
216,219,221,223,225,227,229,230,232,234,236,237,239,240,241,243,244,245,246,247,248,249,250,250,251,252,252,253,253,253,253,253,
254,253,253,253,253,253,252,252,251,250,250,249,248,247,246,245,244,243,241,240,239,237,236,234,232,230,229,227,225,223,221,219,
216,214,212,210,207,205,202,200,197,195,192,189,187,184,181,178,175,173,170,167,164,161,158,155,152,149,146,142,139,136,133,130,
127,124,121,118,115,112,108,105,102,99,96,93,90,87,84,81,79,76,73,70,67,65,62,59,57,54,52,49,47,44,42,40,
38,35,33,31,29,27,25,24,22,20,18,17,15,14,13,11,10,9,8,7,6,5,4,4,3,2,2,1,1,1,1,1,
1,1,1,1,1,1,2,2,3,4,4,5,6,7,8,9,10,11,13,14,15,17,18,20,22,24,25,27,29,31,33,35,
38,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,81,84,87,90,93,96,99,102,105,108,112,115,118,121,124 };

void dds_clear_1sec( void ) { __c4ms = 0; }

uint8_t is_dds_1sec( void ) { return ( __c4ms >= ( REFCLK / 250 ) ); }
 
// timer2 setup: set prscaler to 1, PWM mode to fast PWM,  16 000 000/256 = 62 500 Hz clock
void dds_start( void )
{
  // Timer2 Clock Prescaler to : 1
  sbi(TCCR2B, CS20);
  cbi(TCCR2B, CS21);
  cbi(TCCR2B, CS22);

  cbi(TCCR2A, COM2A0);  // clear Compare Match Arduino pin 11 PB3 OC2A
  sbi(TCCR2A, COM2A1);

  sbi(TCCR2A, COM2B0);  // set Compare Match Arduino pin 3 PD3 OC2B
  sbi(TCCR2A, COM2B1);

  sbi(TCCR2A, WGM20);  // Timer2 Mode 3 fast PWM
  sbi(TCCR2A, WGM21);
  cbi(TCCR2B, WGM22);

  cbi(TIMSK0,TOIE0);  // disable Timer0 !!! delay() is now not available / disable interrupts to avoid timing distortion
  sbi(TIMSK2,TOIE2);  // enable Timer2 Interrupt
  
  sbi(DDRB,3); // set 11 dio arduino (OC2A) to output for PWM;
  sbi(DDRD,3); // set 3 dio arduino (OC2B) to output for PWM;
  
  sei(); // enable CPU interrupt
}

void dds_stop( void )
{
  cli();
  cbi(TIMSK2,TOIE2); // disble Timer2 Interrupt OR cli();
  cbi(DDRB,3); // clear 11 dio arduino (OC2A) to output for PWM;
  cbi(DDRD,3); // clear 3 dio arduino (OC2B) to output for PWM;
}

void dds_set_freq( float freq )
{
  cbi(TIMSK2,TOIE2); // disble Timer2 Interrupt
  __tword_m = POW_2_32 * freq / (float)REFCLK;  // calulate DDS new tuning word
  sbi(TIMSK2,TOIE2); // enable Timer2 Interrupt;
}

//*********************** *******************************************
// Timer2 Interrupt Service at REFCLK = 62 500 Hz, period: 16 microseconds
// this is the timebase REFCLOCK for the DDS generator
// FOUT = (M (REFCLK)) / (2 exp 32)
// runtime : 8 microseconds ( inclusive push and pop)
ISR(TIMER2_OVF_vect)
{
  uint32_t pcu = __phaccu + __tword_m;  //soft DDS, phase accu with 32 bits
  
  OCR2B = OCR2A = pgm_read_byte_near( __sine256 + (pcu >> 24) ); // Use upper 8 bits for phase accu as frequency information.
  __phaccu = pcu;                                                // Read value fron ROM sine table and send to PWM DAC

  if( 0 == __ic-- ) // increment variable c4ms all 4 milliseconds
  {
    __c4ms++;
    __ic = 250; // 62 500 / 250
  }   
}
