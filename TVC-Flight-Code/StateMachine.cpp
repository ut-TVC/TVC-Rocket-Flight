#include "StateMachine.h"

StateMachine::StateMachine() {
  activeState = LAUNCH_PAD_IDLE; // Default state     기본 상태

  rocket.sdCard.led.red();
}

void StateMachine::stateMachineLoop() {
  switch (activeState) {
    case LAUNCH_PAD_IDLE:
      rocket.padIdle();
      // Detect lift off -> Ascent flight   이륙 감지 -> 상승 비행
      if (liftOffCheck()) {
        // Save the time of lift off      이륙 시간 기록
        rocket.flightStartTime = millis();
        activeState = ASCENT;
        rocket.sdCard.led.green();
      }
      break;
    case ASCENT:
      // TVC active     TVC 작동
      // Log Data     로그 데이터
      rocket.ascent();
      // Detect max apogee -> Descent flight and eject Parachute    최대 고도 감지 -> 하강 비행 감지, 낙하산 전개 명령
      if (maxApogeeCheck()) {
        rocket.maxApogee();
        activeState = DESCENT;
        rocket.sdCard.led.blue();
      }
      break;
    case DESCENT:
      rocket.descent();
      // Log Data     로그 데이터
      // Detect landing     착륙 감지
      if (landedCheck()) {
        activeState = LANDED;
        rocket.sdCard.led.purple();
      }
      break;
    case LANDED:
      // Do nothing     아무것도 안함
      break;
  }
}

// Check if rocket has launched by looking at the acceleration on vertical axis (x-axis)
// 수직축(x축)의 가속도를 보고 로켓이 발사되었는지 확인
bool StateMachine::liftOffCheck() {
  if (rocket.acceleration.x < LIFT_THRESHOLD) {
    return true;
  }
  return false;
}

// Check if rocket has reached apogee by looking at the time it takes to reach apogee
// 로켓이 최대 고도에 도달하는 데 걸리는 시간을 살펴서 최대 고도에 도달했는지 확인
bool StateMachine::maxApogeeCheck() {
  if (rocket.flightTime > TIME_TO_APOGEE) {
    return true;
  }
  return false;
}

// Check if rocket has landed by looking at the time it takes to land
// 착륙하는 데 걸리는 시간을 살펴서 로켓이 착륙했는지 확인
bool StateMachine::landedCheck() {
  if (rocket.flightTime > TIME_TO_LANDING) {
    return true;
  }
  return false;
}
