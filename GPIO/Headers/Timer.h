#define TCNT0 (*(volatile uint8_t*)0x46) // Timer Counter0 Register
#define TCCR0A (*(volatile uint8_t*)0x44) // Timer/Counter0 Control Register A
#define TCCR0B (*(volatile uint8_t*)0x45) // Timer/Counter0 Control Register B
#define TIFR0 (*(volatile uint8_t*)0x35) // Timer/Counter0 Interrupt Flag Register
#define TIMSK (*(volatile uint8_t*)0x0x6E) // Timer/Counter0 Interrupt Mask Register




void delay_ms(int ms)
{
  TCCR0A = 0x02;
  TCCR0B = 0x03;
  
  
//  TIMSK = 0x00;
    for (int i=0;i<ms;i++)
    {
      TCNT0 = 6;
      
      while(!(TIFR0 & 0x01)); // 1ms
      TIFR0 = 0x01; // 0000 0000
    }
}


void pwm0