import cv2
import threading
import time

from config import CAMERA_WIDTH, CAMERA_HEIGHT

from detector import FireDetector
from mqtt_handler import MQTTHandler

print("[SYSTEM] Starting...")

detector = FireDetector()

mqtt = MQTTHandler()


cap = cv2.VideoCapture(0)

cap.set(
    cv2.CAP_PROP_FRAME_WIDTH,
    CAMERA_WIDTH
)

cap.set(
    cv2.CAP_PROP_FRAME_HEIGHT,
    CAMERA_HEIGHT
)

cap.set(
    cv2.CAP_PROP_BUFFERSIZE,
    1
)


if not cap.isOpened():
    print("[CAMERA] Khong mo duoc camera")
    raise SystemExit


print("[CAMERA] Camera started")


latest_frame = None

latest_result = {
    "fire": False,
    "servo_angle": 0,
    "boxes": []
}


frame_lock = threading.Lock()

result_lock = threading.Lock()

running = True


def detection_worker():

    global latest_frame
    global latest_result
    global running

    print("[AI] Detection thread started")

    while running:

        with frame_lock:
            if latest_frame is None:
                frame = None
            else:
                frame = latest_frame.copy()

        if frame is None:
            time.sleep(0.01)
            continue

        try:
            result = detector.detect(frame)

            with result_lock:
                latest_result = result

        except Exception as e:
            print("[AI] Detector error:", e)

        time.sleep(0.01)


ai_thread = threading.Thread(
    target=detection_worker,
    daemon=True
)

ai_thread.start()

fire_start_time = None          # Lưu mốc thời gian bắt đầu thấy lửa liên tục
REQUIRED_FIRE_SECONDS = 5.0    # Ngưỡng cấu hình thời gian (giây) để khóa góc (Bạn có thể đổi thành 15 hoặc bất cứ số giây nào)
angle_locked = False
locked_servo_angle = 0


print("[SYSTEM] Running")

while True:

    ret, frame = cap.read()

    if not ret:
        print("[CAMERA] Khong doc duoc frame")
        break

    with frame_lock:
        latest_frame = frame.copy()

    with result_lock:
        result = latest_result.copy()

    fire_detected = result["fire"]
    current_servo_angle = result["servo_angle"]
    boxes = result["boxes"]


    # ========================================================
    # DRAW BOUNDING BOXES
    # ========================================================

    for box in boxes:

        x1 = box["x1"]
        y1 = box["y1"]
        x2 = box["x2"]
        y2 = box["y2"]
        confidence = box["confidence"]
        class_name = box["class_name"]

        if "fire" in class_name.lower():
            box_color = (0, 0, 255)
        else:
            box_color = (0, 255, 0)

        cv2.rectangle(frame, (x1, y1), (x2, y2), box_color, 2)

        label = f"{class_name} {confidence:.2f}"
        cv2.putText(frame, label, (x1, max(y1 - 10, 20)), cv2.FONT_HERSHEY_SIMPLEX, 0.6, box_color, 2)

        center_x = (x1 + x2) // 2
        center_y = (y1 + y2) // 2
        cv2.circle(frame, (center_x, center_y), 5, box_color, -1)


    # ========================================================
    # FIRE TIME-BASED THRESHOLD & LOCK LOGIC
    # ========================================================

    if fire_detected:
        if not angle_locked:
            # Nếu mới bắt đầu thấy lửa, ghim mốc thời gian
            if fire_start_time is None:
                fire_start_time = time.time()

            elapsed_time = time.time() - fire_start_time
            remaining_time = max(0.0, REQUIRED_FIRE_SECONDS - elapsed_time)
            
            status = f"CHECKING FIRE... ({elapsed_time:.1f}s / {REQUIRED_FIRE_SECONDS}s)"
            print(f"🔥 Đang cháy liên tục: {elapsed_time:.1f}s / {REQUIRED_FIRE_SECONDS}s")

            # Kiểm tra xem thời gian cháy liên tục có vượt qua ngưỡng cấu hình (ví dụ 15s) chưa
            if elapsed_time >= REQUIRED_FIRE_SECONDS:
                angle_locked = True
                locked_servo_angle = current_servo_angle
                print(f"🔒 ĐÃ CHÁY QUÁ {REQUIRED_FIRE_SECONDS} GIÂY! Khóa góc servo tại: {locked_servo_angle} độ và gửi MQTT.")

                # Gửi lệnh sang ESP32 một lần duy nhất
                mqtt.publish({
                    "fire": True,
                    "servo_angle": locked_servo_angle
                })
        else:
            # Đã khóa góc thành công sau khi vượt ngưỡng thời gian
            status = f"FIRE LOCKED - Servo fixed at: {locked_servo_angle} deg"
    else:
        # Nếu mất lửa, reset lại mốc thời gian để đảm bảo phải cháy liên tục đủ thời gian mới kích hoạt
        if not angle_locked:
            if fire_start_time is not None:
                print("⚠️ Lửa bị ngắt quãng, reset lại bộ đếm thời gian!")
            fire_start_time = None
            status = "NORMAL (Scanning...)"
        else:
            # Nếu trước đó đã khóa và gửi MQTT, nhưng giờ lửa đã tắt hẳn hoàn toàn
            status = "FIRE EXTINGUISHED / RESET"
            angle_locked = False
            fire_start_time = None

    if angle_locked:
        text_color = (0, 0, 255)      # Đỏ đậm khi đã khóa góc
    elif fire_detected:
        text_color = (0, 165, 255)    # Cam khi đang trong quá trình đếm thời gian
    else:
        text_color = (0, 255, 0)      # Xanh khi bình thường

    cv2.putText(
        frame,
        status,
        (20, 40),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.8,
        text_color,
        2
    )

    cv2.putText(
        frame,
        "Press Q to quit",
        (20, CAMERA_HEIGHT - 20),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.6,
        (255, 255, 255),
        2
    )

    cv2.imshow("Smart Fire Detection", frame)

    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

running = False

ai_thread.join(timeout=2)

cap.release()

cv2.destroyAllWindows()

mqtt.disconnect()

print("Da thoat chuong trinh")