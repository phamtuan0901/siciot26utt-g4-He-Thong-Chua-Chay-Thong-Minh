#include <ESP32Servo.h>
#include "config.h"
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