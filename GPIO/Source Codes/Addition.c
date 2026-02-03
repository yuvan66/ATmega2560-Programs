#include "latest.h"
int main()
{
  porta_set(0xFF);
  portf_set(0x00);
  portk_set(0xFF);
  portc_set(0xFF);
  portd_set(0xFF);

  int keypad[4][4] = {
  { 1, 2, 3, '+' },
  { 4, 5, 6, '-' },
  { 7, 8, 9, '=' },
  { 0, 0, 0, '/' }
};

int a,s,f=0;

  while (1)
  {
    loop: for (int i=0;i<4;i++)
    {
      portk_out(1<<i);
      porta_out(portf_r());
      if (portf_r()!=0)
      {
        portc_out(1<<i);
        a = portf_r();
        if(portf_r()==8)
        {
          a--;
        }
        if (keypad[i][a/2]=='+')
        {
          f = 1;
          goto loop;
        }
        if (f)
        {
          int res = keypad[i][a/2]+s;
          int co=0;
          while(co<20000)
          {
            disp_SS(res%10);
            portd_out(0x01);
            portd_out(0x03);
            disp_SS((res/10)%10);
            portd_out(0x02);
            portd_out(0x03);            
          }
          disp_SS(res);
          continue;
        }

        disp_SS(keypad[i][a/2]);
        s = keypad[i][a/2];
        f = 0;
        
        delay_y(4);
        portc_out(0);
      }
    }
  }
}
// int b = keypad[i][a/2];
        // for (int j=0;j<4;j++)
        // {
        //   portk_out(1<<i);
        //   porta_out(portf_r());
        //   if (portf_r()!=0)
        //   {
        //     a = portf_r();
        //     if (i==0 && portf_r()==8)
        //     {
        //       for (int k=0;k<4;k++)
        //       {
        //         portk_out(1<<i);
        //         porta_out(portf_r());
        //         if (portf_r()==8)
        //         {
        //           a--;
        //         }
        //         disp_SS(b + keypad[k][a/2]);
        //       }
        //     }
        //   }
        // }