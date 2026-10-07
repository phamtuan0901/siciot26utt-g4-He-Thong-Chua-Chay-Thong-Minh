#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "mqtt.h"
#include <ArduinoJson.h>

const char* MQTT_SERVER = "172.20.10.5";
const int MQTT_PORT = 1883;

const char* CAMERA_TOPIC = "hethongchuachaythongminh/gr04/camera";

bool cameraFire = false;
bool cameraSmoke = false;
float angleFire = 0.0;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void mqtt_callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message  [");
    Serial.print(topic);
    Serial.print("]: ");

    String message;
    for (unsigned int i = 0; i < length; i++){
        message += (char)payload[i];
    }

    if(String(topic) == CAMERA_TOPIC){
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc,message);
        if(error){
            Serial.println("JSON camera loi!");
            return;
        }
        //check thay lua
        cameraFire = doc["fire"] | false;

        //check thay khoi
        cameraSmoke = doc["smoke"] | false;

        //Lay goc
        angleFire = doc["servo_angle"];

        Serial.print("Camera FIRE: ");
        Serial.println(cameraFire);

        Serial.print("Camera SMOKE: ");
        Serial.println(cameraSmoke);

    }
    Serial.println();
}

void mqtt_init(){
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(mqtt_callback);
}

void mqtt_check(){
    if (!mqttClient.connected()){
        Serial.println("Ket noi toi MQTT...");

        String clientID = "ESP32_FIRE_01";

        if (mqttClient.connect(clientID.c_str())){
            mqttClient.subscribe(CAMERA_TOPIC);
            Serial.println("MQTT ket noi!");
            Serial.println(
                "Da subscribe camera topic"
            );
        }
        else{
            Serial.print("MQTT khong ket noi thanh cong, trang thai = ");
            Serial.println(mqttClient.state());
        }
    }

    mqttClient.loop();
}

void mqtt_publish(const char* topic, const char* message){
    if(mqttClient.connected()){
        mqttClient.publish(topic, message);
    }
}