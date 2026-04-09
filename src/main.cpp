#include <Arduino.h>
#include <WiFi.h>
#include "slot.h"
#include "barrier.h"
#include "api.h"

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

int slotPins[NUM_SLOTS] = {32,33,25,26,27};
SlotManager slots(slotPins);

#define RELAY_PIN 14

Barrier barrier(RELAY_PIN);

void connectWiFi() {

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting WiFi...");
    }
    Serial.println("WiFi Connected");
}

unsigned long lastSend = 0;

void setup() {
    Serial.begin(115200);
    connectWiFi();
    slots.begin();
    barrier.begin();
}

void loop() {
    slots.update();
    if (slots.getAvailable() > 0) {
        barrier.open();
    }
    barrier.autoClose(5000);
    if (millis() - lastSend > 5000) {
        sendParkingData(
            slots.getAvailable(),
            slots.toJSON()
        );
        lastSend = millis();
    }
}