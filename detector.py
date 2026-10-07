import cv2
from ultralytics import YOLO
from config import (
    MODEL_PATH,
    CAMERA_WIDTH,
    SERVO_MIN_ANGLE,
    SERVO_MAX_ANGLE,
    CONFIDENCE
)


class FireDetector:

    def __init__(self):
        print("[YOLO] Dang tai model.")
        self.model = YOLO(MODEL_PATH)
        print("[YOLO] Model da load thanh cong")

    def calculate_servo_angle(self, center_x):


        """ 
        Chuyển vị trí X của lửa trên camera
        thành góc servo.
        """
        angle = (center_x / CAMERA_WIDTH) * 360.0
        return round(angle,2)

    def detect(self, frame):

        results = self.model(
            frame,
            conf=CONFIDENCE,
            verbose=False
        )

        fire_detected = False
        smoke_detected = False

        # Góc servo mục tiêu
        target_angle = None

        for result in results:
            for box in result.boxes:
                class_id = int(box.cls[0])
                confidence = float(box.conf[0])

                x1, y1, x2, y2 = map(
                    int,
                    box.xyxy[0]
                )

                # TÍNH TÂM BOUNDING BOX
                center_x = (x1 + x2) // 2
                center_y = (y1 + y2) // 2

                # SMOKE
                if class_id == 0:

                    smoke_detected = True

                    label = f"SMOKE {confidence:.2f}"

                # FIRE
                elif class_id == 1:

                    fire_detected = True

                    label = f"FIRE {confidence:.2f}"

                    center_x = (x1 + x2) // 2
                    center_y = (y1 + y2) // 2

                    # Tính góc servo
                    target_angle = self.calculate_servo_angle(
                        center_x
                    )

                else: continue
                # DRAW BOX
                cv2.rectangle(
                    frame,
                    (x1, y1),
                    (x2, y2),
                    (0, 0, 255),
                    2
                )

                cv2.circle(
                    frame,
                    (center_x, center_y),
                    5,
                    (255, 0, 0),
                    -1
                )

                cv2.putText(
                    frame,
                    label,
                    (x1, max(y1 - 10, 20)),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.7,
                    (0, 0, 255),
                    2
                )

                # Hiển thị góc
                if class_id == 1:

                    cv2.putText(
                        frame,
                        f"Servo: {target_angle} deg",
                        (x1, y2 + 25),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.7,
                        (255, 0, 0),
                        2
                    )

        return {
            "fire": fire_detected,
            "smoke": smoke_detected,
            "servo_angle": target_angle
        }