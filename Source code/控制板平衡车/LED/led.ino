#define LOW_TRANS 20
#define HIGH_TRANS 70
byte rxdata_roll=0;
byte rxdata_pitch=0; 

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);          // sets the digital pin 13 as output
}

void loop()
{
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(1000);
}
