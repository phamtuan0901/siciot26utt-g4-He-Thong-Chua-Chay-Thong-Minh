#ifndef DHT11_H
#define DHT11_H

extern float temp;
extern float humidity;
extern bool fireCheck;

void initDHT11();
// void sensorTask(void *param);
bool readDHT11(float &temp, float &humidity);
#endif