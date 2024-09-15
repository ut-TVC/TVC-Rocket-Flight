/*
 * PID Controller, inspired by https://gist.github.com/bradley219/5373998
 */

#include "PID.h"

PID::PID(float Kp, float Ki, float Kd, float saturation) {      // 정의하는 부분
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  this->saturation = saturation;
}

float PID::update(float input) {
  // Calculate delata time      지연 계산 시간
  currentTime = micros();
  deltaTime = (currentTime - previousTime) / 1000000.0f;

  // Calculate error      계산 오류
  error = setpoint - input;

  // Integral term      적분항
  errorIntegral += error * deltaTime;

  // Derivative term      도함수
  errorDerivative = (error - errorLastCycle) / deltaTime;

  // Calculate total output     총 계산 산출값. 각 게인 값에 에러값을 곱하여 output 계산
  output = Kp * error + Ki * errorIntegral + Kd * errorDerivative;

  // Save current error and time for next cycle     다음 주기를 위해 현재 에러 저장
  errorLastCycle = error;
  previousTime = currentTime;

  // Check if output is in saturation     출력이 포화상태인지 확인
  if (output > saturation) {
    output = saturation;
  } else if (output < -saturation) {
    output = -saturation;
  }

  return output;
}
