#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>
#include <Wire.h>
#include <Servo.h> 
#include <servos.h>
 
/*
  SCL - SCL ( Analog 5 )
  SDA - SDA ( analog 4 )
  VDD - 3.3V DC
  GND - GND
*/
 
//  Sử dụng cảm biến ở giá trị mặc định (int time = 2.4ms, gain = 1x)
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();
 
/* Sử dụng cảm với thời gian cụ thể và Gain cụ thể
 * integration time (Thời gian lấy mẫu màu của cảm biến): 2.4ms, 24ms, 50ms, 101ms, 154ms, 600ms
 * Gain (Độ lợi kiểm soát độ nhạy màu của biến): 1x, 4x, 16x, 60x
 */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_16X);
 
void setup() 
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
 
void loop() 

{
    uint16_t r, g, b, c, colorTemp, lux;
     
    tcs.getRawData(&r, &g, &b, &c);
    
    colorTemp = tcs.calculateColorTemperature(r, g, b); //Nhiệt độ màu theo thang đo Kelvin
    
    lux = tcs.calculateLux(r, g, b); //Độ rọi soi, cường độ sáng
     
    S180_DE(90);
    if (r==255 && g==255 && b==255)
    {
      S180_DE(70);
    }
    else if (r==0 && g==0 && b==0)
    {
      S180_DE(130);
    }
    else {
    S180_DE(90);}
    delay(500);
}