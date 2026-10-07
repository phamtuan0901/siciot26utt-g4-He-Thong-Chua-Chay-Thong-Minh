srcHardwareIot/
├── include/
│   ├── communication/
│   │   ├── mqtt.h
│   │   └── wifi.h
│   ├── sensors/
│   │   └── sensor_task.h
│   ├── service/
│   │   └── fire_logic.h
│   ├── actuators/
│   │   ├── relay.h
│   │   └── servo.h
│   └── config.h
├── src/
│   ├── communication/
│   │   ├── mqtt.cpp
│   │   └── wifi.cpp
│   ├── sensors/
│   │   └── sensor_task.cpp
│   ├── service/
│   │   └── fire_logic.cpp
│   ├── actuators/
│   │   ├── relay.cpp
│   │   └── servo.cpp
│   └── main.cpp
├── platformio.ini
└── README.md

### Thành phần chính

- **`include/config.h`**: Chứa các cấu hình phần cứng, chân GPIO, ngưỡng cảnh báo và các thông số của hệ thống.

- **`include/communication/`**: Chứa các module giao tiếp mạng.
  - `wifi.h`: Khởi tạo và quản lý kết nối WiFi.
  - `mqtt.h`: Kết nối MQTT, publish dữ liệu cảm biến và nhận lệnh từ MQTT Broker.

- **`include/sensors/`**: Xử lý các cảm biến của hệ thống.
  - `sensor_task.h`: Đọc dữ liệu từ DHT11, MQ-2 và cảm biến ngọn lửa.

- **`include/service/`**: Chứa logic phát hiện cháy.
  - `fire_logic.h`: Phân tích dữ liệu cảm biến và xác định trạng thái `NORMAL`, `WARNING` hoặc `FIRE`.

- **`include/actuators/`**: Điều khiển các thiết bị đầu ra.
  - `relay.h`: Điều khiển relay và máy bơm.
  - `servo.h`: Điều khiển servo định hướng vòi phun.

- **`src/`**: Chứa phần implementation tương ứng với các module trong `include/`.

- **`main.cpp`**: File khởi chạy chính của ESP32, khởi tạo các module và thực hiện vòng lặp chính của hệ thống.

- **`platformio.ini`**: Cấu hình PlatformIO cho board ESP32 và các thư viện được sử dụng.

### Phần cứng

Hệ thống sử dụng ESP32 làm bộ điều khiển trung tâm và kết nối với các thiết bị:

- ESP32
- DHT11
- MQ-2
- Flame Sensor
- Servo Motor
- Relay
- Máy bơm
- Buzzer / LED cảnh báo

### Chức năng

ESP32 thực hiện:

- Đọc nhiệt độ và độ ẩm từ DHT11.
- Đọc nồng độ khí từ MQ-2.
- Phát hiện ngọn lửa bằng Flame Sensor.
- Phân tích dữ liệu cảm biến để xác định trạng thái cháy.
- Điều khiển servo theo trạng thái hệ thống.
- Điều khiển relay và máy bơm khi phát hiện cháy.
- Gửi dữ liệu cảm biến qua MQTT.
- Nhận lệnh điều khiển từ MQTT Broker.

### Luồng hoạt động

```text
DHT11 ────────┐
MQ-2 ─────────┤
Flame Sensor ─┤
              ▼
           ESP32
              │
              ▼
        Fire Detection
              │
       ┌──────┼──────┐
       ▼      ▼      ▼
    NORMAL WARNING  FIRE
       │      │      │
       │      │      ├── Servo
       │      │      ├── Relay
       │      │      └── Pump
       │      │
       └──────┴──────────► MQTT
                              │
                              ▼
                         MQTT Broker
                              │
                    ┌─────────┴─────────┐
                    ▼                   ▼
                 Node-RED           Backend