void init_port();
char output();
void delay_y();
void init_port()
{
  volatile char* portf_dir;
  portf_dir = 0x30;
  *portf_dir = 0xFF;
}

char output (char out_data)
{
  volatile char* portf_data;
  portf_data = 0x31;
  *portf_data = out_data;
}

void delay_y(int a)
{
  volatile long i;
  for (i=0;i<a*100000;i++);
}