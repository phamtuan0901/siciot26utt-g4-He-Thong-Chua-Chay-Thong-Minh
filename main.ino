#include <Arduino.h>

#include "sensor.h"
#include "process.h"
#include "servo.h"
#include "relay.h"

void setup() {

  Serial.begin(115200);
  initSensor();
  initServo();
  initRelay();

  xTaskCreatePinnedToCore(
    sensorTask,
    "DHT11 Task",
    2048,
    NULL,
    1,
    NULL,
    0
  );
  xTaskCreatePinnedToCore(
    processTask,
    "Process Task",
    2048,
    NULL,
    2,
    NULL,
    1
  );
}
void loop() {
}
