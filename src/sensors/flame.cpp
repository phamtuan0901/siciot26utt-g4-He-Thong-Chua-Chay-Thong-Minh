#include <Arduino.h>
#include "../config/config.h"
#include "flame.h"

void initFlame() {
    pinMode(FLAME_PIN, INPUT);
}

bool readFlame() {
    return digitalRead(FLAME_PIN) == LOW;
}