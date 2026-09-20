#ifndef FLAME_H
#define FLAME_H

// Khai báo biến toàn cục để các file khác (như main hoặc mqtt) có thể đọc được
extern bool isFireDetected; 

void initFlameSensor();
void flameTask(void *param);

#endif