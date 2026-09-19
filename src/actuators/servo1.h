#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
// Bạn cần cài đặt thư viện ESP32Servo trong quản lý thư viện của VS Code
#include <ESP32Servo.h> 

void initServo();
void scanServo();
void stopServo();

#endif