/*---------------宏定义部分----------------*/
#define SPEED_LEFT 150
#define SPEED_RIGHT 150

/*--------------全局变量部分---------------*/
int IN[5]={-1,3,5,6,9};

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

