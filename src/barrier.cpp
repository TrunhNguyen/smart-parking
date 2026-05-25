#include "barrier.h"

// XÓA BỎ 2 DÒNG KHAI BÁO BIẾN TOÀN CỤC Ở ĐÂY

Barrier::Barrier(int pin, int openA, int closeA) {
    servoPin = pin;
    openAngle = openA;
    closeAngle = closeA;
    openTime = 0;   // Khởi tạo giá trị ban đầu cho thuộc tính của class
    isOpened = false; 
}

void Barrier::begin() {
    // Để điều khiển Servo mượt hơn trên ESP32, nên cài thêm độ rộng xung (500, 2400)
    servo.setPeriodHertz(50);
    servo.attach(servoPin, 500, 2400); 
    close(); 
}

void Barrier::open() {
    servo.write(openAngle);
    isOpened = true;        // Sửa từ isOpen thành isOpened
    openTime = millis();    // Lúc này sẽ ghi vào thuộc tính private của class
}

void Barrier::close() {
    servo.write(closeAngle);
    isOpened = false;       // Sửa từ isOpen thành isOpened
}

void Barrier::autoClose(unsigned long delayTime) {
    // Chỉ tự động đóng nếu rào đang mở và đã quá thời gian delayTime
    if (isOpened && (millis() - openTime > delayTime)) {
        close();
    }
}