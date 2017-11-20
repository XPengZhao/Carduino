/*---------------宏定义部分------------------*/
#define Vo 130    // Vo(0-255)
#define k 0.85    // k(0-10)

/*--------------全局变量部分-----------------*/
int IN[5]={-1,3,5,6,9};
int Signal_left,Signal_right,p;
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
  Signal_left=analogRead(A6);
  Signal_right=analogRead(A5);
  p=Signal_left-Signal_right;
  return p;
}

/**
  * 函数motor(int speed_left,speed_right)用于控制电机转动
  * 右电机接IN1、IN2，对应nano上的 D3、D5 引脚
  * 左电机接IN3、IN4，对应nano上的 D6、D9 引脚
  * speed的范围为 -255~+255
  */
void motor(int speed_left,int speed_right)
{ 
  if(speed_right>0)
  {
    digitalWrite(IN[1],LOW);
    analogWrite(IN[2],speed_right);
  }
  else
  {
    digitalWrite(IN[2],LOW);
    analogWrite(IN[1],-speed_right);
  }

  if(speed_left>0)
  {
    digitalWrite(IN[3],LOW);
    analogWrite(IN[4],speed_left);
  }
  else
  {
    digitalWrite(IN[4],LOW);
    analogWrite(IN[3],-speed_left);
  }
}


void p_concrol(int inital_speed)
{
  proportional = readl();
  power_difference = proportional*k;
  if(power_difference > inital_speed)
    power_difference = inital_speed;
  if(power_difference < -inital_speed)
    power_difference = -inital_speed;
    
  if(power_difference<0)
    motor((inital_speed+power_difference),inital_speed);
  else
    motor(inital_speed,(inital_speed-power_difference));
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IN[1],OUTPUT);
  pinMode(IN[2],OUTPUT);
  pinMode(IN[3],OUTPUT);
  pinMode(IN[4],OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  pid(Vo);
}
