#include <Dynamixel2Arduino.h>
#include <ps5Controller.h>
#define TX_PIN 17  // TX2 기본 핀
#define RX_PIN 16  // RX2 기본 핀
#define DXL_SERIAL Serial2
#define DEBUG_SERIAL Serial
const int DXL_DIR_PIN = 4;  // DIR 핀
const float DXL_PROTOCOL_VERSION = 2.0;
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

void setARM(){
    int IDarr[6] = {0, 1, 2, 3, 4, 5};  // ID 배열 (0번은 무시)
    int setpos[6] = {0, 2048, 2617, 910, 1593, 2048};  // 초기 위치 배열 (0번은 무시)

    for(int i = 1; i <= 5; i++) // 1번 모터부터 5번 모터까지 실행
        dxl.setGoalPosition(IDarr[i], setpos[i]); 

}

void forward() {
    dxl.setGoalPosition(2, dxl.getPresentPosition(2) - 100);
    dxl.setGoalPosition(3, dxl.getPresentPosition(3) + 100 * 0.5);
    dxl.setGoalPosition(4, dxl.getPresentPosition(4) + 100 * 0.9);

}


void back(){
    dxl.setGoalPosition(2, dxl.getPresentPosition(2) + 100);
    dxl.setGoalPosition(3, dxl.getPresentPosition(3) - 100 * 0.5);
    dxl.setGoalPosition(4, dxl.getPresentPosition(4) - 100 * 0.5);
}


///---------------------------------------------------------------------------------------
void setup() {
  DXL_SERIAL.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN);  // 1,000,000 bps 설정
  dxl.begin(57600);  // Dynamixel Baudrate 설정
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);  // Protocol Version 설정


    for (int i = 1; i <= 5; i++) {
        dxl.ping(i);
        dxl.torqueOff(i);
        dxl.setOperatingMode(i, OP_POSITION);
        dxl.setGoalVelocity(i, 32767);
        dxl.torqueOn(i);
    }

  setARM();
  ps5.begin("00:00:00:00:00:00"); //자신의 듀얼센스 맥주소로 바꾸세요
}

void loop() {
  while (ps5.isConnected() == true) {

    // 오른쪽 스틱 Y방향, IK 계산하여 앞뒤로 움직임
    if (ps5.RStickY() >= 30)
      forward();
    else if (ps5.RStickY() <= -30)
      back();

  if(ps5.LStickX() >= 30)
    dxl.setGoalPosition(1, dxl.getPresentPosition(1)-60);
  else if(ps5.LStickX() <= -30)
    dxl.setGoalPosition(1, dxl.getPresentPosition(1)+60);


  if (ps5.Square()) 
    dxl.setGoalPosition(5, 2048);
  if (ps5.Circle()) 
    dxl.setGoalPosition(5, 2930);

  if(ps5.Triangle())
    setARM();

  }
}
