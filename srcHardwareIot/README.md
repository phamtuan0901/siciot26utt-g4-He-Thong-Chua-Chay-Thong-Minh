# AI Fire & Smoke Detection

Module AI sử dụng **YOLO** để phát hiện **lửa (Fire)** và **khói (Smoke)** từ camera trong hệ thống Chữa Cháy Thông Minh. Kết quả nhận diện được gửi qua **MQTT** để kết hợp với dữ liệu từ ESP32 và các cảm biến khác.

## Chức năng

- Nhận hình ảnh từ camera theo thời gian thực.
- Phát hiện lửa và khói bằng mô hình YOLO.
- Hiển thị kết quả nhận diện trực tiếp trên camera.
- Xử lý confidence của kết quả detection.
- Gửi trạng thái phát hiện qua MQTT.
- Tích hợp với MQTT Broker, Node-RED và các module khác của hệ thống.

## Công nghệ

- Python 3.10+
- Ultralytics YOLO
- OpenCV
- Paho MQTT
- NumPy
- MQTT

## Cấu trúc

```text
srcAiDetectFire/
├── best.pt
├── config.py
├── detector.py
├── main.py
├── mqtt_handler.py
└── README.md

Công nghệ sử dụng
Python 3.10+
Ultralytics YOLO
OpenCV
Paho MQTT
NumPy
MQTT

Cài đặt
Cài đặt các thư viện cần thiết:

pip install ultralytics opencv-python paho-mqtt numpy
Cấu hình

Các thông số kết nối được cấu hình trong config.py.

Ví dụ:

MQTT_BROKER = "172.20.10.5"
MQTT_PORT = 1883
CAMERA_INDEX = 0
CONFIDENCE_THRESHOLD = 0.5

Trong đó:

MQTT_BROKER: Địa chỉ MQTT Broker.
MQTT_PORT: Port MQTT.
CAMERA_INDEX: Camera sử dụng để nhận diện.
CONFIDENCE_THRESHOLD: Ngưỡng confidence của YOLO.
Chạy chương trình

Di chuyển vào thư mục:

cd srcAiDetectFire

Sau đó chạy:

python main.py

Chương trình sẽ mở camera và thực hiện nhận diện lửa/khói theo thời gian thực.

Luồng xử lý
Camera
   │
   ▼
OpenCV
   │
   ▼
YOLO Model
   │
   ├── Fire
   ├── Smoke
   └── No Detection
   │
   ▼
Detection Result
   │
   ▼
MQTT Handler
   │
   ▼
MQTT Broker
   │
   ├── Node-RED
   └── Backend
Tích hợp với hệ thống

Module srcAiDetectFire đóng vai trò là nguồn dữ liệu AI trong hệ thống Chữa Cháy Thông Minh.

Kết quả từ camera được kết hợp với dữ liệu từ các cảm biến:

              ┌──────────────┐
              │   Camera     │
              └──────┬───────┘
                     │
                     ▼
                YOLO AI
                     │
                Fire / Smoke
                     │
                     ▼
                  MQTT
                     │
        ┌────────────┴────────────┐
        │                         │
        ▼                         ▼
   Node-RED                    Backend
        │                         │
        └────────────┬────────────┘
                     │
                     ▼
                Dashboard

AI có thể cung cấp thêm thông tin cho logic phát hiện cháy cùng với:

Nhiệt độ từ DHT11
Độ ẩm từ DHT11
Giá trị khí từ MQ-2
Cảm biến ngọn lửa
Kết quả nhận diện từ camera

Việc kết hợp nhiều nguồn dữ liệu giúp hệ thống giảm phụ thuộc vào một cảm biến duy nhất và hạn chế cảnh báo sai.