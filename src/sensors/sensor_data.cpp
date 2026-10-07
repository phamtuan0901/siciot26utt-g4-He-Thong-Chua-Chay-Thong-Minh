#include "sensor_data.h"

void resetSensorData(SensorData& data) {
    data.temperature = 0.0f;
    data.humidity = 0.0f;
    data.gasValue = 0;
    data.flameDetected = false;
}