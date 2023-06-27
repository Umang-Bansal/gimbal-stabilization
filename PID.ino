#include "mylib.h"
#include<Servo.h>

float kp = 0.2, Kp = 0.2;
float kd = 0.3, Kd = 0.3;
float ki = 0.01, Ki = 0.01;

float setPoint = 90, setPointPitch = 90;
float lastError = 0, lastErrorPitch = 0;
float errSum = 0, errSumPitch = 0;

Servo servoRoll, servoPitch;

void setup(){
  Serial.begin(115200);
  servoRoll.attach(8);
  servoPitch.attach(9);
  servoRoll.write(90);
  servoPitch.write(90);
  
  while(!Serial.available())
  {
  
  }
  
  mylib.MPU6050Setup();
}

void loop(){

  float *YPR = mylib.MPU6050Loop();
  float feedBack, feedBackPitch;
  float err, errPitch;
  float errProportional, errDerivative, errIntegral;
  float PID_Out, PID_OutPitch;
  
  feedBack = ((YPR[1]+0.83)/1.66)*180;


  err = setPoint - feedBack;



  errProportional = kp*err;

  errDerivative = kd*(err - lastError);
  lastError = err;

  errSum += err;
  errIntegral = ki*errSum;

  
  PID_Out = errProportional + errDerivative + errIntegral;

                     
  feedBackPitch = ((YPR[2]+0.83)/1.66)*180;

  errPitch = setPointPitch - feedBackPitch;

  errProportional = Kp*errPitch;
                    
  errDerivative = Kd*(errPitch - lastErrorPitch);
  lastErrorPitch = errPitch;                    
                    
  errSumPitch += errPitch;
  errIntegral = Ki*errSumPitch;
                    
  
  PID_OutPitch = errProportional + errDerivative + errIntegral;
  
  if(PID_Out < 0){
    increaseAngleRoll(PID_Out);
  }
  else if(PID_Out > 0){
    decreaseAngleRoll(PID_Out);
  } 

  if(PID_OutPitch > 0){
  increaseAnglePitch(PID_OutPitch);
  }
  else if(PID_OutPitch < 0){
  decreaseAnglePitch(PID_OutPitch);
  } 

  delay(20);
  }

void increaseAngleRoll(float x){
  servoRoll.write(servoRoll.read() + fabs(x));
}

void decreaseAngleRoll(float x){
  servoRoll.write(servoRoll.read() - fabs(x));
}
void increaseAnglePitch(float x){
servoPitch.write(servoPitch.read() + fabs(x));
}
void decreaseAnglePitch(float x){
servoPitch.write(servoPitch.read() - fabs(x));
}
