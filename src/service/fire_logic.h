#ifndef FIRE_LOGIC_H
#define FIRE_LOGIC_H

#include "../sensors/sensor_data.h"

enum FireStatus {
    NORMAL,
    WARNING,
    FIRE
};

FireStatus detectFire(const SensorData& data);

const char* fireStatusToString(FireStatus status);

#endif