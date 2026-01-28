#include "latest.h"
int main()
{
  portf_set(0xFF);
  portk_set(0xFF);
  //portk_out(0x00);
  while(1)
  {
    portk_out(0x00);

    for (int i=0;i<10;i++)
    {
      for (int j=0;j<10;j++)
      {
        long int a = 0;
        while(a<40000)
        {
          portk_set(0b00000001);
          portk_out(0x01);
          disp_SS(i);
          portk_set(0b00000010);
          portk_out(0x02);
          disp_SS(j);
          a++;
        }
      }
    }

    // count(2);
    
  }  
}
// for (int i=0;i<10;i++)
    // {
    //   for (int j=0;j<10;j++)
    //   {
    //     disp_SS(i);

    //     delay_y(1);
    //   }
    // }
    // for (int8_t i=0;i<10;i++)
    // {
    //   disp_SS(i);
    //   delay_y(4);
    // }