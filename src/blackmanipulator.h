#ifndef BLACKMANIPULATOR_H
#define BLACKMANIPULATOR_H

#include <Arduino.h>
#include <Dynamixel2Arduino.h>

// 🔽 여기에서 모든 설정 정의
#define TX_PIN 17
#define RX_PIN 16
#define DXL_DIR_PIN 4
#define DXL_SERIAL Serial2
#define DXL_PROTOCOL_VERSION 2.0

class blackmanipulator {
  private:
    Dynamixel2Arduino& dxl;

  public:
    blackmanipulator(Dynamixel2Arduino &dxl_ref);
    void begin();
    void loadARM();
    void setARM();
    void opengrip();
    void closegrip();
};

#endif
