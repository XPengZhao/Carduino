#define LOW_TRANS 20
#define HIGH_TRANS 70
byte rxdata_roll=0;
byte rxdata_pitch=0;
void setup()
{
  serial.begin(9600);
}
void loop()
{
  if(serial.available()>0)
  {
    rxdata_roll=serial.read();
    delay(2);
    rxdata_pitch=serial.read();
    delay(2);
    if(rxdata_roll>0x7f)
    {
      rxdata_roll-=0xff;
    }
    if(rxdata_pitch>0x7f)
    {
      rxdata_roll-=0xff;
    }
    if((rxdata_roll>=-LOW_TRANS&&rxdata_roll<=LOW_TRANS))
    {
      rxdata_roll=0;
    }
    if((rxdata_roll>=HIGH_TRANS))
    {
      rxdata_roll=HIGH_TRANS;
    }
    if((rxdata_roll<=-HIGH_TRANS))
    {
      rxdata_roll=-HIGH_TRANS;
    }

     if((rxdata_pitch>=-LOW_TRANS&&rxdata_pitch<=LOW_TRANS))
    {
      rxdata_pitch=0;
    }
    if((rxdata_ritch>=HIGH_TRANS))
    {
      rxdata_pitch=HIGH_TRANS;
    }
    if((rxdata_pitch<=-HIGH_TRANS))
    {
      rxdata_pitch=-HIGH_TRANS;
    }
  }
}