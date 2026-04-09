#ifndef SLOT_H
#define SLOT_H

#include <Arduino.h>

#define NUM_SLOTS 5

class SlotManager {
private:

    int pins[NUM_SLOTS];
    bool occupied[NUM_SLOTS];

public:

    SlotManager(int slotPins[NUM_SLOTS]);
    void begin();
    void update();
    bool isOccupied(int index);
    int getAvailable();
    String toJSON();
};

#endif