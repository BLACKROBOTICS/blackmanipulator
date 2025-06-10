/*
작성자: BLACKROBOTICS co / hansol lim
작성일: 2025 / 04 / 10
*/

#include "blackmanipulator.h"
#include <Dynamixel2Arduino.h>
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
blackmanipulator arm(dxl);
void setup() {
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);
  DXL_SERIAL.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN);
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  arm.loadARM();
  arm.setARM();

}

void loop() {
  dxl.setGoalPosition(1, 3072);
  delay(2000);
  dxl.setGoalPosition(1, 2048);
  delay(2000);
  dxl.setGoalPosition(1, 1024);
  delay(2000);  
  dxl.setGoalPosition(1, 2048);
  delay(2000);
  
}
