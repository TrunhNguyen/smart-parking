#include "barrier.h"

unsigned long openTime = 0;
bool isOpen = false;

Barrier::Barrier(int pin, int openA, int closeA) {
    servoPin = pin;
    openAngle = openA;
    closeAngle = closeA;
}

void Barrier::begin() {
    servo.attach(servoPin);
    close(); 
}

void Barrier::open() {
    servo.write(openAngle);
    isOpen = true;
    openTime = millis();
}

void Barrier::close() {
    servo.write(closeAngle);
    isOpen = false;
}

void Barrier::autoClose(unsigned long delayTime) {
    if (isOpen &&
        millis() - openTime > delayTime) {
        close();
    }
}