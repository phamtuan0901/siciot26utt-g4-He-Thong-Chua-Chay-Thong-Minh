<<<<<<< HEAD
#ifndef MQTT
#define MQTT
=======
#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H
>>>>>>> 5a27bb5f4ca3a0af90cb0ed49142c28bbe9d02e8

void mqtt_init();
void mqtt_check();
void mqtt_publish(const char* topic, const char* message);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
