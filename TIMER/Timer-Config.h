#define TCNT0 (*(volatile uint8_t*)0x46) // This register holds the current count of the timer; 
//it increments on each clock cycle as defined by the prescaler; it overflows back to 0 after 
//reaching 255 in normal mode; in CTC mode, it resets to 0 when it matches the value in OCR0A


#define TCCR0A (*(volatile uint8_t*)0x44) // bit 0 and 1 are WGM00 and WGM01 respectively; set to 
//0 for normal mode; set WGM00 to 1 for phase correct PWM mode; set WGM01 to 1 for CTC mode; set both to 1 for fast PWM mode


#define TCCR0B (*(volatile uint8_t*)0x45) // Defines the clock source and prescaler; 0x05 for 1024 prescaler;
// 0x04 for 256 prescaler; 0x03 for 64 prescaler; 0x02 for 8 prescaler; 0x01 for no prescaler


#define TIFR0 (*(volatile uint8_t*)0x35) // bit 0 is TOV0; set to 1 to clear the overflow flag;
// check this bit to know if overflow has occurred


#define TIMSK (*(volatile uint8_t*)0x6E) // bit 0 is TOIE0; set to 1 to enable interrupt on overflow

#define OCR0A (*(volatile uint8_t*)0x47) // Output Compare Register A; used in CTC mode to define the value
// at which TCNT0 resets to 0; also used in PWM modes to define the duty cycle (0-255 corresponding to 0%-100% duty cycle)


#define SREG (*(volatile uint8_t*)0x5F) // bit 7 is I; set to 1 to enable global interrupts; set to 0 to disable global interrupts



#define TIMER0_NORMAL_MODE 199
#define TIMER0_CTC_MODE 200
#define TIMER0_FAST_PWM_MODE 201
#define TIMER0_PHASE_CORRECT_PWM_MODE 202

#define TIMER0_PRESCALER_1 0x01
#define TIMER0_PRESCALER_8 0x02
#define TIMER0_PRESCALER_64 0x03
#define TIMER0_PRESCALER_256 0x04
#define TIMER0_PRESCALER_1024 0x05



//*** TIMER0 Functions ***

timer0_interrupt_enable()
{
    TIMSK |= (1U<<0); // Set TOIE0 bit to enable Timer0 overflow interrupt
    SREG |= (1U<<7); // Set I bit in SREG to enable global interrupts
}

timer0_interrupt_disable()
{
    TIMSK &= ~(1U<<0); // Clear TOIE0 bit to disable Timer0 overflow interrupt
    SREG &= ~(1U<<7); // Clear I bit in SREG to disable global interrupts
}

timer0_setmode(uint8_t mode)
{
    if(mode==199)
    {
        TCCR0A &= ~( (1U<<0) | (1U<<1) ); // Clear WGM00 and WGM01 for normal mode
        TCCR0B &= ~(1U<<3); // Clear WGM02 for normal mode
    }

    else if (mode==200)
    {
        TCCR0A &= ~(1U<<0); // Clear WGM00
        TCCR0A |= (1U<<1); // Set WGM01 for CTC mode
        TCCR0B &= ~(1U<<3); // Clear WGM02 for CTC mode
    }

    else if (mode==201)
    {
        TCCR0A |= (1U<<0) | (1U<<1); // Set WGM00 and WGM01 for fast PWM mode
        TCCR0B &= ~(1U<<3); // Clear WGM02 for fast PWM mode
    }

    else if (mode==202)
    {
        TCCR0A |= (1U<<0); // Set WGM00 for phase correct PWM mode
        TCCR0A &= ~(1U<<1); // Clear WGM01
        TCCR0B &= ~(1U<<3); // Clear WGM02 for phase correct PWM mode
    }
}

timer0_stop()
{
    TCCR0B &= ~(0x07); // Clear the clock select bits (CS00, CS01, CS02) to stop the timer
}

timer0_start(uint8_t prescaler)
{
    TCCR0B &= ~(0x07); // Clear the clock select bits (CS00, CS01, CS02) to reset any previous prescaler settings
    TCCR0B |= (prescaler & 0x07); // Set the desired prescaler (only the lower 3 bits are relevant)
}

delay_ms(uint16_t ms)
{
    TCCR0A = 0x02;
    TCCR0B = 0x03;
    
    //  TIMSK = 0x00;
    for (int i=0;i<ms;i++)
    {
      TCNT0 = 6;
      
      while(!(TIFR0 & 0x01)); // 1ms
      TIFR0 = 0x01; // Clear the overflow flag by writing a 1 to it
    }
}