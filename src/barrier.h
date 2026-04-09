#ifndef BARRIER_H
#define BARRIER_H

#include <Arduino.h>
#include <ESP32Servo.h>

class Barrier {
private:

    Servo servo;          
    int servoPin;         
    int openAngle;        
    int closeAngle;      
    unsigned long openTime;
    bool isOpened;

public:

    Barrier(int pin, int openA = 90, int closeA = 0);
    void begin();
    void open();
    void close();
    void autoClose(unsigned long delayTime);
};

#endif