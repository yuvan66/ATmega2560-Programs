#include "usart.h"

void usart_init()
{
	// SET BAUD RATE // 103 -> 9600 BAUD RATE
	UBRR0 = 103U;
	
	// ENABLE TRANSMITTER & RECEIVER
	UCSR0B |= ((1<<3) | (1<<4));
	
	// SETTING ASYNCHRONOUS USART
	UCSR0C &= (~(1<<7));
	UCSR0C &= (~(1<<6));
	
	// DISABLING PARITY MODE
	UCSR0C &= (~(1<<5));
	UCSR0C &= (~(1<<4));
	
	// SETTING 1 STOP BIT
	UCSR0C &= (~(1<<3));
	
	// SETTING DATA SIZE 8-bit
	UCSR0C |= ((1<<2) | (1<<1));
	UCSR0B &= (~(1<<2));
	
	// CLOCK POLARITY -> 0 FOR ASYNCHRONOUS MODE
	UCSR0C &= (~(1<<0));
}

void usart_transmit(uint8_t data)
{
	// WAITING FOR DATA TRANSMIT BUFFER TO BE CLEARED
	while(!(UCSR0A & (1<<5)));
	
	// LOADING data INTO TRANSMIT BUFFER -> SENDING(TRANSMITTING) THE data
	UDR0 = data;
}

void usart_transmit_string(char string[])
{
  for (uint8_t c=0;string[c]!='\0';c++)
  {
    UDR0 = string[c];
    for(volatile uint32_t ii=0;ii<10000;ii++);
  }
}