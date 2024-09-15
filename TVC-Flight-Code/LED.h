/*
 * Common Anode LED
 * 
 * Changes color according to the state the Flight Controller is currently in 
 * 각 현재 비행 상태에따라 다음과 같이 색으로 표현한다. 
 *
 * STATE           | COLOR  
 * ----------------|-------- 
 * LAUNCH_PAD_IDLE | red     발사대 대기상태(비행전) -> 빨강
 * ASCENT          | green   상승 비행  -> 초록
 * DESCENT         | blue    하강  -> 파랑
 * LANDED          | purple  착륙 -> 보라
 */

#include <Arduino.h>

#define R_LED 41
#define G_LED 40
#define B_LED 39

class LED {
  public:
    LED();
    void red();
    void green();
    void blue();
    void purple();
    void off();     
};
