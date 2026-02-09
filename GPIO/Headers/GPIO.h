#include<stdint.h>



              /****** Contains Functions to Configure GPIO PORTS and a particular PIN Seperately ******/

                /****** Contains Functions to Write GPIO PORTS and a particular PIN Seperately ******/

                     /****** Contains Functions that returns the VALUE at GPIO PORTS ******/



#define HIGH 1U
#define LOW 0U

#define OUTPUT 1U
#define INPUT 0U

#define OUT 0xFF
#define IN 0x00


#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define J 8
#define K 9
#define L 10


volatile uint8_t *DDR[]  = {(volatile uint8_t *)0x21,(volatile uint8_t *)0x24,(volatile uint8_t *)0x27,(volatile uint8_t *)0x2A,
	                        (volatile uint8_t *)0x2D,(volatile uint8_t *)0x30,(volatile uint8_t *)0x33,(volatile uint8_t *)0x101,
							(volatile uint8_t *)0x104,(volatile uint8_t *)0x107,(volatile uint8_t *)0x10A};
								  
volatile uint8_t *DAT[]  = {(volatile uint8_t *)0x22,(volatile uint8_t *)0x25,(volatile uint8_t *)0x28,(volatile uint8_t *)0x2B,
	                        (volatile uint8_t *)0x2E,(volatile uint8_t *)0x31,(volatile uint8_t *)0x34,(volatile uint8_t *)0x102,
							(volatile uint8_t *)0x105,(volatile uint8_t *)0x108,(volatile uint8_t *)0x10B};
								  
volatile uint8_t  *RD[]  = {(volatile uint8_t *)0x20,(volatile uint8_t *)0x23,(volatile uint8_t *)0x26,(volatile uint8_t *)0x29,
	                        (volatile uint8_t *)0x2C,(volatile uint8_t *)0x2F,(volatile uint8_t *)0x32,(volatile uint8_t *)0x100,
						    (volatile uint8_t *)0x103,(volatile uint8_t *)0x106,(volatile uint8_t *)0x109};



//Set Direction for Entire PORT
void config_reg(uint8_t x, uint8_t y) // config_reg(port_name,0xFF)
{
	*DDR[x] = y;
}

//Set Direction for a particular PIN of a PORT
void config_pin(uint8_t x, uint8_t y, uint8_t z) // config_pin(port_name, pin, state) // state is either OUT or IN
{
	if(z==1U)
	{
		*DDR[x] |= (1U<<y);
	}
	else
	{
		*DDR[x] &= ~(0U<<y);
	}
}



//Set Data for Entire PORT
void reg_write(uint8_t x,volatile uint8_t y) //reg_write(port_name,0xFF)
{
	*DAT[x] = y;
}

//Set Data for a particular PIN of a PORT
void pin_write(uint8_t x, uint8_t y, uint8_t z) // pin_write(port_name, pin, state) // state is either HIGH or LOW
{
	volatile uint8_t *p;
	p = DAT[x];
	if(z==1U)
	{
		*DAT[x] |= (1U<<y);
	}
	else
	{
		*DAT[x] &= ~(0U<<y);
	}
}



//Read Register
uint8_t reg_read(uint8_t x) //Returns the register data in unsigned int (8 bit)
{
	return *RD[x];
}


// Additional Functions

// Delay
void delay_y(uint8_t x) // Argument is the amount of delay (1 is lowest)
{
	for (volatile long i=0;i<10000*x;i++);
}



// LED Blinking
// **** This Function runs FOREVER!!! ****
// ****Must configure the PORT you use as OUTPUT during SETUP****
// Connect the 1st PIN of the PORT to the LED
void led_blink(uint8_t x)
{
	while (1)
	{
		*DAT[x] |= (1U<<1);
		for(volatile int i=0;i<10000;i++);
		*DAT[x] &= ~(1U<<1);
		for(volatile int i=0;i<10000;i++);
	}
}



// LED Chaser
// **** This Function runs FOREVER!!! ****
// **** Must configure the PORT you use as OUTPUT during SETUP ****
void led_chaser(uint8_t x) // led_chaser(port_name)
{
	while (1)
	{
		for(volatile int i=0;i<8;i++)
		{
			*DAT[x] = (1U<<i);
			delay_y(1);
		}
	}
}