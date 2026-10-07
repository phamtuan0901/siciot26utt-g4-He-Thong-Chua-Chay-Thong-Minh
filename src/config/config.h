#ifndef CONFIG_H
#define CONFIG_H

// ==================== PIN ====================

#define SERVO_PIN 27
#define RELAY_IN2 26

// DHT
#define DHT_TYPE DHT11
#define DHT_PIN 33

// Flame
#define FLAME_PIN 34

// MQ-2
#define MQ2_PIN 35

// ==================== THRESHOLD ====================

#define GAS_FIRE_THRESHOLD 700
#define GAS_WARN_THRESHOLD 400

#define TEMPERATURE_FIRE_THRESHOLD 35.0
#define TEMPERATURE_WARN_THRESHOLD 32.0

// Servo
#define HOME_ANGLE 0

#endif