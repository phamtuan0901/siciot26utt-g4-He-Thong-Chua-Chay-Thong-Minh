#include <Arduino.h>

// 1. Nhúng các module Communication (Giao tiếp)
#include "../communication/wifi.h"
#include "../communication/mqtt.h"

// 2. Nhúng các module Sensors (Cảm biến)
#include "../sensors/dht11.h" // Chứa khai báo DHT, biến temp, humidity
#include "../sensors/flame.h"  // Chứa khai báo isFireDetected, initFlameSensor, flameTask
#include "../sensors/smoke.h"  // Chứa khai báo isGasDetected, initMQ2, mq2Task

// 3. Nhúng các module Actuators (Thiết bị chấp hành)
#include "../actuators/relay.h" // Chứa khai báo turnOnRelay, turnOffRelay
#include "../actuators/servo.h" // Chứa khai báo initServo, scanServo, stopServo


// ==========================================
// TASK LOGIC TRUNG TÂM (ĐIỀU KHIỂN RADAR & BƠM)
// ==========================================
void mainLogicTask(void *param) {
    while (true) {
        // Lấy dữ liệu từ các biến toàn cục (đã được 'extern' trong các file .h)
        float currentTemp = temp;        // Từ sensor.h
        bool fireAlert = isFireDetected; // Từ flame.h
        bool gasAlert = isGasDetected;   // Từ smoke.h

        // 1. NGUY CƠ RÒ RỈ KHÍ GAS (Chỉ báo động, không cần quay servo xịt nước)
        if (gasAlert) {
            turnOnRelay(); // Bật còi báo động / Bật quạt thông gió (tùy cấu hình relay của bạn)
            Serial.println("⚠ PHÁT HIỆN RÒ RỈ KHÍ GAS/KHÓI!");
        }
        
        // 2. PHÁT HIỆN NHIỆT ĐỘ CAO (Bắt đầu quét Radar)
        else if (currentTemp > 35.0) {
            if (!fireAlert) {
                // Nóng nhưng chưa thấy lửa -> Servo quay vòng quanh để tìm kiếm
                scanServo();       
                turnOffRelay();    // Chưa chĩa trúng lửa thì chưa được bơm nước
                Serial.println("⚠ Nhiệt độ cao! Radar đang quét tìm vị trí lửa...");
            } else {
                // Nóng VÀ cảm biến trên Servo đã quét trúng tia lửa hồng ngoại
                stopServo();       // Phanh gấp Servo lại để khóa mục tiêu
                turnOnRelay();     // Bật máy bơm xịt nước thẳng vào gốc lửa
                Serial.println("🔥 ĐÃ KHÓA MỤC TIÊU LỬA! Đang phun nước...");
            }
        } 
        
        // 3. PHÁT HIỆN LỬA CHỚP NHOÁNG (Nhiệt độ chưa kịp tăng nhưng đã có lửa)
        else if (fireAlert) {
            stopServo();           // Phanh Servo
            turnOnRelay();         // Bật bơm ngay lập tức
            Serial.println("🔥 CẢNH BÁO: TIA LỬA HỒNG NGOẠI! Đang phun nước...");
        }
        
        // 4. MÔI TRƯỜNG AN TOÀN
        else {
            stopServo();           // Servo đứng im nghỉ ngơi
            turnOffRelay();        // Tắt máy bơm, tắt còi
        }

        // Delay 100ms để nhường CPU cho các task khác. 
        // (Tốc độ 100ms giúp Servo phanh rất nhạy ngay khi thấy lửa)
        vTaskDelay(100 / portTICK_PERIOD_MS); 
    }
}


// ==========================================
// HÀM SETUP (Khởi tạo hệ thống)
// ==========================================
void setup() {
    Serial.begin(115200);
    Serial.println("\nKhởi động Hệ Thống Chữa Cháy Thông Minh...");

    // 1. Khởi tạo phần mạng (Bỏ comment nếu bạn đã code xong wifi/mqtt)
    // initWiFi();
    // initMQTT();

    // 2. Khởi tạo chân thiết bị (Các hàm này phải được viết trong các file .cpp tương ứng)
    initSensor();       // Khởi tạo DHT11
    initFlameSensor();  // Khởi tạo Cảm biến lửa
    initMQ2();          // Khởi tạo Cảm biến MQ-2
    initRelay();        // Khởi tạo Relay (Bơm, Còi, Đèn)
    initServo();        // Khởi tạo Servo Radar

    // 3. Khởi chạy hệ điều hành FreeRTOS (Chạy song song các tiến trình)
    // Cú pháp: xTaskCreate(Hàm_chạy, "Tên_Task", Bộ_nhớ_RAM, Tham_số, Độ_ưu_tiên, Handle);
    
    // Các task thu thập dữ liệu (Ưu tiên mức 1)
    xTaskCreate(sensorTask, "DHT_Task",   2048, NULL, 1, NULL);
    xTaskCreate(flameTask,  "Flame_Task", 2048, NULL, 1, NULL);
    xTaskCreate(mq2Task,    "Smoke_Task", 2048, NULL, 1, NULL);
    
    // Task Logic ra quyết định đóng cắt (Ưu tiên mức 2 - cao hơn để phản ứng nhanh)
    xTaskCreate(mainLogicTask, "Logic_Task", 2048, NULL, 2, NULL);
}


// ==========================================
// HÀM LOOP
// ==========================================
void loop() {
    // Vì dự án đang dùng FreeRTOS Tasks để chạy đa nhiệm song song,
    // hàm loop mặc định của Arduino không còn tác dụng.
    // Xóa nó đi bằng lệnh dưới để giải phóng bộ nhớ cho ESP32.
    vTaskDelete(NULL);
}