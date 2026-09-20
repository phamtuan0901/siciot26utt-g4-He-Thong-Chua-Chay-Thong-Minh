# 🔥 HỆ THỐNG CHỮA CHÁY THÔNG MINH

## 1. Giới thiệu dự án

Dự án **Hệ thống Chữa Cháy Thông Minh** được xây dựng nhằm phát hiện các dấu hiệu bất thường liên quan đến cháy/nhiệt độ và thực hiện các hành động xử lý phù hợp.

Hệ thống được thiết kế theo mô hình **module hóa**, trong đó mỗi module đảm nhiệm một chức năng riêng. Điều này giúp các thành viên trong nhóm có thể phát triển độc lập và dễ dàng tích hợp vào chương trình chính.

Các module chính của hệ thống:

* `sensors` – Thu thập dữ liệu từ cảm biến.
* `actuators` – Điều khiển các thiết bị chấp hành.
* `communication` – Giao tiếp và truyền nhận dữ liệu.
* `camera_ai` – Camera và xử lý nhận diện bằng AI.
* `main.c` – Chương trình chính, điều phối toàn bộ hệ thống.

---

## 2. Vấn đề và Bối cảnh

* Bối cảnh chung: Các văn phòng làm việc hiện đại, đặc biệt là các công ty công nghệ, tài chính, truyền thông, có mật độ thiết bị điện tử cực kỳ dày đặc (máy tính để bàn, laptop, ...). Đặc thù của các thiết bị này là phải vận hành liên tục 24/7. Điều này tỏa ra lượng nhiệt lớn, dây cáp chằng chịt, dẫn đến rủi ro quá tải hoặc chập mạch nguồn điện luôn ở mức cao.

* Số liệu thực tế: Theo các báo cáo về an toàn phòng cháy chữa cháy, sự cố về hệ thống và thiết bị điện (chập mạch, quá tải) luôn chiếm tỷ lệ cao nhất, thường lên tới 60-70% nguyên nhân gây ra các vụ cháy nổ tại các cơ sở kinh doanh, tòa nhà văn phòng. Thiệt hại trong các vụ cháy này không chỉ là phần cứng mà nguy hiểm hơn là sự mất mát về "dữ liệu vĩnh viễn" và thời gian doanh nghiệp bị đình trệ hoạt động.

* Ví dụ điển hình: Một vụ cháy lớn từng xảy ra tại khu văn phòng của một công ty liên doanh cáp điện ở Hải Phòng vào đúng ngày nghỉ. Do không có nhân viên làm việc và hệ thống chỉ báo động tại chỗ, đám cháy nghi do chập điện đã âm ỉ và lan rộng, thiêu rụi toàn bộ tài liệu, hồ sơ và hệ thống máy móc, máy tính trong văn phòng trước khi lực lượng cứu hỏa nhận được tin báo.

- Vấn đề cốt lõi :

* Cảnh báo cháy không linh hoạt: Cảnh báo tại chỗ như thông thường sẽ không thông báo đến được Chủ doanh nghiệp

* Khủng hoảng ngoài giờ làm việc: Sự cố chập điện thường bùng phát vào ban đêm hoặc ngày nghỉ cuối tuần khi không có nhân viên trực. Hệ thống báo cháy truyền thống (chỉ hú còi tại chỗ) trở nên vô dụng vì không ai nghe thấy để dập lửa ngay từ những giây đầu tiên.

---

## 3. Mục tiêu cần đạt

- Đối tượng hướng đến:

* Người mua : Giám đốc doanh nghiệp

* Người sử dụng thiết bị : Nhân viên công ty

- Mục tiêu giải pháp hệ thống cần đạt:

* Cảnh báo đa kênh : Hệ thống phải lập tức gửi cảnh báo (Notification, SMS, Cuộc gọi tự động) đến điện thoại của IT Manager và tổ bảo vệ, dù họ đang ở nhà.

* Kiểm soát và Phân quyền thông minh qua App: Cung cấp cho bộ phận IT giao diện giám sát nhiệt độ/độ ẩm theo thời gian thực. Bắt buộc có chức năng "Xác nhận báo động" trên App: Cho phép người quản lý có khoảng 10-15 giây để xác nhận qua camera hoặc nhờ bảo vệ kiểm tra, từ đó có thể chủ động tắt/hủy lệnh xả khí từ điện thoại nếu đó là báo giả, tránh lãng phí chi phí nạp lại bình khí đắt tiền. *

---

# 4. Kiến trúc tổng thể

```text
                    ┌─────────────────────┐
                    │      SENSORS        │
                    │                     │
                    │ Temperature         │
                    │ Humidity            │
                    │ Other Sensors       │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │      CAMERA AI      │
                    │                     │
                    │ Camera              │
                    │ Image Processing    │
                    │ AI Detection        │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │       MAIN.C        │
                    │                     │
                    │ System Logic        │
                    │ Decision Making     │
                    │ Module Integration  │
                    └───────┬─────┬───────┘
                            │     │
                 ┌──────────┘     └──────────┐
                 ▼                           ▼
       ┌─────────────────┐          ┌─────────────────┐
       │    ACTUATORS    │          │  COMMUNICATION  │
       │                 │          │                 │
       │ Servo           │          │ MQTT            │
       │ Pump            │          │ Wi-Fi           │
       │ Alarm           │          │ Data Transfer   │
       └─────────────────┘          └────────┬────────┘
                                             │
                                             ▼
                                      ┌─────────────┐
                                      │  Node-RED   │
                                      └─────────────┘
```

---

# 5. Cấu trúc thư mục

Cấu trúc hiện tại của project:

```text
He-Thong-Chua-Chay-Thong-Minh/
│
├── src/
│   │
│   ├── actuators/
│   │   └── ...
│   │
│   ├── communication/
│   │   └── ...
│   │
│   ├── sensors/
│   │   └── ...
│   │
│   ├── camera_ai/
│   │   ├── camera_ai.c
│   │   └── camera_ai.h
│   │
│   └── main.c
│
├── .gitignore
│
└── README.md
```

---

# 6. Chức năng của từng module

## 6.1. Sensors

Thư mục:

```text
src/sensors/
```

Module `sensors` chịu trách nhiệm thu thập dữ liệu từ các cảm biến của hệ thống.

Ví dụ:

* DHT11/DHT22.
* Cảm biến nhiệt độ.
* Cảm biến độ ẩm.
* Cảm biến khói.
* Các cảm biến khác.

### Nhiệm vụ

* Khởi tạo cảm biến.
* Đọc dữ liệu.
* Kiểm tra dữ liệu.
* Cung cấp dữ liệu cho `main.c`.

Module cảm biến **không nên xử lý logic hệ thống hoặc MQTT**.

---

# 7. Actuators

Thư mục:

```text
src/actuators/
```

Module `actuators` chịu trách nhiệm điều khiển các thiết bị chấp hành.

Ví dụ:

* Servo.
* Máy bơm.
* Còi cảnh báo.
* Relay.
* Đèn cảnh báo.

### Nhiệm vụ

* Khởi tạo thiết bị.
* Bật/tắt thiết bị.
* Điều chỉnh trạng thái thiết bị.
* Thực hiện lệnh do `main.c` đưa xuống.

---

# 8. Communication

Thư mục:

```text
src/communication/
```

Module `communication` chịu trách nhiệm giao tiếp giữa thiết bị và hệ thống bên ngoài.

Có thể bao gồm:

* Wi-Fi.
* MQTT.
* Các giao thức truyền thông khác.

### Nhiệm vụ

```text
Thiết bị
   │
   ├── Publish dữ liệu
   │
   ▼
MQTT Broker
   │
   ▼
Node-RED
```

Và chiều ngược lại:

```text
Node-RED
   │
   ▼
MQTT Broker
   │
   ▼
Thiết bị
   │
   ▼
Actuators
```

---

# 9. Camera AI

Thư mục mới:

```text
src/camera_ai/
```

Camera AI là module được bổ sung để hệ thống có khả năng sử dụng hình ảnh và AI trong quá trình phát hiện sự cố.

### Chức năng dự kiến

```text
Camera
   │
   ▼
Capture Image
   │
   ▼
Image Processing
   │
   ▼
AI Model
   │
   ▼
Detection Result
   │
   ▼
main.c
```

Module Camera AI có thể được phát triển để:

* Phát hiện lửa.
* Phát hiện khói.
* Nhận diện đối tượng.
* Phân loại hình ảnh.
* Phát hiện các tình trạng bất thường.

> Thuật toán AI cụ thể sẽ được xác định dựa trên phần cứng Camera và model AI mà nhóm sử dụng.

---

# 10. Main.c

File:

```text
src/main.c
```

`main.c` là trung tâm điều phối của toàn bộ hệ thống.

Main **không nên chứa toàn bộ code chi tiết của từng module**.

Thay vào đó:

```text
main.c
 │
 ├── sensors
 │
 ├── camera_ai
 │
 ├── actuators
 │
 └── communication
```

### Nhiệm vụ của main

* Khởi tạo các module.
* Đọc dữ liệu cảm biến.
* Nhận kết quả Camera AI.
* Phân tích tình trạng hệ thống.
* Đưa ra quyết định.
* Điều khiển actuator.
* Gửi dữ liệu qua communication.

---

# 11. Luồng hoạt động chính

## Khi hệ thống khởi động

```text
START
  │
  ▼
Initialize Sensors
  │
  ▼
Initialize Camera AI
  │
  ▼
Initialize Actuators
  │
  ▼
Initialize Communication
  │
  ▼
Main Loop
```

---

## Trong vòng lặp chính

```text
                 ┌──────────────┐
                 │ Read Sensors │
                 └──────┬───────┘
                        │
                        ▼
                 ┌──────────────┐
                 │ Camera AI    │
                 │ Detection    │
                 └──────┬───────┘
                        │
                        ▼
                 ┌──────────────┐
                 │ Analyze Data │
                 └──────┬───────┘
                        │
                 ┌──────┴──────┐
                 │             │
              Normal        Abnormal
                 │             │
                 ▼             ▼
              Monitor       Actuators
                               │
                               ▼
                          Communication
                               │
                               ▼
                            Node-RED
```

---

# 12. Logic phát hiện cháy dự kiến

Hệ thống có thể kết hợp nhiều nguồn dữ liệu để tăng độ chính xác.

Ví dụ:

```text
DHT11
 │
 ├── Temperature
 │
 └── Humidity
        │
        ▼
   ┌───────────┐
   │           │
   │  MAIN.C   │
   │           │
   └─────┬─────┘
         │
         │
Camera AI
 │
 └── Fire/Smoke Detection
         │
         ▼
    Decision Making
         │
    ┌────┴────┐
    │         │
 NORMAL     FIRE
    │         │
    ▼         ▼
 Monitor    Alarm
              │
              ▼
             Pump
              │
              ▼
          Communication
              │
              ▼
           Node-RED
```

Việc quyết định có cháy hay không nên được xử lý ở `main.c`, thay vì để Camera AI hoặc Sensor tự điều khiển actuator.

---

# 13. Công việc cần thực hiện

## Sensors

* [ ] Hoàn thiện module DHT11.
* [ ] Kiểm tra nhiệt độ.
* [ ] Kiểm tra độ ẩm.
* [ ] Thêm các cảm biến khác nếu cần.
* [ ] Test độc lập module.

## Actuators

* [ ] Hoàn thiện module Servo.
* [ ] Thêm relay nếu cần.
* [ ] Thêm máy bơm nếu cần.
* [ ] Thêm còi cảnh báo nếu cần.
* [ ] Test từng thiết bị.

## Communication

* [ ] Cấu hình Wi-Fi.
* [ ] Kết nối MQTT Broker.
* [ ] Tạo MQTT topic.
* [ ] Publish dữ liệu cảm biến.
* [ ] Subscribe lệnh điều khiển.
* [ ] Xử lý mất kết nối.
* [ ] Test với Node-RED.

## Camera AI

* [ ] Xác định loại Camera.
* [ ] Xác định vi điều khiển/board sử dụng.
* [ ] Khởi tạo Camera.
* [ ] Chụp frame.
* [ ] Xử lý hình ảnh.
* [ ] Tích hợp AI model.
* [ ] Thực hiện inference.
* [ ] Trả về kết quả nhận diện.
* [ ] Test nhận diện.
* [ ] Tích hợp với `main.c`.

## Main

* [ ] Khởi tạo tất cả module.
* [ ] Đọc dữ liệu sensors.
* [ ] Nhận kết quả Camera AI.
* [ ] Xử lý logic phát hiện cháy.
* [ ] Điều khiển actuators.
* [ ] Gửi trạng thái qua communication.
* [ ] Tích hợp toàn bộ hệ thống.

## Node-RED

* [ ] Kết nối MQTT.
* [ ] Nhận dữ liệu cảm biến.
* [ ] Nhận trạng thái Camera AI.
* [ ] Hiển thị trạng thái hệ thống.
* [ ] Gửi lệnh điều khiển.
* [ ] Kiểm tra cảnh báo.

---

# 14. Nguyên tắc phát triển module

Mỗi module phải có trách nhiệm riêng:

```text
sensors
    ↓
Đọc cảm biến

camera_ai
    ↓
Camera + AI

actuators
    ↓
Điều khiển thiết bị

communication
    ↓
Giao tiếp

main.c
    ↓
Điều phối hệ thống
```

Không nên để các module phụ thuộc trực tiếp vào nhau nếu không cần thiết.

Ví dụ:

```text
Không nên:

DHT11 → MQTT → Servo
```

Mà nên:

```text
DHT11 ──────┐
            │
Camera AI ──┤
            ▼
          main.c
            │
     ┌──────┴──────┐
     ▼             ▼
 Actuators    Communication
```

Điều này giúp dự án dễ bảo trì và dễ làm việc nhóm.

---

# 15. Mục tiêu cuối cùng

Hệ thống hoàn chỉnh cần có khả năng:

* Giám sát môi trường.
* Thu thập dữ liệu cảm biến.
* Phân tích hình ảnh bằng Camera AI.
* Phát hiện tình trạng bất thường.
* Đưa ra quyết định xử lý.
* Điều khiển thiết bị chữa cháy/cảnh báo.
* Gửi dữ liệu lên hệ thống giám sát.
* Nhận lệnh điều khiển từ Node-RED.
* Hoạt động theo kiến trúc module hóa.

---

# 17. Lưu ý

Module `camera_ai` hiện là **khung phát triển**.

Để triển khai Camera AI thực tế cần xác định:

1. Loại Camera.
2. Board/vi điều khiển.
3. Độ phân giải Camera.
4. Model AI.
5. Đối tượng cần nhận diện.
6. Cách chạy AI: trên thiết bị hoặc trên server.
7. Cách truyền kết quả AI về hệ thống.

Sau khi xác định các thông tin trên, module `camera_ai` sẽ được triển khai cụ thể.

---

## 18. Mục tiêu kiến trúc

```text
                SMART FIRE SYSTEM
                       │
          ┌────────────┼────────────┐
          │            │            │
       Sensors      Camera AI    Communication
          │            │            │
          └────────────┼────────────┘
                       │
                       ▼
                    main.c
                       │
                       ▼
                   Actuators
                       │
                       ▼
                    MQTT
                       │
                       ▼
                   Node-RED
```

**Mục tiêu:** xây dựng một hệ thống chữa cháy thông minh có khả năng **cảm nhận → phân tích → quyết định → hành động → truyền thông tin** theo kiến trúc module hóa.
