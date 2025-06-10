#include "blackmanipulator.h"

// 생성자: 전역 dxl을 참조로 받아서 저장
blackmanipulator::blackmanipulator(Dynamixel2Arduino &dxl_ref) : dxl(dxl_ref) {
}

#define TX_PIN 17  // TX2 기본 핀
#define RX_PIN 16  // RX2 기본 핀
#define DXL_DIR_PIN 4  // 다이나믹셀 DIR 핀
#define DXL_SERIAL Serial2  // 다이나믹셀 시리얼 포트
using namespace ControlTableItem; 

void blackmanipulator::begin() {
    DXL_SERIAL.begin(57600, SERIAL_8N1, TX_PIN, RX_PIN);
}

void blackmanipulator::loadARM() {
    dxl.begin(57600);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

    // 모든 모터 초기화
    for (int i = 1; i <= 5; i++) {
        if (dxl.ping(i)) {  
            dxl.torqueOff(i);  
            dxl.setOperatingMode(i, OP_POSITION);
            dxl.torqueOn(i);
        }
    }
}

// 모터들을 초기 위치로 이동하는 함수
void blackmanipulator::setARM() {
    int IDarr[6] = {0, 1, 2, 3, 4, 5};  // ID 배열 (0번 무시)
    int setpos[6] = {0, 2048, 2617, 910, 1593, 2048};  // 초기 위치 배열
    
    for (int i = 1; i <= 5; i++) //모터 속도설정 함수
    dxl.writeControlTableItem(PROFILE_VELOCITY, i, 128);

    for (int i = 1; i <= 5; i++) {  
        if (dxl.ping(IDarr[i])) {
            dxl.setGoalPosition(IDarr[i], setpos[i]);  
        }
    }
    for (int i = 1; i <= 5; i++) //모터 속도설정 최고속도도
    dxl.writeControlTableItem(PROFILE_VELOCITY, i, 512);
}
