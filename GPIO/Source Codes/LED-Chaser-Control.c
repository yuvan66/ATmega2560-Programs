//#include "yuvan.h"
#include "yuvan2.h"
int main()
{
  port_def(0,0xFF,NULL);
  port_def(1,0x00,0xFF);
  // portf_set(0xFF);
  // portk_set(0x00);
  // portk_out(0xFF);
  while (1)
  {
    volatile int i;
    for(i=0;i<8;i++)
    {
      portf_out(1<<i);
      delay_y(1);
      if(portk_rd()==0xFE)
      {
        while (portk_rd()==0xFE)
        {

        }
      }
    }

    // portf_out(0xFF);
    // delay_y(1);
    
    // portf_out(0x00);
    // delay_y(1);
    
  }
}