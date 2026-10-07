import cv2

from config import CAMERA_WIDTH, CAMERA_HEIGHT
from detector import FireDetector
from mqtt_handler import MQTTHandler


detector = FireDetector()
mqtt = MQTTHandler()
cap = cv2.VideoCapture(0)

angle_locked = False
fire_state = False

cap.set(
    cv2.CAP_PROP_FRAME_WIDTH,
    CAMERA_WIDTH
)

cap.set(
    cv2.CAP_PROP_FRAME_HEIGHT,
    CAMERA_HEIGHT
)

if not cap.isOpened():

    print("Khong mo duoc camera")
    raise SystemExit


while True:

    ret, frame = cap.read()

    if not ret:

        print("Khong doc duoc frame")
        break

    result = detector.detect(frame)

    fire_detected = result["fire"]
    smoke_detected = result["smoke"]
    servo_angle = result["servo_angle"]

    if fire_detected:
        if not angle_locked:
            mqtt.publish({
                "fire": fire_detected,
                "smoke": smoke_detected,
                "servo_angle": servo_angle
            })
            angle_locked = True 
            fire_state = True
        else:
            pass
    else:
        
        if fire_detected:
            status = f"FIRE - SERVO {servo_angle} deg"

        elif smoke_detected:
            status = "SMOKE DETECTED!"

        else:

            status = "NORMAL"

        cv2.putText(
            frame,
            status,
            (20, 40),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (0, 0, 255) if fire_detected else (0, 255, 0),
            3
        )

        # =========================
        # DISPLAY
        # =========================

        cv2.imshow(
            "Smart Fire Detection",
            frame
        )

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    
cap.release()
cv2.destroyAllWindows()

if mqtt.client is not None:
    mqtt.client.disconnect()

print("Da thoat chuong trinh")