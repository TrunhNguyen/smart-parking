#include <Arduino.h>
#include <WiFi.h>
#include "slot.h"
#include "barrier.h"
#include "api.h"

const char* ssid = "Huykhoi";
const char* password = "12345677";

// --- GIỮ NGUYÊN SƠ ĐỒ CHÂN NHƯ CODE ĐẦU TIÊN ---
int slotPins[NUM_SLOTS] = {12, 14, 27, 26}; // 4 chân cảm biến IR cho 4 slot
SlotManager slots(slotPins);

#define RELAY_PIN 13 // Chân điều khiển rào chắn chuyển về chân 13
Barrier barrier(RELAY_PIN);

unsigned long lastSend = 0;
int lastAvailableSpots = 0; // Lưu số chỗ trống ở vòng lặp trước

void connectWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting WiFi...");
    }
    Serial.println("WiFi Connected");
}

void setup() {
    Serial.begin(115200);
    connectWiFi();
    slots.begin();
    barrier.begin();
    
    // Khởi tạo trạng thái ban đầu
    slots.update();
    lastAvailableSpots = slots.getAvailable();
}

void loop() {
    slots.update();
    int currentAvailable = slots.getAvailable();

    // CHỈ XỬ LÝ KHI SỐ CHỖ TRỐNG CÓ SỰ THAY ĐỔI
    if (currentAvailable != lastAvailableSpots) {
        
        if (currentAvailable == 0) {
            // Trường hợp 1: Bãi vừa bị lấp đầy hoàn toàn -> ĐÓNG rào ngay lập tức
            Serial.println("Bai da full -> Dong barrier khan cap!");
            barrier.close(); 
        } 
        else {
            // Trường hợp 2: Số chỗ trống thay đổi và bãi VẪN CÒN CHỖ
            Serial.println("Trang thai bai thay doi & van con cho -> Mo barrier trong 5s");
            barrier.open(); // Mở rào và reset mốc thời gian đếm ngược
        }

        // Cập nhật lại trạng thái cũ
        lastAvailableSpots = currentAvailable;
    }

    // Luôn luôn gọi hàm này để tự động đóng sau 5 giây (nếu rào đang mở)
    barrier.autoClose(5000);

    // Gửi dữ liệu lên API mỗi 5 giây
    if (millis() - lastSend > 5000) {
        sendParkingData(
            currentAvailable,
            slots.toJSON()
        );
        lastSend = millis();
    }
}