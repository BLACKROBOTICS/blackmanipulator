#include <HardwareSerial.h>
#define TX_PIN 17
#define RX_PIN 16
#define TX_ENABLE_PIN 4
HardwareSerial DXL_SERIAL(2); // UART2 사용
void setup() {
  pinMode(TX_ENABLE_PIN, OUTPUT);
  digitalWrite(TX_ENABLE_PIN, LOW); // 수신 모드로 설정
  Serial.begin(57600); // USB 시리얼
  DXL_SERIAL.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN); // 다이나믹셀 시리얼, 57600만 지원
}

void loop() {
  if (Serial.available()) {
    digitalWrite(TX_ENABLE_PIN, HIGH); // 송신 모드
    while (Serial.available()) {
      DXL_SERIAL.write(Serial.read());
    }
    
    DXL_SERIAL.flush();
    delayMicroseconds(10);
    digitalWrite(TX_ENABLE_PIN, LOW); // 수신 모드
  }

  // DXL → USB
  if (DXL_SERIAL.available()) {
    Serial.write(DXL_SERIAL.read());
  }
}
