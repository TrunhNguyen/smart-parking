#include <WiFi.h>
#include <HTTPClient.h>

#include "api.h"

String serverURL = "http://192.168.1.10:8000/api/.../";

void sendParkingData(
    int available,
    String slotJSON
) {

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverURL);
        http.addHeader(
            "Content-Type",
            "application/json"
        );
        String body = "{";
        body += "\"available\":";
        body += available;
        body += ",";
        body += "\"slots\":";
        body += slotJSON;
        body += "}";
        int response = http.POST(body);
        Serial.print("HTTP: ");
        Serial.println(response);
        http.end();
    }
}