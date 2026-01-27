#define portf_dir (*(volatile uint8_t *)0x30)
#define portf_dat (*(volatile uint8_t *)0x31)
#define portk_dir (*(volatile uint8_t *)0x107)
#define portk_dat (*(volatile uint8_t *)0x108)
//#define portk_rd (*(volatile uint8_t *)0x106)


// PORTF __--__ Functions __--__ DIR,DAT,Seven-Segment
void portf_set(uint8_t fdir) //set direction to PORTF
{
  portf_dir = fdir;
}

void portf_out(volatile uint8_t fdat) //ouput data for PORTF
{
  portf_dat = fdat;
}

uint8_t disp_SS (volatile uint8_t x)
{
  volatile uint8_t a[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
  portf_dat = a[x];
  //return a[x];
}


// PORTK __--__ Functions __--__ DIR,DAT,PIN
void portk_set(uint8_t kdir) //set direction to PORTK
{
  portk_dir = kdir;
}

void portk_out(volatile uint8_t kdat) //ouput data for PORTK
{
  portk_dat = kdat;
}

uint8_t portk_rd() //func. to return PORTK input data
{
  volatile uint8_t *portk_rd;
  portk_rd = 0x106;
  return (*portk_rd);
}



//Additional Functions__--__Additional Functions __--__ Delay
void delay_y(uint8_t x)
{
  volatile long i;
  for (i=0;i<100000*x;i++); 
}

void l2r() // led chaser left-to-right for PORTF
{
  volatile int i;
    for(i=0;i<8;i++)
    {
      portf_out(1<<i);
      delay_y(1);
    }
}

void r2l() // led chaser right-to-left for PORTF
{
  volatile int i;
    for(i=6;i>=0;i--)
    {
      portf_out(1<<i);
      delay_y(1);
    }
}