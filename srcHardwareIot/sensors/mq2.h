#ifndef MQ2_H
#define MQ2_H

void initMQ2();
int readMQ2();

bool detectSmoke(int value);
bool detectGas(int value);

#endif