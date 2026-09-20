#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

void mqtt_init();
void mqtt_check();
void mqtt_publish(const char* topic, const char* message);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
