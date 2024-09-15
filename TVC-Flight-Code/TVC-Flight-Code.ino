/*
 * TVC-Flight-Code
 * 
 * This is the source code for a software implementation of thrust vector control (TVC) for model rockets.
 * 이것은 모델 로켓용 추력 벡터 제어(TVC) 소프트웨어 구현을 위한 소스 코드입니다.
 * The software consists of a state machine and PID control loops to adjust the orientation of the rocket during its powered ascent.
 * 이 소프트웨어는 주 기계와 PID 제어 루프로 구성되어 로켓이 동력으로 상승하는 동안 로켓의 방향을 조정합니다.
 *
 * This version 1.0 was used for the first test flight of the rocket on Sep 03 2022.
 * 이 버전 1.0은 2022년 9월 3일 로켓의 첫 시험 비행에 사용되었습니다.
 *
 * @version 1.0
 * @author Tom Kuttler
 * @GitHub https://github.com/tomkuttler/TVC-Rocket-Flight-Code
 */

#include "StateMachine.h"

StateMachine *stateMachine;

void setup() {
  stateMachine = new StateMachine();
}

void loop() {
  stateMachine->stateMachineLoop();
}
