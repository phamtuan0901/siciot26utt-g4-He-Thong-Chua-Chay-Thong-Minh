#ifndef SENSOR_H
#define SENSOR_H

extern float temp;
extern float humidity;
extern bool fireCheck;

void initSensor();
void sensorTask(void *param);

#endif