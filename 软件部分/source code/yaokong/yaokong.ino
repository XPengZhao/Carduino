/***************************************************/
/*程序名称：蓝牙避障循迹音乐智能小车               */
/*作    者：孙训                                   */
/*时  间：2015年12月20日                           */
/*硬件连接：看引脚定义部分                         */
/***************************************************/

/*----------可调参数部分---------------------*/ 
int v=150;//蓝牙模式默认中速档 
int safedistance=10;  //默认超声波安全距离10cm

/*----------引脚设置部分---------------------*/ 
int IN[4 ]= {3,5,6,9};  //电机:分别对应IN1，IN2，IN3，IN4  
int inputPin=7;     //echo D7
int outputPin=8;    //trig D8

/*----------蓝牙命令部分---------------------*/ 
#define forward_command  0x00        //前进命令 
#define back_command  0x10        //后退命令 
#define left_command  0x20        //左转命令 
#define right_command 0x30        //右转命令 
#define stop_command  0x40        //停止命令

#define speed_1     0x50        //低速命令
#define speed_2     0x60        //中低速命令
#define speed_3     0x70        //中速命令
#define speed_4     0x80        //中高速命令
#define speed_5     0x90        //高速命令 

 
/*----------函数声明部分---------------------*/
void motor(int speed2,int speed1); //speed1 右轮速度,speed2 左轮速度 
void receive_data(void);          //接收串口命令数据 
float distance(void);            //测距函数
void forward(void);             //前进子函数 
void back(void);                //后退子函数 
void turn_left(void);           //左转子函数 
void turn_right(void);          //右转子函数 
void stop_car(void);      //停止子函数
void bluetoothControl();    //蓝牙控制函数 



/*----------引几个全局变量部分---------------------*/
byte comdata=0;            //定义数组类型，用于存放串口命令数据
int p1,p2,p;//因循迹模式里要经常用到，就定义为全局变量吧 
float IntervalTime;

/*----------arduino主程序部分---------------------*/
void setup() {
  pinMode(IN[0],OUTPUT);
  pinMode(IN[1],OUTPUT);
  pinMode(IN[2],OUTPUT);
  pinMode(IN[3],OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
  motor(0,0); 
}
void loop()
{
    bluetoothControl();
    if(distance()<=safedistance) stop_car();
}

/*----------自写函数部分---------------------*/
float distance(void)
{
  long IntervalTime=0; //定义一个时间变量
 
    digitalWrite(outputPin, 1);//置高电平
    delayMicroseconds(12);//延时12us
    digitalWrite(outputPin, 0);//设为低电平
    IntervalTime=pulseIn(inputPin, 1);//用自带的函数采样反馈的高电平的宽度，单位us
    float S=IntervalTime/58.00; //使用浮点计算出距离，单位cm
    return S;
} 

void motor(int speed2,int speed1){ //speed1 right,speed2 left
  int s1,s2,s3,s4;
  if(speed1>0){
    s1=0;
    s2=1;
  }
  else{
    s1=1;
    s2=0;
  }
  digitalWrite(IN[s1],LOW);
  analogWrite(IN[s2],abs(speed1));
  if(speed2>0){
    s3=2;
    s4=3;
  }
  else{
    s3=3;
    s4=2;
  }
  digitalWrite(IN[s3],LOW);
  analogWrite(IN[s4],abs(speed2));
}

void bluetoothControl()
{
  if(Serial.available()>0){
    receive_data();           //接收串口命令数据 
  }
}

void receive_data(void)           //接收串口命令数据
{
    comdata=Serial.read();
    delay(2);//让串口缓存准备好下一个字节，不延时可能会导致数据丢失 
    switch (comdata){
        case forward_command: forward();    break;//前进命令 
        case back_command:    back();       break;//后退命令
        case left_command:    turn_left();  break;//左转命令
        case right_command:   turn_right(); break;//右转命令
        case stop_command:    stop_car();   break;//停止命令
        
        case speed_1:v=v<0?-50:50;motor(v,v);break;//低速命令 
        case speed_2:v=v<0?-100:100;motor(v,v);break;//中低速命令 
        case speed_3:v=v<0?-150:150;motor(v,v);break;//中速命令 
        case speed_4:v=v<0?-200:200;motor(v,v);break;//中高速命令 
        case speed_5:v=v<0?-250:250;motor(v,v);break;//高速命令 
      }
}

void forward(void)              //前进 
{
  v=abs(v); 
  motor(v,v); 
}

void back(void)               //后退 
{
  v=-abs(v);
  motor(v,v); 
}

void turn_left(void)              //左转 
{
  motor(-v,v); 
 delay(10000/abs(v));
 motor(v,v); 
}

void turn_right(void)             //右转 
{
  motor(v,-v); 
  delay(10000/abs(v));
  motor(v,v); 
}

void stop_car(void)
{
  motor(0,0); 
}

