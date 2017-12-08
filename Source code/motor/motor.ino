/*---------------宏定义部分----------------*/
#define SPEED_LEFT 50
#define SPEED_RIGHT 50

/*--------------全局变量部分---------------*/
int IN[5]={-1,3,5,6,9};
int A5=5,A6=6;

/*-------------子函数部分------------------*/

/**
  * D3 D5引脚控制左电机     D3-->0  D5-->1正转
  * D6 D9引脚控制右电机     D6-->0  D9-->1正转
  */
void motor(int speed_left,int speed_right)
{ 
  if(speed_left>0)
  {
    digitalWrite(IN[1],LOW);
    analogWrite(IN[2],speed_left);
  }
  else
  {
    digitalWrite(IN[2],LOW);
    analogWrite(IN[1],-speed_left);
  }

  if(speed_right>0)
  {
    digitalWrite(IN[3],LOW);
    analogWrite(IN[4],speed_right);
  }
  else
  {
    digitalWrite(IN[4],LOW);
    analogWrite(IN[3],-speed_right);
  }
}

/**
  * 该函数通过模拟引脚读取输出的模拟量。
  */
void signal_read(void)
{
  int data1=0,data2=0;
  data1=analogRead(A5);
  data2=analogRead(A6);
  Serial.println(data1);
  Serial.println(data2);
}


void setup()
{
  pinMode(IN[1],OUTPUT);
  pinMode(IN[2],OUTPUT);
  pinMode(IN[3],OUTPUT);
  pinMode(IN[4],OUTPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  Serial.begin(9600);
}

void loop()
{
  motor(SPEED_LEFT,SPEED_RIGHT);
  delay(100);
  signal_read();
}

