#include "latest.h"
int main()
{
  portf_set(0xFF);
  portk_set(0x00);
  portk_out(0xFF);
  disp_SS(0);
  volatile int a=0;
  //portk_out(0x00);
  while(1)
  {
    while(1)
    {
      if (portk_r()==0b11111110)
    {
      disp_SS(a++);
      delay_y(1);
    }
    else if (portk_r()==0b11111101)
    {
      disp_SS(a--);
      delay_y(1);
    }
    else
    {
      disp_SS(a);
      delay_y(1);
    }
    }
  }
}