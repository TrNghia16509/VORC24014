#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>

#define MIN_PWM 0
#define MAX_PWM 4095

//#define SDA 3
//#define SCL 0
// PWM channels of pca9685 0-16
#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11
#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setupMotors()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPAD);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
}

  void DC1()
  {
   pwm.setPWM(8, 0, 0);
   pwm.setPWM(9, 0, 0);
  }

  void DC1_forward(int LY)
  {
   pwm.setPWM(8, 0, LY);
   pwm.setPWM(9, 0, 0);
  }

  void DC1_backward(int LY)
  {
   pwm.setPWM(8, 0, 0);
   pwm.setPWM(9, 0, LY);
  }

  void DC2()
  {
   pwm.setPWM(10, 0, 0);
   pwm.setPWM(11, 0, 0);
  } 

  void DC2_forward(int RY)
  {
   pwm.setPWM(10, 0, RY);
   pwm.setPWM(11, 0, 0);
  }

  void DC2_backward(int RY)
  {
   pwm.setPWM(10, 0, 0);
   pwm.setPWM(11, 0, RY);
    delay(500);
  }

  void DC3()
  { 
   pwm.setPWM(12, 0, 0);
   pwm.setPWM(13, 0, 0);
    delay(500);
  }

  void DC3_in()
  {
   pwm.setPWM(12, 0, 2048);
   pwm.setPWM(13, 0, 0);
   delay(500);
  }

  void DC3_out()
  {
   pwm.setPWM(12, 0, 0);
   pwm.setPWM(13, 0, 2048);
   delay(500);
  }

  void DC4(int quay)
  {
    pwm.setPWM(14, 0, quay);
    pwm.setPWM(15, 0, 0);
  }
// /**
//  * Set speed and direction for 2 motors
//  *
//  * @param left_motor_speed: speed with direction for left motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
//  * @param right_motor_speed: speed with direction for right motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
//  */
// void setSpeed(float left_motor_speed, float right_motor_speed) {

//   int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

//   if (left_motor_speed > 0) {
//     c1 = max(MIN_PWM, min(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
//   } else {
//     c2 = max(MIN_PWM, min(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
//   }

//   if (right_motor_speed > 0) {
//     c3 = max(MIN_PWM, min(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
//   } else {
//     c4 = max(MIN_PWM, min(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
//   }

//   setPWMMotors(c1, c2, c3, c4);
// }
