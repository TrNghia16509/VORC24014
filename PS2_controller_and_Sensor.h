//khai báo hàm cần dùng 
#pragma once
#include <PS2X_lib.h>
#include "motors_and_servos.h"
#include <Adafruit_Sensor.h>// Thư viện cảm biến
#include <Adafruit_TCS34725.h>// Thư viện cảm biến màu sắc TCS34725
#include <Wire.h>

PS2X ps2x; // create PS2 Controller Class

#define PS2_DAT 12 // MISO  19
#define PS2_CMD 13 // MOSI  23
#define PS2_SEL 15 // SS     5
#define PS2_CLK 14 // SLK   18

void setupPS2controller() // hàm kết nối tay cầm PS2 với mạch
{
  int err = -1;
  while (err != 0){
  err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
}
bool PS2control_loop() // hàm sử dụng tay cầm PS2 để điều khiển
{
  
  ps2x.read_gamepad(false,false);

  int nJoyLY = ps2x.Analog(PSS_LY); // đọc giá trị trục Oy của joystick bên trái
  int nJoyRY = ps2x.Analog(PSS_RY); // đọc giá trị trục Oy của joystick bên phải

  // chuyển đổi giá trị trục Oy của các joystick thành giá trị xung
  // set map ngược để động cơ 2 xoay ngược
  nJoyLY = map(nJoyLY, 0, 256, -4092, 4092);
  nJoyRY = map(nJoyRY, 0, 256, 4092, -4092);
  // điểu khiển DC1 với giá trị trục Oy của joystick bên trái
  if (nJoyLY>0)
  {
    DC1(nJoyLY, 0);
    delay(50);
  }
  else if (nJoyLY<0)
  {
    DC1(0, nJoyLY);
    delay(50);
  }
  else { DC1(0, 0);
  delay(50);}

 // điểu khiển DC2 với giá trị trục Oy của joystick bên phải
  if (nJoyRY>0)
  {
    DC2(nJoyRY, 0);
    delay(50);
  }
  else if (nJoyRY<0)
  {
    DC2(0, nJoyRY);
    delay(50);
  }
  else { DC2(0, 0);
  delay(50);}

  // điểu khiển S360MO bằng nút hình tròn và nút sang trái
  // hình tròn: sang phải; nút sang trái: sang trái
  if (ps2x.Button(PSB_CIRCLE))
  {
    S360_MO(4096);
    delay(50);
  }
  else if (ps2x.Button(PSB_PAD_LEFT))
  {
    S360_MO(0);
    delay(50);
  }
  else {S360_MO(2048);}

  // điểu khiển DC3 bằng RB và RT (ấn 1 lần sẽ quay và ấn lần nữa sẽ dừng)
  // RB: DC3 quay theo chiều thuận; RT: DC3 quay theo chiều ngược
  if (ps2x.NewButtonState(PSB_R2))
  {
    DC3(2048, 0);
    delay(50);
  }
  else if (ps2x.NewButtonState(PSB_R2))
  {
    DC3(0, 0);
    delay(50);
  }

  if (ps2x.NewButtonState(PSB_R1))
  {
    DC3(0 ,2048);
    delay(50);
  }
  else if (ps2x.NewButtonState(PSB_R1))
  { DC3(0, 0);
  delay(50);
  }

//điểu khiển S180_OP bằng LB
//nếu được nhấn thì mở cổng ngược lại thì đóng cổng
  if (ps2x.ButtonPressed(PSB_L2))
  {
    S180_OP(1500);
  }
  else 
  {
    S180_OP(1000);
  }

 // điểu khiển DC4 bằng LT
 // nếu giá trị của LT lớn hơn 2048 thì bắn bóng theo độ mạnh của lực nhấn vào LT ngược lại thì đứng yên
  int nTrigL = ps2x.Analog(PSB_L1);
  nTrigL = map(nTrigL, 0 ,255, 0, 4096);
  if (nTrigL > 2048)
  {
    DC4(nTrigL);
  }
  else DC4(0);

 // điểu khiển S360PU bằng nút hình tam giác 
 // nếu nút tam giác được nhấn thì đẩy bóng ngược lại thả ra thì quay lại vị trí cũ
  if (ps2x.ButtonPressed(PSB_TRIANGLE))
  {
    S360_PU(4095);
    delay(1000);
  }
  else {S360_PU(2048);
  delay(1000);}
  delay(50);
  return 1;
}

 
 //khai báo các chân cảm biến
#define SCL 22
#define SDA 21
/*
  SCL - SCL ( Analog 5 )
  SDA - SDA ( analog 4 )
  VDD - 3.3V DC
  GND - GND
*/

/* Sử dụng cảm với thời gian cụ thể và Gain cụ thể
 * integration time (Thời gian lấy mẫu màu của cảm biến): 2.4ms, 24ms, 50ms, 101ms, 154ms, 600ms
 * Gain (Độ lợi kiểm soát độ nhạy màu của biến): 1x, 4x, 16x, 60x
 */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_16X);
 
 // kết nối cảm biến với mạch
void setupSensor() 
{
  Serial.begin(9600);
 
  if (tcs.begin()) 
  {
    Serial.println("Cảm biến hoạt động");
  } 
  else 
  {
    Serial.println("Cảm biến không kết nối, hãy kiểm tra lại kết nối...");
    while (1);
  }
  
}
 
 // hàm sử dụng cảm biến 
void loopSensor() 
{
    uint16_t r, g, b, c, colorTemp, lux; //khai báo các biến cần dùng 
     
    tcs.getRawData(&r, &g, &b, &c);// lấy dữ liệu theo bảng màu RGB
    
    colorTemp = tcs.calculateColorTemperature(r, g, b); //Nhiệt độ màu theo thang đo Kelvin
    
    lux = tcs.calculateLux(r, g, b); //Độ rọi soi, cường độ sáng
     
    //điểu khiển S180DE theo màu sắc của bóng
    //nếu bóng màu đen thì quay servo sao cho bóng đen qua bên màu đen
    //nếu bóng màu trắng thì quay servo sao cho bóng trắng qua bên màu trắng
    //nếu không có bóng thì quay về giữa
    
    S180_DE(1500);
    if (r==255 && g==255 && b==255)
    {
      S180_DE(1389);
    }
    else if (r==0 && g==0 && b==0)
    {
      S180_DE(1772);
    }
    else {
    S180_DE(1500);}
    delay(50);
}
