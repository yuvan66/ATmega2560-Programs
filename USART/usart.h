#include <stdint.h>


#define UBRR0 (*(volatile uint16_t *) 0xC4)
#define UCSR0A (*(volatile uint8_t *) 0xC0)
#define UCSR0B (*(volatile uint8_t *) 0xC1)
#define UCSR0C (*(volatile uint8_t *) 0xC2)
#define UDR0 (*(volatile uint8_t *) 0xC6)

void usart_init(void);

void usart_transmit(uint8_t data);

void usart_transmit_string(char string[]);