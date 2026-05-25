#include <WiFi.h>
#include <HTTPClient.h>
#include "api.h"

// Bạn nhớ thay đoạn "..." bằng endpoint chuẩn của backend nhé (ví dụ: update)
String serverURL = "http://192.168.1.10:8000/api/.../";

void sendParkingData(int available, String slotJSON) {

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverURL);
        http.addHeader("Content-Type", "application/json");
        
        // Đóng gói JSON payload
        String body = "{";
        body += "\"available\":";
        body += available;
        body += ",";
        body += "\"slots\":";
        body += slotJSON;
        body += "}";
        
        // --- THÊM DÒNG NÀY ĐỂ DEBUG TRÊN SERIAL MONITOR ---
        Serial.print("Payload gui len server: ");
        Serial.println(body);
        
        // Thực hiện gửi POST request
        int response = http.POST(body);
        
        Serial.print("HTTP Response Code: ");
        Serial.println(response);
        
        http.end();
    } else {
        Serial.println("Loi: ESP32 chua ket noi duoc WiFi!");
    }
}