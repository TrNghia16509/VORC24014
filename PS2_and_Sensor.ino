#include "motors_and_servos.h"
#include "PS2_controller_and_Sensor.h"

void setup()
{
  Serial.begin(115200);
  setupMotors();
  setupServo();
  setupPS2controller();
  setupSensor();
  Serial.println("Done setup!");
}

void loop()
{
  ps2x.read_gamepad(0, 0);
  PS2control_loop();
  loopSensor();
  delay(50);
}

