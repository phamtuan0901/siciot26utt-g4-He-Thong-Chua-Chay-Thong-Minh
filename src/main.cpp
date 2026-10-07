#include <Arduino.h>
#include "communication/wifi.h"
#include "communication/mqtt.h"
#include "sensors/sensor_task.h"
#include "service/fire_logic.h"
#include "actuators/relay.h"
#include "actuators/servo.h"
#include "config.h"
#include <json_parser.h>
void setup(){
    Serial.begin(115200);
    pinMode(25, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT); 

    digitalWrite(25, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);

    sensorsInit();
    initServo();
    initRelay();
    wifi_init();
    mqtt_init();
}
void loop() {
    
    mqtt_check();
    SensorData data = readAllSensors();
    FireStatus status = detectFire(data);

    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.print(" | Humidity: ");
    Serial.print(data.humidity);
    Serial.print(" | Gas: ");
    Serial.print(data.gasValue);
    Serial.print(" | Flame: ");
    Serial.print(data.flameDetected);
    Serial.print(" | Status: ");
    Serial.println(fireStatusToString(status));

    switch (status) {
        case NORMAL:
            digitalWrite(25, HIGH);
            digitalWrite(32, LOW);
            digitalWrite(14, LOW);
            digitalWrite(12, LOW);
            break;

        case WARNING:
            digitalWrite(25, LOW);
            digitalWrite(32, HIGH);
            digitalWrite(14, LOW);
            digitalWrite(12, LOW);
            break;

        case FIRE:
            digitalWrite(25, LOW);
            digitalWrite(32, LOW);
            digitalWrite(14, HIGH);
            digitalWrite(12, HIGH);
            break;
        
        default:
            digitalWrite(12, LOW);
            break;
    }

    if (status == FIRE) {
        moveToFirePosition(angleFire);
        relayOn();
    }

    else {
        relayOff();
        moveToHomePosition();
    }

    String payload = "{";
    payload += "\"temperature\":" + String(data.temperature, 2) + ",";
    payload += "\"humidity\":" + String(data.humidity, 2) + ",";
    payload += "\"gas\":" + String(data.gasValue) + ",";
    payload += "\"flame\":" + String(data.flameDetected ? 1 : 0) + ",";
    payload += "\"fireStatus\":\"" + String(fireStatusToString(status)) + "\"";
    payload += "}";

    mqtt_publish(
        "hethongchuachaythongminh/gr04",
        payload.c_str()
    );

    Serial.print("MQTT Payload: ");
    Serial.println(payload);
    delay(1000);
}

