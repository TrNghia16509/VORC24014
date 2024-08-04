#include "motors.h"
#include <PS2X_lib.h>
#include "Servo.h"
#include "servos.h"
PS2X ps2x; // create PS2 Controller Class

#define PS2_DAT 12 // MISO  19
#define PS2_CMD 13 // MOSI  23
#define PS2_SEL 15 // SS     5
#define PS2_CLK 14 // SLK   18


//#define PS2_DAT A3 // MISO  19
//#define PS2_CMD A4 // MOSI  23
//#define PS2_SEL A5 // SS     5
//#define PS2_CLK A2 // SLK   18


//#define MIN_PWM 0
//#define MAX_PWM 4095
// bool RUN = 0;

void setupPS2controller()
{
  int err = -1;
  while (err != 0){
  err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
//  ps2x.readType();
  //  ps2x.read_gamepad(false, 0); // disable vibration of the controller
}
bool PS2control_loop()
{
  // Based on IgorF2's Arduino Bot:https://www.instructables.com/Arduino-Robot-With-PS2-Controller-PlayStation-2-Jo/
  ps2x.read_gamepad(false,false);

  int nJoyLY = ps2x.Analog(PSS_LY); // read Left y-joystick
  int nJoyRY = ps2x.Analog(PSS_RY); // read Right y-joystick

  nJoyLY = map(nJoyLY, 0, 256, -4092, 4092);
  nJoyRY = map(nJoyRY, 0, 256, 4092, -4092);
  if (nJoyLY>0)
  {
    DC1_forward(nJoyLY);
    delay(500);
  }
  else if (nJoyLY<0)
  {
    DC1_backward(nJoyLY);
    delay(500);
  }
  else { DC1();}
  delay(500);

  if (nJoyRY>0)
  {
    DC2_forward(nJoyRY);
    delay(500);
  }
  else if (nJoyRY<0)
  {
    DC2_backward(nJoyRY);
    delay(500);
  }
  else { DC2();}

  if (ps2x.NewButtonState(PSB_R2))
  {
    DC3_in();
    delay(500);
  }
  else if (ps2x.NewButtonState(PSB_R1))
  {
    DC3_out();
    delay(500);
  }
  else { DC3();
  delay(500);
  }

  int turn
  turn = 2048;
  if (ps2x.Button(PSB_CIRCLE))
  {
    turn += 5;
    S360_MO(turn);
    delay(500);
  }
  else if (ps2x.Button(PSB_PAD_LEFT))
  {
    turn -= 5;
    S360_MO(turn);
    delay(500);
  }
  else {S360MO(0)};

  if (ps2x.ButtonPressed(PSB_L2))
  {
    S180_OP(90);
  }
  else 
  {
    S180_OP(0);
  }

  int nTrigL = ps2x.Analog(PSB_L1);
  nTrigL = map(nTrigL, 0 ,255, 0, 4096);
  if (nTrigL > 2048)
  {
    DC4(nTrigL);
  }
  else DC4(0);

  if (ps2x.Button(PSB_TRIANGLE))
  {
    S360_PU(337.5);
  }
  else S360_PU(0);
  delay(100);
  return 1;
}
