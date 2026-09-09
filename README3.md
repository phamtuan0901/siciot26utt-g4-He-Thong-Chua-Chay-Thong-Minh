BÁO CÁO ĐỀ TÀI IoT: HỆ THỐNG CHỮA CHÁY THÔNG MINH
Phương pháp tiếp cận: Design Thinking (Tư duy Thiết kế)

Ngôn ngữ lập trình & Nền tảng: C (Embedded System), MQTT, Node-RED

PHẦN 1: BỐI CẢNH VÀ ĐẶT VẤN ĐỀ (PROBLEM & CONTEXT)
1.1. Bối cảnh thực tế
Hiện nay, các vụ hỏa hoạn tại các hộ gia đình kết hợp sản xuất/kinh doanh nhỏ (như xưởng may, kho chứa hàng, tiệm tạp hóa) gây ra thiệt hại nghiêm trọng về người và tài sản. Hầu hết các cơ sở này chỉ trang bị bình chữa cháy xách tay hoặc các đầu báo khói độc lập đơn giản.

1.2. Vấn đề tồn tại của các giải pháp hiện hành
Báo động giả cao: Các cảm biến khói truyền thống dễ bị kích động bởi bụi bẩn, khói bếp, hơi nước hoặc khói thuốc lá, dẫn đến việc người dùng có xu hướng ngắt kết nối thiết bị báo cháy do phiền toái.

Chữa cháy thụ động / Nhầm lẫn gây thiệt hại: Các hệ thống phun nước tự động cơ học (Sprinkler) chỉ nổ khi nhiệt độ đạt ngưỡng rất cao (trên 68 
∘
 C). Ngược lại, nếu kích hoạt phun nước khi chỉ dựa vào cảm biến khói, nguy cơ xả nước nhầm làm hỏng tài sản/hàng hóa là rất lớn.

Thiếu khả năng giám sát và cảnh báo từ xa: Người chủ cơ sở không nhận được thông tin thời gian thực khi không có mặt tại hiện trường để đưa ra quyết định xử lý kịp thời.

PHẦN 2: THẤU HỂU NGƯỜI DÙNG (EMPATHIZE)
2.1. Phương pháp khảo sát
Nhóm thực hiện quan sát và phỏng vấn trực tiếp 10 chủ cơ sở sản xuất nhỏ và chủ nhà ở kết hợp kinh doanh tại địa phương.

2.2. Kết quả tổng hợp Pain Points (Điểm đau người dùng)
Báo động giả: 8/10 người từng tắt báo cháy độc lập vì thiết bị kêu vô cớ khi nấu ăn hoặc có bụi.

Lo sợ thiệt hại thứ cấp: 9/10 người lo ngại việc hệ thống tự động xả nước/hóa chất chữa cháy khi chưa xác định chính xác có lửa thật hay không, gây hư hỏng toàn bộ máy móc, hàng hóa dệt may, điện tử.

Mất kiểm soát khi vắng mặt: 10/10 người muốn có thông báo tức thì qua điện thoại kèm hình ảnh/xác nhận trực quan thay vì chỉ có còi hú tại chỗ.

PHẦN 3: XÁC ĐỊNH BÀI TOÁN (DEFINE)
3.1. Chân dung người dùng (Persona)
Họ và tên: Nguyễn Văn Nam (38 tuổi).

Nghề nghiệp: Chủ xưởng may gia công quy mô 150m² tại tầng 1, gia đình sống ở tầng 2.

Nhu cầu: Cần một hệ thống phát hiện cháy chính xác, báo động kịp thời về điện thoại và chỉ tự động dập lửa khi có căn cứ chắc chắn.

Nỗi sợ: Báo động giả gây hoảng loạn cho gia đình; hệ thống tự phun nước làm hỏng hàng trăm cuộn vải và máy may công nghiệp.

3.2. Phát biểu góc nhìn (POV - Point of View)
"Anh Nam cần một hệ thống báo và chữa cháy tự động có độ tin cậy kép (kết hợp cảm biến và camera xác thực), bởi vì một quyết định xả nước nhầm do báo động giả sẽ phá hỏng toàn bộ hàng hóa dệt may của xưởng."

3.3. Câu hỏi Dẫn dắt Giải pháp (HMW - How Might We)
"Làm thế nào để hệ thống chữa cháy vừa phát hiện sự cố nhanh chóng trong vài giây đầu, vừa loại bỏ tối đa báo động giả trước khi kích hoạt thiết bị dập lửa tự động?"

PHẦN 4: ĐỀ XUẤT VÀ LỰA CHỌN GIẢI PHÁP (IDEATE)
4.1. Các phương án giải pháp xem xét
Tiêu chí	Phương án A: Cảm biến truyền thống	Phương án B: Chỉ dùng Camera AI (Cloud)	Phương án C: Cảm biến đa thông số + Edge Camera AI + Lập trình module C (Được chọn)
Mô tả	Cảm biến khói + còi hú độc lập.	Stream video lên Server/Cloud để chạy AI phát hiện lửa.	Kết hợp dữ liệu cảm biến (Nhiệt/Độ ẩm/Khói) với Camera AI xử lý tại chỗ/biên, điều khiển qua logic C.
Độ chính xác	Thấp (Dễ báo động giả).	Cao.	Rất cao (Xác thực chéo 2 lớp).
Độ trễ xử lý	Nhỏ (< 1s).	Lớn (Phụ thuộc băng thông mạng).	Rất nhỏ (< 2s).
Khả năng Offline	Có.	Không (Mất mạng là vô dụng).	Có (Vẫn tự động xử lý tại vi điều khiển).
Chi phí	Rất rẻ.	Cao (Chi phí Server/Vận hành).	Tối ưu / Phù hợp.
4.2. Lý do chọn Phương án C
Phương án C giải quyết triệt để điểm đau của người dùng: Xác thực chéo (Cross-verification) giữa cảm biến môi trường và hình ảnh AI giúp triệt tiêu báo động giả, đồng thời giữ được tính hoạt động độc lập (Offline) khi gặp sự cố ngắt mạng hoặc mất Wi-Fi.

PHẦN 5: THIẾT KẾ GIẢI PHÁP IoT (IOT SOLUTION DESIGN)
5.1. Kiến trúc tổng thể hệ thống
Plaintext
                    ┌─────────────────────┐
                    │      SENSORS        │
                    │ Temperature/Humidity│
                    │ Smoke / Gas         │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │      CAMERA AI      │
                    │ Image Processing    │
                    │ AI Detection        │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │       MAIN.C        │
                    │ Decision Logic      │
                    │ Cross-Verification  │
                    └───────┬─────┬───────┘
                            │     │
            ┌───────────────┘     └───────────────┐
            ▼                                     ▼
  ┌─────────────────┐                   ┌─────────────────┐
  │    ACTUATORS    │                   │  COMMUNICATION  │
  │ Servo / Pump    │                   │ MQTT / Wi-Fi    │
  │ Alarm / Relay   │                   └────────┬────────┘
  └─────────────────┘                            │
                                                 ▼
                                        ┌─────────────────┐
                                        │    Node-RED     │
                                        └─────────────────┘
5.2. Các thành phần chính của kiến trúc
Sensors (Thu thập dữ liệu): DHT11/DHT22 (Nhiệt độ, Độ ẩm), Cảm biến khói/khí gas. Nhiệm vụ chỉ đọc và kiểm tra tính hợp lệ của dữ liệu thô.

Camera AI (Xác thực hình ảnh): Thu nhận khung hình, xử lý nhận diện sự xuất hiện của ngọn lửa hoặc quầng khói bằng mô hình AI.

Main.c (Bộ não điều phối): Tiếp nhận dữ liệu từ sensors và camera_ai, thực hiện logic xác thực chéo để đưa ra quyết định hành động.

Actuators (Chấp hành): Điều khiển Servo (quay hướng phun), Relay/Máy bơm (xả chất chữa cháy), Còi/Đèn cảnh báo.

Communication (Truyền thông): Đóng gói dữ liệu chuẩn MQTT, gửi về Node-RED Dashboard phục vụ giám sát từ xa.

PHẦN 6: PHÁT TRIỂN PROTOTYPE (PROTOTYPE DEVELOPMENT)
6.1. Cấu trúc thư mục mã nguồn C (Mô hình Module hóa)
Plaintext
He-Thong-Chua-Chay-Thong-Minh/
│
├── src/
│   ├── actuators/       # Lập trình điều khiển Servo, Pump, Alarm, Relay
│   ├── communication/   # Lập trình Wi-Fi, MQTT client
│   ├── sensors/         # Lập trình đọc DHT11/DHT22, Cảm biến khói
│   ├── camera_ai/       # Lập trình khởi tạo camera, thu nhận frame, trả về kết quả AI
│   └── main.c           # Chương trình chính: Khởi tạo & Vòng lặp điều phối logic
│
├── .gitignore
└── README.md
6.2. Thuật toán xử lý logic xác thực chéo tại main.c
Plaintext
                  ┌──────────────────────┐
                  │ Read Sensors & AI    │
                  └──────────┬───────────┘
                             │
                             ▼
               ┌──────────────────────────┐
               │ Temp > Threshold OR      │
               │ Smoke > Threshold?       │
               └─────────────┬────────────┘
                             │
             ┌───────────────┴───────────────┐
            NO                              YES
             │                               │
             ▼                               ▼
     ┌───────────────┐             ┌───────────────────┐
     │ Monitor Mode  │             │ AI Fire Detected? │
     └───────────────┘             └─────────┬─────────┘
                                             │
                             ┌───────────────┴───────────────┐
                            NO                              YES
                             │                               │
                             ▼                               ▼
                     ┌───────────────┐               ┌───────────────┐
                     │ Warning Level │               │ FIRE ALARM!   │
                     │  (Send MQTT)  │               │ - Turn Pump   │
                     │ No Pump Water │               │ - Turn Alarm  │
                     └───────────────┘               │ - Send MQTT   │
                                                     └───────────────┘
PHẦN 7: KIỂM THỬ VÀ ĐÁNH GIÁ (TEST & EVALUATION)
7.1. Bảng kịch bản kiểm thử kỹ thuật (Technical Metrics & Functional Test)
Nội dung test	Điều kiện thử nghiệm	Tiêu chí Pass/Fail	Kết quả đạt được	Trạng thái
Độ trễ phản ứng	Đốt lửa thật trong phạm vi 1.5m	Thời gian từ khi có lửa đến khi bật còi < 3 giây	1.8 giây	PASS
Chống báo động giả	Thổi khói thuốc / Bụi mịn gần cảm biến	Cảm biến báo khói nhưng Camera không thấy lửa -> Không bật bơm nước	Bật cảnh báo vàng trên Node-RED, không phun nước	PASS
Truyền nhận dữ liệu	Đặt thiết bị hoạt động liên tục 1 giờ	Tỷ lệ gửi packet MQTT thành công > 99%	99.4%	PASS
Hoạt động Offline	Ngắt kết nối Wi-Fi/Router	Khi có cháy thật, Servo & Bơm vẫn tự kích hoạt tại chỗ	Hệ thống tự xử lý độc lập thành công	PASS
7.2. Kết quả kiểm thử người dùng (User Test)
Mời 3 người dùng (trong đó có đại diện Persona - chủ xưởng) trải nghiệm thử nghiệm kịch bản báo động giả (khói bếp).

Đánh giá: Người dùng đánh giá cao tính năng "Cảnh báo phân cấp" — chỉ gửi thông báo nhắc nhở khi có khói/nhiệt nhẹ và chỉ tự động xả nước khi Camera AI xác nhận có ngọn lửa bùng phát.

PHẦN 8: VÒNG LẬP CẢI TIẾN VÀ HƯỚNG MỞ RỘNG (ITERATION & FUTURE WORK)
8.1. Vòng lặp cải tiến đã thực hiện (Iteration 1)
Phản hồi ban đầu: Khi thử nghiệm AI nhận diện hình ảnh trong điều kiện thiếu sáng, mô hình AI phản ứng chậm (mất > 4 giây).

Hành động cải tiến: Tối ưu hóa lại kích thước đầu vào khung hình (Downscale resolution) và bổ sung LED trợ sáng tự động kích hoạt khi cảm biến nhiệt phát hiện sự gia tăng bất thường, giảm thời gian xử lý AI xuống còn 1.8 giây.

8.2. Hạn chế hiện tại
Phần cứng vi điều khiển thử nghiệm chạy AI trực tiếp còn giới hạn về số khung hình trên giây (FPS).

Servo hiện tại chỉ quay theo góc cố định, chưa thể quét tự động tìm tâm điểm ngọn lửa.

8.3. Hướng phát triển tiếp theo
Chuyển đổi module Camera AI sang chip chuyên dụng hỗ trợ NPU biên (Edge AI) như ESP32-S3 hoặc K210 để tăng FPS.

Nâng cấp module Actuator thành cụm Servo Pan-Tilt (quay 2 trục X-Y) giúp vòi phun tự động dò và xịt chính xác vào gốc lửa.

Tích hợp thêm module giao tiếp SIM/GSM dự phòng để nhắn tin SMS và gọi điện khẩn cấp cho chủ nhà khi mạng Wi-Fi bị đứt hoặc mất điện toàn phần.
