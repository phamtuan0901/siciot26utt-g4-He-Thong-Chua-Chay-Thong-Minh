#include <Arduino.h>
<<<<<<< HEAD
#include "../config/config.h"
=======
#include "config.h"
>>>>>>> 5a27bb5f4ca3a0af90cb0ed49142c28bbe9d02e8
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