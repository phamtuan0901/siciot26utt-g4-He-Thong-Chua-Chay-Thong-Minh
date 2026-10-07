#include <ESP32Servo.h>
#include "../config/config.h"


Servo servo;

void initServo() {
  Serial.println("Servo khoi dong: ");
  servo.attach(SERVO_PIN);
  servo.write(HOME_ANGLE);
  delay(1000);
}

void moveToFirePosition(float angle) {
  angle = constrain(angle,0.0,360.0);
  Serial.print("Servo quay toi goc: ");
  Serial.println(angle);
  servo.write((int)(angle));
  delay(1000);
}

void moveToHomePosition() {
  servo.write(HOME_ANGLE);
  delay(1000);  
}