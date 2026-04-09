#ifndef API_H
#define API_H

#include <Arduino.h>

void sendParkingData(
    int available,
    String slotJSON
);

#endif