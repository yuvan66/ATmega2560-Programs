#define porta_dir (*(volatile uint8_t *)0x21)
#define porta_dat (*(volatile uint8_t *)0x22)
#define portb_dir (*(volatile uint8_t *)0x24)
#define portb_dat (*(volatile uint8_t *)0x25)
#define portc_dir (*(volatile uint8_t *)0x27)
#define portc_dat (*(volatile uint8_t *)0x28)
#define portd_dir (*(volatile uint8_t *)0x2A)
#define portd_dat (*(volatile uint8_t *)0x2B)
#define portf_dir (*(volatile uint8_t *)0x30)
#define portf_dat (*(volatile uint8_t *)0x31)
#define portk_dir (*(volatile uint8_t *)0x107)
#define portk_dat (*(volatile uint8_t *)0x108)
//#define portk_rd (*(volatile uint8_t *)0x106)


// PORTA __--__ Functions __--__ DIR,DAT,RD
void porta_set(uint8_t adir) //set direction to PORTA
{
  porta_dir = adir;
}

void porta_out(volatile uint8_t adat) //ouput data for PORTA
{
  porta_dat = adat;
}

uint8_t porta_r() //func. to return PORTA input data
{
  volatile uint8_t *porta_rd;
  porta_rd = 0x20;
  return (*porta_rd);
}


// PORTB __--__ Functions __--__ DIR,DAT,RD
void portb_set(uint8_t bdir) //set direction to PORTB
{
  portb_dir = bdir;
}

void portb_out(volatile uint8_t bdat) //ouput data for PORTB
{
  portb_dat = bdat;
}

uint8_t portb_r() //func. to return PORTB input data
{
  volatile uint8_t *portb_rd;
  portb_rd = 0x20;
  return (*portb_rd);
}


// PORTC __--__ Functions __--__ DIR,DAT,RD
void portc_set(uint8_t cdir) //set direction to PORTC
{
  portc_dir = cdir;
}

void portc_out(volatile uint8_t cdat) //ouput data for PORTC
{
  portc_dat = cdat;
}

uint8_t portc_r() //func. to return PORTC input data
{
  volatile uint8_t *portc_rd;
  portc_rd = 0x26;
  return (*portc_rd);
}


// PORTD __--__ Functions __--__ DIR,DAT
void portd_set(uint8_t ddir) //set direction to PORTD
{
  portd_dir = ddir;
}

void portd_out(volatile uint8_t ddat) //ouput data for PORTD
{
  portd_dat = ddat;
}


// PORTF __--__ Functions __--__ DIR,DAT,Seven-Segment
void portf_set(uint8_t fdir) //set direction to PORTF
{
  portf_dir = fdir;
}

void portf_out(volatile uint8_t fdat) //ouput data for PORTF
{
  portf_dat = fdat;
}

uint8_t portf_r() //func. to return PORTK input data
{
  volatile uint8_t *portf_rd;
  portf_rd = 0x2F;
  return (*portf_rd);
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

uint8_t portk_r() //func. to return PORTK input data
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


void disp_SS (volatile uint8_t x)
{
  volatile uint8_t a[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
  portb_dat = a[x];
  //return a[x];
}

void count(double x)
{
  for (int i=0;i<10;i++)
    {
      for (int j=0;j<10;j++)
      {
        long int a = 0;
        while(a<(x*10000))
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
}