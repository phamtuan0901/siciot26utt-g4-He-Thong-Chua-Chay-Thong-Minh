#include <Arduino.h>
#include <DHT.h>
#include "../config/config.h"
#include "../sensors/dht11.h"

DHT dht(DHT_PIN, DHT_TYPE);

float temp = 0;
float humidity = 0;

bool fireCheck = false;

void initDHT11() {
  dht.begin();
}

// void sensorTask(void *param) {

//   while (true) {

//     temp = dht.readTemperature();
//     humidity = dht.readHumidity();

//     if (isnan(temp) || isnan(humidity)) {

//       Serial.println("Loi doc DHT11!");

//     } 
//     else {
//       Serial.print("Nhiet do: ");
//       Serial.print(temp);
//       Serial.print(" °C | Do am: ");
//       Serial.print(humidity);
//         Serial.println(" %");
      
//     }
//     vTaskDelay(pdMS_TO_TICKS(2000));
//   }
// }

bool readDHT11(float& temperature, float& humidity){
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if(isnan(temperature) || isnan(humidity)){
      return false;
    }
    return true;
}