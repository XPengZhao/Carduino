char rx_buff[4];
void setup()
{
  serial.begin(9600);
}
void loop()
{
  if(serial.available()>0)
  {
    serial.readBytes(rx_buff,4);
  }
}