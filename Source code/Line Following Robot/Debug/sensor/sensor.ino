void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int p1=0,p2=0;
  p1=analogRead(A6);
  p2=analogRead(A5);
  Serial.print(p1,OCT);
  Serial.print("\t");
  Serial.println(p2,OCT);
  delay(100);
}
