#include <Arduino.h>
#include "sensor_task.h"

#include "dht11.h"
#include "flame.h"
#include "mq2.h"


void sensorsInit(){
    // Khởi tạo DHT11
    initDHT11();

    // Khởi tạo cảm biến lửa
    initFlame();

    // Khởi tạo MQ-2
    initMQ2();
}


SensorData readAllSensors(){

    SensorData data;
    float temperature = 0.0;
    float humidity = 0.0;

    bool dhtSuccess = readDHT11(temperature, humidity);

    if (dhtSuccess){
        data.temperature = temperature;
        data.humidity = humidity;
    }
    else{
        data.temperature = -1;
        data.humidity = -1;
        Serial.println("Loi doc DHT11");
    }


    // Flame sensor
    data.flameDetected = readFlame();

    
    // MQ-2
    data.gasValue = readMQ2();


    return data;
}