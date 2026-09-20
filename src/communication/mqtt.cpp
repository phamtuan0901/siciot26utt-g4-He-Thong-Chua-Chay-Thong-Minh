#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "mqtt.h"

const char* MQTT_SERVER = "172.20.10.3";
const int MQTT_PORT = 1883;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Message received [");
    Serial.print(topic);
    Serial.print("]: ");

    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();
}

void mqtt_init()
{
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(mqtt_callback);
}

void mqtt_check()
{
    if (!mqttClient.connected())
    {
        Serial.println("Connecting to MQTT...");

        String clientID = "ESP32_PCCC";

        if (mqttClient.connect(clientID.c_str()))
        {
            Serial.println("MQTT connected!");

            // Topic mà ESP32 muốn nhận lệnh
            mqttClient.subscribe("pccc/actuator/pump");
        }
        else
        {
            Serial.print("MQTT connection failed, state = ");
            Serial.println(mqttClient.state());
        }
    }

    mqttClient.loop();
}

void mqtt_publish(const char* topic, const char* message)
{
    if (mqttClient.connected())
    {
        mqttClient.publish(topic, message);
    }
}