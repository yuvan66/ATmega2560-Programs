/* 
 * File:   usart_bit_banging.h
 * Author: yuvan
 *
 * Created on April 16, 2026, 5:01 PM
 */


//#include "Timer-Config.h"

#include<stdint.h>

#define TCNT0 (*(volatile uint8_t*)0x46)
#define OCR0A (*(volatile uint8_t*)0x47)
#define TCCR0A (*(volatile uint8_t*)0x44)
#define TCCR0B (*(volatile uint8_t*)0x45)
#define TIFR0 (*(volatile uint8_t*)0x35)
#define OCR0A (*(volatile uint8_t*)0x47)

#define DDRF (*(volatile uint8_t *) 0x30)
#define DATF (*(volatile uint8_t *) 0x31)


void bit_duration(void);


void usart_init_bb(void);


void usart_transmit_bb(uint8_t data);