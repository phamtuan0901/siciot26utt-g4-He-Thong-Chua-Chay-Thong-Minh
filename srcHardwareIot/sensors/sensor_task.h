#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "../sensors/sensor_data.h"

// Khởi tạo tất cả cảm biến
void sensorsInit();

// Đọc tất cả cảm biến và trả về SensorData
SensorData readAllSensors();

#endif