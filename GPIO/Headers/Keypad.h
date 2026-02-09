#include "GPIO.h"



/******                This Library contains functions to scan a 4x4 Keypad and Returns 
                             scanned Position's Value from the keypad[][] Array                       ******/


                  /****** Feel free to modify the keypad[][] array to suit your needs ******/     
                  
                  /****** Here, ROWS are used as INPUTS and COLUMNS are used as OUTPUTS ******/
                  
                           /****** MUST PULL-DOWN the ROW Pins EXTERNALLY! ******/
                  

const int keypad[4][4] = {
	{ 1, 2, 3, 0 },
	{ 4, 5, 6, 0 },
	{ 7, 8, 9, 0 },
	{ 0, 0, 0, 0 }
};


// Function to Scan the Keypad and Return the Scanned Position's Value from the keypad[][] Array
// ***MUST CONFIGURE the PORTS that is used during the SETUP
uint8_t kp_scan(uint8_t x, uint8_t y)// kp_scan(row_port, column_port)
{
	int b;
	while(1)
	{
		for (int i=0;i<4;i++)
		{
			*DAT[y] = (1<<i);
			if (*RD[x]!=0x00)
			{
				b = *RD[x];
				if(*RD[x]==8)
				{
					b--;
				}
				return keypad[i][b/2];
			}
		}
	}
}