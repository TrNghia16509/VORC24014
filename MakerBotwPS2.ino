#include "motors.h"
#include "PS2_controller_1.h"
#include "servos.h"

void setup()
{
  Serial.begin(115200);
  setupMotors();
  setupServo();
  setupPS2controller();
  Serial.println("Done setup!");
}

void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control_loop();
}
