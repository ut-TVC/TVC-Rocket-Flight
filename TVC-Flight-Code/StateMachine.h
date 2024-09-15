/*
 * State Machine 상태 장치
 * 
 * The code is divided into four states:
 * 이코드는 다음 4가지 상태를 다룹니다.
 * LAUNCH_PAD_IDLE (발사대 대기 상태)
 *   Check the acceleration of the rocket on vertical axis (수직축의 로켓의 가속도를 확인합니다.)
 * ASCENT(상승)
 *   Thrust vector control is active 추력 벡터 제어 활성화
 *   Flight data is logged to SD-Card    ‾\ 비행 데이터 를 SD 카드에 기록
 * DESCENT(하강)                           | Eject parachute (낙하산 동작)
 *   Flight data is logged to SD-Card   <-/ 비행 데이터 를 SD 카드에 기록
 * LANDED(착륙)
 *   No active code (computer waiting to be turned off) 동작 없음 (종료 대기)
 */

#include <Arduino.h>
#include <Wire.h>
#include "Rocket.h"

#define LIFT_THRESHOLD -2   // Acceleration on vertical axis/x-axis (negative value = acceleration upwards) (in m/s^2) // 수직축/x축에서의 가속도(음의 값 = 위로 가속도)(m/s^2 단위)

// Calculated with a flight simulation in AeroVECTOR https://github.com/GuidodiPasquo/AeroVECTOR
#define TIME_TO_APOGEE 4     // Time from start until rocket reaches max apogee and parachute will be ejected (in s) // 로켓이 최대 도달에 이르고 낙하산을 사용하기 까지의 시간
#define TIME_TO_LANDING 30   // Time from start until rocket lands (in s) 로켓이 착륙할떄 까지의 시간

enum State {
  LAUNCH_PAD_IDLE,
  ASCENT,
  DESCENT,
  LANDED
};

class StateMachine {
  public:
    StateMachine();
    void stateMachineLoop();
    bool liftOffCheck();
    bool maxApogeeCheck();
    bool landedCheck();

  private:
    Rocket rocket;
    State activeState;
};
