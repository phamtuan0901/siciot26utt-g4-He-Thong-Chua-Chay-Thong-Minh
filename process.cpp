#include <Arduino.h>

#include "process.h"
#include "sensor.h"
#include "servo.h"
#include "relay.h"

enum SystemState {
  NORMAL,
  FIRE
};

SystemState state = NORMAL;

void processTask(void *param) {

  while (true) {
    if (state == NORMAL) {

      if (fireCheck) {

        Serial.println();
        Serial.println("🔥 PHAT HIEN CHAY!");

        Serial.println("Servo dang quay...");
        moveToFirePosition();

        Serial.println("Servo da den vi tri!");
        relayOn();

        state = FIRE;
      }
    }
    else if (state == FIRE) {
      if (!fireCheck) {

        Serial.println();
        Serial.println("🌡 Nhiet do da giam!");
        relayOff();

        vTaskDelay(pdMS_TO_TICKS(500));
        Serial.println("Servo dang quay ve...");

        moveToHomePosition();

        Serial.println("✅ He thong tro lai NORMAL");

        state = NORMAL;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(200));
  }
}