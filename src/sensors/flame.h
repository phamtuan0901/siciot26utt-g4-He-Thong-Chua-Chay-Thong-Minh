#ifndef FLAME_H
#define FLAME_H

<<<<<<< HEAD
=======
#include <Arduino.h>

>>>>>>> 5a27bb5f4ca3a0af90cb0ed49142c28bbe9d02e8
// Khai báo biến toàn cục để các file khác (như main hoặc mqtt) có thể đọc được
extern bool isFireDetected; 

void initFlameSensor();
void flameTask(void *param);

#endif