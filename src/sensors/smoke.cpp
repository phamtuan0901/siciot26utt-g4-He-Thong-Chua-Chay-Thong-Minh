#include "mq2.h"
#include "config.h" // Giả định bạn đã định nghĩa GAS_PIN (ví dụ 34) ở trong file này

// Khởi tạo giá trị ban đầu cho các biến toàn cục
int gasValue = 0;
bool isGasDetected = false;

// Ngưỡng cảnh báo nồng độ khói/gas (có thể tinh chỉnh tùy thực tế)
const int GAS_THRESHOLD = 2000; 

void initMQ2() {
    // Với Analog trên ESP32, pinMode không bắt buộc, nhưng khai báo để code tường minh
    pinMode(GAS_PIN, INPUT);
}

void mq2Task(void *param) {
    while (true) {
        // Đọc giá trị Analog từ cảm biến MQ-2
        gasValue = analogRead(GAS_PIN);
        
        // Kiểm tra xem nồng độ khói có vượt mức nguy hiểm không
        if (gasValue > GAS_THRESHOLD) {
            isGasDetected = true;
        } else {
            isGasDetected = false;
        }

        // Cảm biến khói không cần phản ứng chớp nhoáng như lửa, 
        // delay 500ms là đủ để nhường CPU cho các Task khác chạy mượt mà
        vTaskDelay(500 / portTICK_PERIOD_MS); 
    }
}