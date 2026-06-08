#include"Timer-Config.h"

#define ICR1 (*(volatile uint16_t*)0x86)

timer1_setmode(TIMER1_FAST_PWM_MODE);

timer1_start(TIMER0_PRESCALER_8);

timer1_COM();

ICR1 = 39999;

void servo_angle(uint32_t angle)
{
    OCR1A = 1090 + ((uint32_t)angle * 2910) / 180;
    // OCR1A = val;
}
// OCR1A = 3500;