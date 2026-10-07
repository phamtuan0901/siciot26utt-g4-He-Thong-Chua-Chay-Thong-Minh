#include <Arduino.h>
#include "../config/config.h"
#include "mq2.h"

void initMQ2() {
    pinMode(MQ2_PIN, INPUT);
}

int readMQ2() {
    return analogRead(MQ2_PIN);
}

// bool detectGas(int value) {
//     return value >= GAS_THRESHOLD;
// }

// bool detectGas(int value) {
//     return value >= MQ2_GAS;
// }