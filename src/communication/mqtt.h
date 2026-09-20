#ifndef MQTT
#define MQTT

void mqtt_init();
void mqtt_check();
void mqtt_publish(const char* topic, const char* message);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
