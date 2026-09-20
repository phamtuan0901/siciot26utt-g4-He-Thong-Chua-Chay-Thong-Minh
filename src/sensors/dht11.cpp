<<<<<<< HEAD
// #include <Arduino.h>
// #include <DHT.h>
// #include "config.h"
// #include "sensor.h"

// DHT dht(DHT_PIN, DHT_TYPE);

// float temp = 0;
// float humidity = 0;

// bool fireCheck = false;

// void initSensor() {
//   dht.begin();
// }

// void sensorTask(void *param) {

//   while (true) {

//     temp = dht.readTemperature();
//     humidity = dht.readHumidity();

//     if (isnan(temp) || isnan(humidity)) {

//       Serial.println("Loi doc DHT11!");

//     } else {

//       Serial.print("Nhiet do: ");
//       Serial.print(temp);

//       Serial.print(" °C | Do am: ");
//       Serial.print(humidity);

//       Serial.println(" %");
//       if (temp >= FIRE_TEMP) {
//         fireCheck = true;
//       }
//       else if (temp < SAFE_TEMP) {
//         fireCheck = false;
//       }
//     }
//     vTaskDelay(pdMS_TO_TICKS(2000));
//   }
// }
=======
#include <Arduino.h>
#include <DHT.h>
#include "config.h"
#include "sensor.h"

DHT dht(DHT_PIN, DHT_TYPE);

float temp = 0;
float humidity = 0;

bool fireCheck = false;

void initSensor() {
  dht.begin();
}

void sensorTask(void *param) {

  while (true) {

    temp = dht.readTemperature();
    humidity = dht.readHumidity();

    if (isnan(temp) || isnan(humidity)) {

      Serial.println("Loi doc DHT11!");

    } else {

      Serial.print("Nhiet do: ");
      Serial.print(temp);

      Serial.print(" °C | Do am: ");
      Serial.print(humidity);

      Serial.println(" %");
      if (temp >= FIRE_TEMP) {
        fireCheck = true;
      }
      else if (temp < SAFE_TEMP) {
        fireCheck = false;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
>>>>>>> 5a27bb5f4ca3a0af90cb0ed49142c28bbe9d02e8
