#include "blackmanipulator.h"
#include <Dynamixel2Arduino.h>
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
blackmanipulator arm(dxl);
void setup() {
  DXL_SERIAL.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN);
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  arm.loadARM();
  arm.setARM();
}

void loop() {
}
