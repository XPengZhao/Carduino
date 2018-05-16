

#include "BalanceCar.h"

//////////////////速度PI////////////////////
double BalanceCar::speedpiout(double kps,double kis,double kds,int f,int b,double p0)
{
  float speeds = (pulseleft + pulseright) * 1.0;                                                                 //车速 脉冲值
  pulseright = pulseleft = 0;
  speeds_filterold *= 0.7;                                                                     //一阶互补滤波
  float speeds_filter = speeds_filterold + speeds * 0.3;
  speeds_filterold = speeds_filter;
  positions += speeds_filter;
  positions += f;                                                                         //全进控制量融合
  positions += b;                                                                         //全进控制量融合
  positions = constrain(positions, -4550,4550); //抗积分饱和
  double output = kis * (p0 - positions) + kps * (p0 - speeds_filter);                      //速度环控制 PI
  if(flag1==1)
  {
  positions=0;
  }
  
  return output;
}
//////////////////速度PI////////////////////

float BalanceCar::turnspin(int turnleftflag,int turnrightflag,int spinleftflag,int spinrightflag,double kpturn,double kdturn,float Gyroz)
{
  int spinonce = 0;
  float turnspeed = 0;
	float rotationratio = 0;
   float turnout_put = 0;
	
  if (turnleftflag == 1 || turnrightflag == 1 || spinleftflag == 1 || spinrightflag == 1)
  {
    if (spinonce == 0)                             //旋转前判断当前车速，增强小车适应性。
    {
      turnspeed = ( pulseright + pulseleft);                      //小车当前车速 脉冲表示
	  spinonce++;
    }

    if (turnspeed < 0)                                 //小车当前速度绝对值
    {
      turnspeed = -turnspeed;

    }
    if(turnleftflag==1||turnrightflag==1)
    {
     turnmax=5;
     turnmin=-5;
    }
    if(spinleftflag==1||spinrightflag==1)
    {
      turnmax=10;
      turnmin=-10;
    }
    rotationratio = 55 / turnspeed;                        //根据小车速度设定值
    if (rotationratio < 0.5)rotationratio = 0.5;
    if (rotationratio > 5)rotationratio = 5;
  }
  else
  {
    rotationratio = 0.5;
    spinonce = 0;
    turnspeed = 0;
  }
  if (turnleftflag == 1 || spinleftflag == 1)//根据方向参数叠加
  {
    turnout += rotationratio;
  }
  else if (turnrightflag == 1 || spinrightflag == 1)//根据方向参数叠加
  {
    turnout -= rotationratio;
  }
  else turnout = 0;
  if (turnout > turnmax) turnout = turnmax;//幅值最大值设置
  if (turnout < turnmin) turnout = turnmin;//幅值最小值设置

  turnout_put = -turnout * kpturn - Gyroz * kdturn;//旋转PD算法控制 融合速度和Z轴旋转定位。
	return turnout_put;
}

void BalanceCar::pwma(double speedoutput,float rotationoutput,float angle,float angle6,int turnleftflag,int turnrightflag,int spinleftflag,int spinrightflag,
	int f,int b,float accelz,int Pin1,int Pin2,int Pin3,int Pin4,int PinPWMA,int PinPWMB)
{

  pwm1 = -angleoutput - speedoutput - rotationoutput; //Left电机PWM输出值
  pwm2 = -angleoutput - speedoutput + rotationoutput;//Right电机PWM输出值

  //幅度值限制
  if (pwm1 > 255) pwm1 = 255;
  if (pwm1 < -255) pwm1 = -255;
  if (pwm2 > 255) pwm2 = 255;
  if (pwm2 < -255) pwm2 = -255;


  //角度过大，停止电机
  if (angle > 30 || angle < -30)
  {
    pwm1 = 0;
    pwm2 = 0;
  }
  //

 
//    if (posture > 10 & turnleftflag == 0 & turnrightflag == 0 & spinleftflag == 0 & spinrightflag == 0 && f == 0 && b == 0) //50ms检测是否悬空
//    {
//  
//      if  ((pulseright + pulseleft ) > -2 && (pulseright + pulseleft) < 2)
//      {
//        flag1 = 1;
//      }
//      if (flag1 == 1 )
//      {
//  
//          if (angle > -0.3 && angle < 0.3 && accelz > 1300)
//          {
//            flag2 = 1;
//          }
//  
//        else flag1 = 0;
//      }
//      if (flag2 == 1)
//      {
//        if (((stopl + stopr) > 2800) || ((stopl + stopr) < -2800))
//        {
//          flag3 = 1;
//        }
//      }
//      if (flag3 == 1)
//      {
//        pwm1 = 0;
//        pwm2 = 0;
//  
//        flag4 = 1;
//      }
//    }
//  
//  
//  
//    if (posture > 100)
//    {
//  
//      if (flag4 == 1)
//      {
//        if (pulseright == 0 && pulseleft == 0)
//        {
//  
//          flag4 = 2;
//          pulseright = pulseleft = 0;
//  
//        }
//      }
//  
//      if (flag4 == 2)
//      {
//        if ((pulseleft < 2 ) && ( pulseright < 2) && accelz > 1500) //&&BLANACECAR.pulseleft<-2&&BLANACECAR.pulseright<-2 )
//        {
//          stopl = stopr = 0;
//          pwm1 = pwm2 = 0;
//  
//          posture = 0;
//          flag4 = 0;
//          flag1 = 0;
//          flag2 = 0;
//          flag3 = 0;
//        }
//  
//      }
//		}

		  if (angle6 > 3 || angle6 < -3 &&turnleftflag == 0 && turnrightflag == 0 && spinleftflag == 0 && spinrightflag == 0 && f == 0 && b == 0)
  {
           if(stopl + stopr > 1500||stopl + stopr <- 1500)
   {
    pwm1 = 0;
    pwm2 = 0;
	flag1=1;

	}
  }
  else 
  {
   stopl=stopr=0;
   flag1=0;

  }



//电机的正负输出判断        左电机判断
if (pwm1 >= 0) {
  digitalWrite(Pin2, 0);
  digitalWrite(Pin1, 1);
  analogWrite(PinPWMA, pwm1);
} else {
  digitalWrite(Pin2, 1);
  digitalWrite(Pin1, 0);
  analogWrite(PinPWMA, -pwm1);
}
//电机的正负输出判断        右电机判断
if (pwm2 >= 0) {
  digitalWrite(Pin4, 0);
  digitalWrite(Pin3, 1);
  analogWrite(PinPWMB, pwm2);
} else {
  digitalWrite(Pin4, 1);
  digitalWrite(Pin3, 0);
  analogWrite(PinPWMB, -pwm2);
}

}