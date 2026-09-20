#include <Arduino.h>
#include "../config/config.h"
#include "relay.h"

void initRelay() {
  pinMode(RELAY_IN2, OUTPUT);
  digitalWrite(RELAY_IN2, LOW);
}

void relayOn() {
  digitalWrite(RELAY_IN2, HIGH);
  Serial.println("Relay ON - Bat bom nuoc");
}

void relayOff() {
  digitalWrite(RELAY_IN2, LOW);
  Serial.println("Relay OFF - Tat bom nuoc");
}