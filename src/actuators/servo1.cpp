#include "servo.h"
#include "../config.h" // Nơi chứa khai báo SERVO_PIN (ví dụ chân 18)

Servo radarServo;

void initServo() {
    // Cấp phát timer cho Servo trên ESP32
    ESP32PWM::allocateTimer(0);
    radarServo.setPeriodHertz(50);
    radarServo.attach(SERVO_PIN, 500, 2400);
    
    stopServo(); // Mặc định khi bật máy là đứng im
}

void scanServo() {
    radarServo.write(0); // Quay liên tục để quét tìm lửa
}

void stopServo() {
    radarServo.write(90); // Khóa đứng yên tại vị trí hiện tại
}x