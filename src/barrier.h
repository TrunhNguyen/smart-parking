#ifndef BARRIER_H
#define BARRIER_H

#include <Arduino.h>

class Barrier {
private:

    int relayPin;

public:

    Barrier(int pin);
    void begin();
    void open();
    void close();
    void autoClose(unsigned long delayTime);
};

#endif