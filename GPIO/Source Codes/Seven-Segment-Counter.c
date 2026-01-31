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
          // portk_set(0b00000001);    --This commented set of lines had a major electrical issue causing Direction Register 
          // portk_out(0x01);          to change at very high speed, leading to malfunctioning of the Register.
          // disp_SS(i);               So, these are changed as below to set the Direction Register 
          // portk_set(0b00000010);    only once at the start of the program.--
          // portk_out(0x02);
          // disp_SS(j);

          // Updated lines
          disp_SS(i);                  //Value for first digit               
          portk_out(0x01);             //Activate first digit
          portk_out(0x03);             //Turn off both digits
          disp_SS(j);                  //Value for second digit
          portk_out(0x02);             //Activate second digit
          portk_out(0x03);             //Turn off both digits
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