#ifndef SLOT_H
#define SLOT_H

#include <Arduino.h>

// SỬA TỪ 5 THÀNH 4 ĐỂ ĐỒNG BỘ VỚI SƠ ĐỒ 4 CHÂN CẢM BIẾN
#define NUM_SLOTS 4

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