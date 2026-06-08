#include "usart_bit_banging.h"

#include <stdint.h>

void bit_duration(void)
{
  // SETTING COUNTER'S INITIAL VALUE AS 0
    TCNT0 = 231;

  //
  // OCR0A = 1;
    
    // LOOPS FOR 104uS
    while(!(TIFR0 & 0x02));
        
    // CLEARING THE OCF0A BIT 
        TIFR0 = 0x02;
}

void usart_init_bb(void)
{
    // SETTING THE GPIO PIN AS OUTPUT TO ACT AS TRANSMITTER
    DDRF |= 0x01;
    
    // IDLE -> ALWAYS HIGH UNITL START BIT
    DATF = (0x01);  

    // SETTING TIMER0 IN CTC MODE
    TCCR0A = 0x02;
    
    // SETTING PRESCALER TO 64 FOR ACHIEVING 104uS DELAY FOR EVERY COUNT 
    TCCR0B = 0x03;
}


void usart_transmit_bb(uint8_t data)
{ 
  bit_duration();
    // MAKING THE START BIT
    DATF &= ~(0x01);
    
    // TODO
    bit_duration();
    
    for (uint8_t i=0;i<8;i++)
    {
      // DATF = data&0x01;
        
        // TODO
        if (data & (1<<0))
        {
            DATF |= (1<<0);
        }
        
        //TODO
        else
        {
            DATF &= ~(1<<0);
        }

        // 
        data = (data >> 1);
        
        // TODO
        bit_duration();
    }
    
    // TODO
    DATF |= (1<<0);
    
//    bit_duration();
    
}