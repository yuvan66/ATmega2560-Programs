#include "latest.h"
int main ()
{
  portf_set(0xFF);
  portk_set(0xF0);
  portk_out(0x0F);

  int a=0;
  disp_SS(0);
  int b[4] = {0x1F,0x2F,0x4F,0x8F};
  portk_out(b[0]);

  while (1)
  {


    // Ground floor (0)
    if ((portk_rd()&0x0F)==0b00000111)
    {
      if (a>0)
      {
      for (int i=a;i>0;i--)
      {
        a--;
        disp_SS(a);
        portk_out(b[a]);
        //portk_out(0x1F);
        delay_y(4);
      }
      }
      // a = 0;
      disp_SS(0);
      portk_out(b[0]);
    }


    // First floor (1)
    if ((portk_rd()&0x0F)==0b00001011)
    {
      if (a>1)
      {
      for (int i=a;i>1;i--)
      {
        a--;
        disp_SS(a);
        portk_out(b[a]);
        // portk_out(0x2F);
        delay_y(4);
      }
      }
      a = 1;
      disp_SS(1);
      portk_out(b[1]);
    }


    // Second floor (2)
    if ((portk_rd()&0x0F)==0b00001101)
    {
      if (a<2)
      {
        for (int i=a;i<2;i++)
        {
          a++;
          disp_SS(a);
          portk_out(b[a]);
          // portk_out(0x4F);
          delay_y(4);
        }
      }
      a = 2;
      disp_SS(2);
      portk_out(b[2]);
    }


    // Third floor (3)
    if ((portk_rd()&0x0F)==0b00001110)
    {
      
      // delay_y(2);
      if (a<3)
      {
        for (int i=a;i<3;i++)
        {
          a++;
          disp_SS(a);
          portk_out(b[a]);
          // portk_out(0x8F);
          delay_y(4);
        }
      }
      a = 3;
      disp_SS(3);
      portk_out(b[3]);
    }
  }
}