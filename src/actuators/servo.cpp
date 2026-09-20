#include <ESP32Servo.h>
<<<<<<< HEAD
#include "../config/config.h"
=======
#include "config.h"
>>>>>>> 5a27bb5f4ca3a0af90cb0ed49142c28bbe9d02e8
#include "servo.h"

Servo servo;

void initServo() {
  servo.attach(SERVO_PIN);
  servo.write(HOME_ANGLE);
}

void moveToFirePosition() {
  servo.write(FIRE_ANGLE);
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void moveToHomePosition() {
  servo.write(HOME_ANGLE);
  vTaskDelay(pdMS_TO_TICKS(1000));
}