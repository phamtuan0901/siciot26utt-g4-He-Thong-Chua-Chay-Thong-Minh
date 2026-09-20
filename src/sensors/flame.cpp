<<<<<<< HEAD
// #include "flame.h"
// #include "config.h" // Giả định bạn đã định nghĩa FLAME_PIN (ví dụ 32) ở trong file này giống như sensor.cpp

// bool isFireDetected = false;

// void initFlameSensor() {
//     // FLAME_PIN phải được define trong file config.h
//     pinMode(FLAME_PIN, INPUT); 
// }

// void flameTask(void *param) {
//     while (true) {
//         // Đọc cảm biến: LOW thường nghĩa là phát hiện lửa
//         int flameState = digitalRead(FLAME_PIN);
        
//         if (flameState == LOW) {
//             isFireDetected = true;
//         } else {
//             isFireDetected = false;
//         }

//         // Bắt buộc phải có hàm delay của FreeRTOS để nhường CPU cho các Task khác (như sensorTask, mqttTask)
//         vTaskDelay(200 / portTICK_PERIOD_MS); 
//     }
// }
=======
#include "flame.h"
#include "config.h" // Giả định bạn đã định nghĩa FLAME_PIN (ví dụ 32) ở trong file này giống như sensor.cpp

bool isFireDetected = false;

void initFlameSensor() {
    // FLAME_PIN phải được define trong file config.h
    pinMode(FLAME_PIN, INPUT); 
}

void flameTask(void *param) {
    while (true) {
        // Đọc cảm biến: LOW thường nghĩa là phát hiện lửa
        int flameState = digitalRead(FLAME_PIN);
        
        if (flameState == LOW) {
            isFireDetected = true;
        } else {
            isFireDetected = false;
        }

        // Bắt buộc phải có hàm delay của FreeRTOS để nhường CPU cho các Task khác (như sensorTask, mqttTask)
        vTaskDelay(200 / portTICK_PERIOD_MS); 
    }
}
>>>>>>> 5a27bb5f4ca3a0af90cb0ed49142c28bbe9d02e8
