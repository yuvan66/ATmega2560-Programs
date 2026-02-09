#include "GPIO.h"


/****** This Library contains functions to display Single Digit values to Four Digit Values on a Seven Segment Display ******/

                            /******     Has certain Constraints to use this Library Functions     
							                       Refer those constraints BELOW                    ******/									
							
							
							/******     CANNOT DISPLAY ALPHABETS. ONLY NUMBERS FROM 0 to 9         ******/
							
							
							
const volatile uint8_t a[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	
	

// Function to Display Single Digit value 
// ***MUST CONFIGURE the PORT that is used during the SETUP
void disp_1d(uint8_t x, uint8_t val) // disp_1d(port_name,value)
{   
	*DAT[x] = a[val];
}



// Function to Display Two Digit value
// ***MUST CONFIGURE the PORTS that is used during the SETUP
void disp_2d(uint8_t x, uint8_t y, uint8_t val) //disp_2d(port_name, selection_port_name, value)
{
	volatile long b = 0;
	*DAT[y] = 0xFF;
	while(b<100000)
	{
		*DAT[x] = a[val%10];
		*DAT[y] = ~0x02;
		*DAT[y] = 0x03;
		*DAT[x] = a[val/10];
		*DAT[y] = ~0x01;
		*DAT[y] = 0x03;
		b++;
	}
}



// Function to Display Three Digit value
// **MUST CONFIGURE the PORTS that is used during the SETUP
void disp_3d(uint8_t x, uint8_t y, uint16_t val) //disp_2d(port_name, selection_port_name, value)
{
	volatile long b = 0;
	*DAT[y] = 0xFF;
	while(b<100000)
	{
		*DAT[x] = a[val%10];
		*DAT[y] = ~0x04;
		*DAT[y] = 0x07;
		*DAT[x] = a[(val/10)%10];
		*DAT[y] = ~0x02;
		*DAT[y] = 0x07;
		*DAT[x] = a[(val/100)%10];
		*DAT[y] = ~0x01;
		*DAT[y] = 0x07;
		b++;
	}
}



// Function to Display Four Digit value
// ***MUST CONFIGURE the PORTS that is used during the SETUP
void disp_4d(uint8_t x, uint8_t y, uint16_t val) //disp_2d(port_name, selection_port_name, value)
{
	volatile long b = 0;
	*DAT[y] = 0xFF;
	while(b<100000)
	{
		*DAT[x] = a[val%10];
		*DAT[y] = ~0x08;
		*DAT[y] = 0x0F;
		*DAT[x] = a[(val/10)%10];
		*DAT[y] = ~0x04;
		*DAT[y] = 0x0F;
		*DAT[x] = a[(val/100)%10];
		*DAT[y] = ~0x02;
		*DAT[y] = 0x0F;
		*DAT[x] = a[val/1000];
		*DAT[y] = ~0x01;
		*DAT[y] = 0x0F;
		b++;
	}
}