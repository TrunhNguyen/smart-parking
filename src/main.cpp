#include <Arduino.h>
#include <WiFi.h>
#include "slot.h"
#include "barrier.h"
#include "api.h"

const char* ssid = "Trunh";
const char* password = "1234567898";

// --- GIỮ NGUYÊN SƠ ĐỒ CHÂN NHƯ CODE ĐẦU TIÊN ---
int slotPins[NUM_SLOTS] = {32, 14, 27, 26}; // 4 chân cảm biến IR cho 4 slot
SlotManager slots(slotPins);

#define RELAY_PIN 13 // Chân điều khiển rào chắn chuyển về chân 13
Barrier barrier(RELAY_PIN);

unsigned long lastSend = 0;
int lastAvailableSpots = -1; // Khởi tạo bằng -1 để ép chạy kiểm tra ngay lần đầu tiên

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

    // Mở rào ngay khi khởi động nếu bãi chưa đầy
    if (lastAvailableSpots > 0) {
        Serial.println("Khoi dong: Bai con cho -> Mo barrier");
        barrier.open();
    } else {
        Serial.println("Khoi dong: Bai da full -> Dong barrier");
        barrier.close();
    }
}

void loop() {
    slots.update();
    int currentAvailable = slots.getAvailable();

    // CHỈ XỬ LÝ KHI SỐ CHỖ TRỐNG CÓ SỰ THAY ĐỔI
    if (currentAvailable != lastAvailableSpots) {
        
        if (currentAvailable == 0) {
            // Trường hợp 1: Bãi vừa bị lấp đầy hoàn toàn -> ĐÓNG rào
            Serial.println("Bai da full -> Dong barrier!");
            barrier.close(); 
        } 
        else {
            // Trường hợp 2: Bãi từ trạng thái FULL chuyển sang CÒN CHỖ -> MỞ rào lại
            // Hoặc số chỗ trống thay đổi nhưng vẫn còn chỗ -> Cứ giữ rào mở
            Serial.println("Bai con cho -> Mo/Giu barrier luon mo");
            barrier.open(); 
        }

        // Cập nhật lại trạng thái để tránh lặp lại logic
        lastAvailableSpots = currentAvailable;
    }

    // --- XOÁ HOẶC COMMENT HÀM AUTO CLOSE ---
    // barrier.autoClose(5000); // Không dùng nữa vì muốn barrier luôn mở

    // Gửi dữ liệu lên API mỗi 5 giây
    if (millis() - lastSend > 5000) {
        sendParkingData(
            currentAvailable,
            slots.toJSON()
        );
        lastSend = millis();
    }
}