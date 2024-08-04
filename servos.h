#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>
#include <Servo.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Servo S360PU
Servo S360MO
Servo S180DE
Servo S180OP
void setupServo()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
  S360PU.attach(J6); 
  S360MO.attach(J7);
  S180DE.attach(J5); 
  S180OP.attach(J2);
}

  void S360_MO(int move)
  {
    pwm.setPWM(7, 0, move);
    delay(500);
  }

  void S180_OP(int open)
  {
    S180OP.write(open);
    delay(500);
  }
  
  void S180_DE( int deviced)
  {
    S180DE.write(deviced);
    delay(500);
  }

  void S360_PU( float push)
  {
    S360PU.write(push);
  }