#ifndef MQ2_H
#define MQ2_H

#include <Arduino.h>

// Khai báo biến toàn cục để các file khác có thể lấy dữ liệu nồng độ khói
extern int gasValue;
extern bool isGasDetected; // Biến cờ báo hiệu đã vượt ngưỡng nguy hiểm

void initMQ2();
void mq2Task(void *param);

#endif