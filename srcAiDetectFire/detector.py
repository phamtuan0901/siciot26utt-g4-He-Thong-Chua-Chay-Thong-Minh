from ultralytics import YOLO
from config import (
    MODEL_PATH,
    CONFIDENCE,
    IMAGE_SIZE,
    SERVO_MIN_ANGLE,
    SERVO_MAX_ANGLE
)


class FireDetector:

    def __init__(self):

        print("[YOLO] Loading model...")

        self.model = YOLO(MODEL_PATH)

        print("[YOLO] Model loaded")

        print("[YOLO] Classes:")

        for class_id, class_name in self.model.names.items():
            print(f"    {class_id}: {class_name}")

        # Góc servo đã làm mượt
        self.smoothed_angle = None

        # EMA cho góc servo (giảm alpha xuống 0.15 để góc quay mượt và đỡ giật hơn)
        self.alpha = 0.15

        # Bộ đếm chống nhiễu / chống nhảy trạng thái lửa
        self.fire_lost_counter = 0
        self.max_lost_frames = 6  # Giữ trạng thái fire trong 6 frame nếu bị mất tạm thời
        self.last_fire_status = False
        self.last_best_fire = None

    def detect(self, frame):

        results = self.model.predict(
            source=frame,
            conf=CONFIDENCE,
            imgsz=IMAGE_SIZE,
            verbose=False
        )

        result_data = {
            "fire": False,
            "servo_angle": SERVO_MIN_ANGLE,
            "boxes": [],
            "frame": frame
        }

        if not results or results[0].boxes is None:
            # Nếu model không bắt được object trong frame này, kiểm tra bộ đếm giữ trạng thái
            if self.last_fire_status and self.fire_lost_counter < self.max_lost_frames:
                self.fire_lost_counter += 1
                result_data["fire"] = True
                best_fire = self.last_best_fire
            else:
                self.fire_lost_counter = 0
                self.last_fire_status = False
                self.last_best_fire = None
                return result_data
        else:
            result = results[0]
            annotated_frame = result.plot()
            result_data["frame"] = annotated_frame

            best_fire = None

            for box in result.boxes:

                x1, y1, x2, y2 = map(
                    int,
                    box.xyxy[0].tolist()
                )

                confidence = float(box.conf[0])
                class_id = int(box.cls[0])
                class_name = self.model.names[class_id]
                class_name_lower = class_name.lower()

                # Chỉ xử lý khi phát hiện FIRE, bỏ qua SMOKE
                if "fire" in class_name_lower:
                    if (
                        best_fire is None
                        or confidence > best_fire["confidence"]
                    ):
                        best_fire = {
                            "x1": x1,
                            "y1": y1,
                            "x2": x2,
                            "y2": y2,
                            "confidence": confidence
                        }

                result_data["boxes"].append({
                    "x1": x1,
                    "y1": y1,
                    "x2": x2,
                    "y2": y2,
                    "confidence": confidence,
                    "class_id": class_id,
                    "class_name": class_name
                })

            if best_fire is not None:
                result_data["fire"] = True
                self.fire_lost_counter = 0
                self.last_fire_status = True
                self.last_best_fire = best_fire
            else:
                if self.last_fire_status and self.fire_lost_counter < self.max_lost_frames:
                    self.fire_lost_counter += 1
                    result_data["fire"] = True
                    best_fire = self.last_best_fire
                else:
                    self.fire_lost_counter = 0
                    self.last_fire_status = False
                    self.last_best_fire = None

        # =========================
        # TÍNH GÓC SERVO
        # =========================

        if best_fire is not None:

            center_x = (
                best_fire["x1"]
                + best_fire["x2"]
            ) / 2

            frame_width = frame.shape[1]

            ratio = center_x / frame_width

            target_angle = (
                SERVO_MIN_ANGLE
                + ratio
                * (
                    SERVO_MAX_ANGLE
                    - SERVO_MIN_ANGLE
                )
            )

            target_angle = max(
                SERVO_MIN_ANGLE,
                min(
                    SERVO_MAX_ANGLE,
                    target_angle
                )
            )

            # =========================
            # EMA SMOOTHING
            # =========================

            if self.smoothed_angle is None:

                self.smoothed_angle = target_angle

            else:

                self.smoothed_angle = (
                    self.alpha * target_angle
                    + (1 - self.alpha)
                    * self.smoothed_angle
                )

            result_data["servo_angle"] = round(
                self.smoothed_angle
            )

        return result_data