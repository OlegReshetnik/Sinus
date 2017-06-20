#include "serial_lib.h"

uint8_t rx_buf[ RX_BUFFER_SIZE ];
volatile uint8_t rx_head = 0;
uint8_t rx_tail = 0;

uint8_t tx_buf[ TX_BUFFER_SIZE ];
uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;

void serial_init()
{
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
    UCSR0A |= ( 1 << U2X0 );
  #else
    UCSR0A &= ~( 1 << U2X0 );
  #endif

  UCSR0B |= ( 1 << RXEN0 ) | ( 1 << TXEN0 ) | ( 1 << RXCIE0 ); // включить приемник, передатчик, прерывание приемника

  sei();
}

uint8_t serial_rx_ready()
{
  uint8_t head = rx_head;
  if( head >= rx_tail ) return head - rx_tail;
  return RX_BUFFER_SIZE - ( rx_tail - head );
}

uint8_t serial_tx_ready()
{
  uint8_t tail = tx_tail;
  if( tx_head >= tail ) return tx_head - tail;
  return TX_BUFFER_SIZE - ( tail - tx_head );
}

uint8_t serial_read()
{
  if( rx_head == rx_tail ) return SERIAL_NO_DATA;
  else
  {
    uint8_t data = rx_buf[ rx_tail++ ];
    if( rx_tail == RX_BUFFER_SIZE ) rx_tail = 0;
	return data;
  }
}

void serial_clear_read() 
{
  rx_tail = rx_head;
}

void serial_write(uint8_t data)
{
  uint8_t head = tx_head + 1;
  if( head == TX_BUFFER_SIZE ) head = 0;

  while( head == tx_tail ); // Ждать место

  tx_buf[ tx_head ] = data;
  tx_head = head;
  
  UCSR0B |=  ( 1 << UDRIE0 ); // Прерывание передатчика
}

void serial_print_string( uint8_t * str )
{
	while( *str ) serial_write( *str++ );
}

ISR(USART_UDRE_vect)
{
  uint8_t tail = tx_tail;
  UDR0 = tx_buf[ tail++ ];
  
  if( tail == TX_BUFFER_SIZE ) tail = 0;
  tx_tail = tail;

  if( tail == tx_head ) UCSR0B &= ~( 1 << UDRIE0 ); // выключить прерывание передатчика
}

ISR(USART_RX_vect)
{
  uint8_t data = UDR0;
  uint8_t old_head = rx_head;
  uint8_t head = old_head + 1;

  if( head == RX_BUFFER_SIZE ) head = 0;

  if( head != rx_tail )
  {
    rx_buf[ old_head ] = data;
    rx_head = head;
  }
}
