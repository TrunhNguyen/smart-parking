#include "barrier.h"

unsigned long openTime = 0;
bool isOpen = false;

Barrier::Barrier(int pin) {
    relayPin = pin;
}

void Barrier::begin() {
    pinMode(relayPin, OUTPUT);
    close();
}

void Barrier::open() {
    digitalWrite(relayPin, HIGH);
    isOpen = true;
    openTime = millis();
}

void Barrier::close() {
    digitalWrite(relayPin, LOW);
    isOpen = false;
}

void Barrier::autoClose(unsigned long delayTime) {
    if (isOpen &&
        millis() - openTime > delayTime) {
        close();
    }
}