#include <stdint.h> 


#define TCNT0 (*(volatile uint8_t*)0x46) // Timer 0 Counter Register; holds the current count of Timer 0; 
//increments based on the clock source and prescaler settings; overflows back to 0 after reaching 255 in normal mode;
// in CTC mode with OCR0A as top, it resets to 0 when it matches the value in OCR0A


#define TCCR0A (*(volatile uint8_t*)0x44) // Timer 0 Control Register A; used to configure the mode of operation for Timer 0 (normal, CTC, PWM, etc.) 
//and the output compare behavior for OC0A and OC0B pins


#define TCCR0B (*(volatile uint8_t*)0x45) // Timer 0 Control Register B; used to configure the clock source and prescaler for Timer 0,
// as well as additional mode settings (like CTC mode with OCR0A as top)


#define TIFR0 (*(volatile uint8_t*)0x35) // Timer 0 Interrupt Flag Register; bit 0 (TOV0) is set when Timer 0 overflows; 
//bit 1 (OCF0A) is set when a compare match occurs with OCR0A;


#define TIMSK (*(volatile uint8_t*)0x6E) // Timer Interrupt Mask Register; bit 0 (TOIE0) enables interrupt on overflow for Timer 0;


#define OCR0A (*(volatile uint8_t*)0x47) // Output Compare Register A; used in CTC mode to define the value
// at which TCNT0 resets to 0; also used in PWM modes to define the duty cycle (0-255 corresponding to 0%-100% duty cycle)


#define SREG (*(volatile uint8_t*)0x5F) // bit 7 is I; set to 1 to enable global interrupts; set to 0 to disable global interrupts



#define TCCR1A  (*(volatile uint8_t *)0x80) // Timer 1 Control Register A; used to configure 
//the mode of operation for Timer 1 (normal, CTC, PWM, etc.) and the output compare behavior for OC1A and OC1B pins


#define TCCR1B  (*(volatile uint8_t *)0x81) // Timer 1 Control Register B; used to configure
//the clock source and prescaler for Timer 1, as well as additional mode settings (like CTC mode with OCR1A as top)


#define TCNT1   (*(volatile uint16_t *)0x84) // Timer 1 Counter Register; holds the current count of Timer 1;
// increments based on the clock source and prescaler settings; overflows back to 0 after reaching 65535 in normal mode;
// in CTC mode with OCR1A as top, it resets to 0 when it matches the value in OCR1A


#define OCR1A   (*(volatile uint16_t *)0x88) // Output Compare Register A for Timer 1; used in CTC mode to define
// the value at which TCNT1 resets to 0; also used in PWM modes to define the duty cycle for OC1A pin (0-65535 corresponding to 0%-100% duty cycle)


#define TIMSK1  (*(volatile uint8_t *)0x6F) // Timer 1 Interrupt Mask Register; bit 0 (TOIE1) enables interrupt on overflow;
// bit 1 (OCIE1A) enables interrupt on compare match A; bit 2 (OCIE1B) enables interrupt on compare match B


#define SREG  (*(volatile uint8_t *)0x5F) // AVR Status Register; bit 7 (I) is the Global Interrupt Enable flag; 
//set to 1 to enable global interrupts;



#define TIMER0_NORMAL_MODE 199
#define TIMER0_CTC_MODE 200
#define TIMER0_FAST_PWM_MODE 201
#define TIMER0_PHASE_CORRECT_PWM_MODE 202

#define TIMER0_PRESCALER_1 0x01
#define TIMER0_PRESCALER_8 0x02
#define TIMER0_PRESCALER_64 0x03
#define TIMER0_PRESCALER_256 0x04
#define TIMER0_PRESCALER_1024 0x05


#define TIMER1_NORMAL_MODE 299
#define TIMER1_CTC_MODE 300
#define TIMER1_FAST_PWM_MODE 301
#define TIMER1_PHASE_CORRECT_PWM_MODE 302

#define TIMER1_PRESCALER_1 0x01
#define TIMER1_PRESCALER_8 0x02
#define TIMER1_PRESCALER_64 0x03
#define TIMER1_PRESCALER_256 0x04
#define TIMER1_PRESCALER_1024 0x05



//*** TIMER0 Functions ***

void timer0_interrupt_enable()
{
    TIMSK |= (1U<<0); // Set TOIE0 bit to enable Timer0 overflow interrupt
    SREG |= (1U<<7); // Set I bit in SREG to enable global interrupts
}

void timer0_interrupt_disable()
{
    TIMSK &= ~(1U<<0); // Clear TOIE0 bit to disable Timer0 overflow interrupt
}

void timer0_setmode(uint16_t mode)
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

void timer0_stop()
{
    TCCR0B &= ~(0x07); // Clear the clock select bits (CS00, CS01, CS02) to stop the timer
}

void timer0_start(uint8_t prescaler)
{
    TCCR0B &= ~(0x07); // Clear the clock select bits (CS00, CS01, CS02) to reset any previous prescaler settings
    TCCR0B |= (prescaler & 0x07); // Set the desired prescaler (only the lower 3 bits are relevant)
}

/*
void delay_ms(uint16_t ms)
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
}*/


//*** TIMER1 Functions ***/

void timer1_interrupt_enable()
{
    TIMSK1 |= (1U<<1); // 
    SREG |= (1U<<7); // Set I bit in SREG to enable global interrupts
}

void timer1_interrupt_disable()
{
    TIMSK1 &= ~(1U<<0); // Clear TOIE1 bit to disable Timer1 overflow interrupt
}

void timer1_setmode(uint16_t mode)
{
    if (mode==299)
    {
        TCCR1A &= ~( (1U<<0) | (1U<<1) ); // Clear WGM10 and WGM11 for normal mode
        TCCR1B &= ~( (1U<<3) | (1U<<4) ); // Clear WGM12 and WGM13 for normal mode
    }

    else if (mode==300)
    {
        TCCR1A &= ~( (1<<0) | (1U<<1) ); // Clear WGM10 and WGM11
        TCCR1B |= (1<<3); // Set WGM12 for CTC mode
        TCCR1B &= ~(1<<4); // Clear WGM13 for CTC mode
    }

    else if (mode==301)
    {
        TCCR1A |= (1U<<0) | (1U<<1); // Set WGM10 and WGM11 for fast PWM mode
        TCCR1B &= ~( (1U<<3) | (1U<<4) ); // Clear WGM12 and WGM13 for fast PWM mode
    }

    else if (mode==302)
    {
        TCCR1A |= (1U<<0); // Set WGM10 for phase correct PWM mode
        TCCR1A &= ~(1U<<1); // Clear WGM11
        TCCR1B &= ~( (1U<<3) | (1U<<4) ); // Clear WGM12 and WGM13 for phase correct PWM mode
    }
}

void timer1_stop()
{
    TCCR1B &= ~(0x07); // Clear the clock select bits (CS10, CS11, CS12) to stop the timer
}

void timer1_start(uint8_t prescaler)
{
    TCCR1B &= ~(0x07); // Clear the clock select bits (CS10, CS11, CS12) to reset any previous prescaler settings
    TCCR1B |= prescaler; // Set the desired prescaler (only the lower 3 bits are relevant)
}