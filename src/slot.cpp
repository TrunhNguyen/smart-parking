#include "slot.h"

SlotManager::SlotManager(int slotPins[NUM_SLOTS]) {
    for (int i = 0; i < NUM_SLOTS; i++) {
        pins[i] = slotPins[i];
        occupied[i] = false;
    }
}

void SlotManager::begin() {
    for (int i = 0; i < NUM_SLOTS; i++) {
        // SỬA TỪ INPUT THÀNH INPUT_PULLUP ĐỂ CHÂN ĐỌC KHÔNG BỊ NHIỄU LƠ LỬNG
        pinMode(pins[i], INPUT_PULLUP);
    }
}

void SlotManager::update() {
    for (int i = 0; i < NUM_SLOTS; i++) {
        int value = digitalRead(pins[i]);
        if (value == LOW)
            occupied[i] = true;   // Có xe che khuất
        else
            occupied[i] = false;  // Trống
    }
}

bool SlotManager::isOccupied(int index) {
    return occupied[index];
}

int SlotManager::getAvailable() {
    int count = 0;
    for (int i = 0; i < NUM_SLOTS; i++) {
        if (!occupied[i])
            count++;
    }
    return count;
}

String SlotManager::toJSON() {
    String json = "{";
    for (int i = 0; i < NUM_SLOTS; i++) {
        json += "\"slot";
        json += i;
        json += "\":";
        json += occupied[i] ? "1" : "0";
        if (i < NUM_SLOTS - 1)
            json += ",";
    }
    json += "}";
    return json;
}