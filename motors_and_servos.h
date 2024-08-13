// khai báo các thư viện cần sử dụng
#pragma once
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>// Thư viện PCA9685
#include <PS2X_lib.h>// Thư viện PS2

// Khai báo các chân servo và động cơ 
// PWM channels of pca9685 2, 5-15
#define DC1_chan1 8
#define DC1_chan2 9
#define DC2_chan1 10
#define DC2_chan2 11
#define DC3_chan1 12
#define DC3_chan2 13
#define DC4_chan1 14
#define DC4_chan2 15
#define S360MO_chan 7
#define S360PU_chan 6
#define S180DE_chan 5
#define S180OP_chan 2
//Khai báo clas với của thư viện với địa chỉ gốc
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x70);
void setupMotors() // hàm kết nối động cơ với mạch
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
  // bắt đầu: cho các động cơ không chạy
  pwm.setPWM(DC1_chan1, 0, 0);
  pwm.setPWM(DC1_chan2, 0, 0);
  pwm.setPWM(DC2_chan1, 0, 0);
  pwm.setPWM(DC2_chan2, 0, 0);
  pwm.setPWM(DC3_chan1, 0, 0);
  pwm.setPWM(DC3_chan2, 0, 0);
  pwm.setPWM(DC4_chan1, 0, 0);
}

void DC1(int LY_1, int LY_2) // hàm điểu khiển DC1 (động cơ di chuyển bên trái)
{ 
   pwm.setPWM(DC1_chan1, 0, LY_1);
   pwm.setPWM(DC1_chan2, 0, LY_2);
}

void DC2(int RY_1, int RY_2) // hàm điểu khiển DC2 (động cơ di chuyển bên phải)
{
   pwm.setPWM(DC2_chan1, 0, RY_1);
   pwm.setPWM(DC2_chan2, 0, RY_2);
} 

void DC3(int R_1, int R_2) // hàm điểu khiển DC3 (động cơ intake)
{ 
   pwm.setPWM(12, 0, R_1);
   pwm.setPWM(13, 0, R_2);
    delay(50);
}

void DC4(int quay) // hàm điểu khiển DC4 (động cơ bắn bóng)
{
    pwm.setPWM(14, 0, quay);
    pwm.setPWM(15, 0, 0);
}

void setupServo() // hàm kết nối servo với mạch
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
}

void S360_MO(int move) // hàm điểu khiển S360MO (servo di chuyển ngang)
{
    pwm.setPWM(S360MO_chan, 0, move);
    delay(50);
}

void S180_OP(int open) // hàm điểu khiển S180OP (servo mở/đóng cổng thoát chất thải)
{
    pwm.writeMicroseconds(S180OP_chan, open);
    delay(50);
}
  
void S180_DE( int deviced) // hàm điều khiển S180DE  (servo chia bóng)
{
    pwm.writeMicroseconds(S180DE_chan, deviced);
    delay(50);
}

void S360_PU( float push) // hàm điểu khiển S360PU (servo đẩy bóng)
{
    pwm.setPWM(S360PU_chan, 0, push);
    delay(50);
}
