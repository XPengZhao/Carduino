/*---------------宏定义部分------------------*/
#define Vo 130    // Vo(0-255)
#define k 0.85    // k(0-10)

/*--------------全局变量部分-----------------*/
int IN[5]={-1,3,5,6,9};
int p1,p2,p;
int last_proportional = 0;
long integral = 0;
int proportional,derivative,power_difference;

/*--------------子函数部分-------------------*/

/**
  * 函数readl()用于读取两个传感器的信号差
  * 两个传感器分别接 A5,A6 引脚
  */
int readl()
{
  p1=analogRead(A6);
  p2=analogRead(A5);
  p=p1-p2;
  return p;
}

/**
  * 函数motor(int speed_left,speed_right)用于控制电机转动
  * 右电机接IN1、IN2，对应nano上的 D3、D5 引脚
  * 左电机接IN3、IN4，对应nano上的 D6、D9 引脚
  */
void motor(int speed_left,int speed_right)
{ 
  int s1,s2,s3,s4;
  if(speed_right>0)
  {
    s1=0;
    s2=1;
  }
  else
  {
    s1=1;
    s2=0;
  }
  digitalWrite(IN[s1],LOW);
  analogWrite(IN[s2],abs(speed_right));
  if(speed_left>0)
  {
    s3=2;
    s4=3;
  }
  else{
    s3=3;
    s4=2;
  }
  digitalWrite(IN[s3],LOW);
  analogWrite(IN[s4],abs(speed_left));
}

void pid(int max_speed){
  proportional = readl();
  derivative = proportional-last_proportional;
  integral+= proportional;
  last_proportional = proportional;
  power_difference = proportional*k;// + integral/20000 + derivative*3/4;
//power_difference = proportional*5;
  if(power_difference > max_speed)
    power_difference = max_speed;
  if(power_difference < -max_speed)
    power_difference = -max_speed;
  if(power_difference<0)
    motor((max_speed+power_difference),max_speed);
  else
    motor(max_speed,(max_speed-power_difference));
}
void setup() {
  // put your setup code here, to run once:
  pinMode(IN[0],OUTPUT);
  pinMode(IN[1],OUTPUT);
  pinMode(IN[2],OUTPUT);
  pinMode(IN[3],OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  pid(Vo);
}
