/*
 * PID-Controller
 * PID-제어기
 *
 * The orientation of the motor mount is calculated with two separate PID-Controllers
 * 모터 마운트의 방향은 두 개의 개별 PID 컨트롤러로 계산됩니다    
 */

#include <Wire.h>         //Wire.h는 아두이노에서 I2C 통신을 쉽게 할 수 있도록 Wire이라는 객체를 제공함.
#include <Arduino.h>      //Arduino.h는 많은 양의 정의와 표준 항목이 있어 다른 헤더 파일들을 포함하는 포괄적인 헤더 파일임.

class PID {
  public:
    PID(float Kp, float Ki, float Kd, float saturation);
    float update(float input);

  private:
    // Proportional gain      비례 게인 값
    float Kp = 0.0f;
    // Integral gain      적분 게인 값
    float Ki = 0.0f;
    // Derivative gain    미분 게인 값
    float Kd = 0.0f;

    // Loop interval time     루프 간격 시간
    float deltaTime = 0.0f;
    float error = 0.0f;
    float setpoint = 0.0f;
    float errorIntegral = 0.0f;
    float errorDerivative = 0.0f;
    float errorLastCycle = 0.0f;

    // Maximum value of manipulated variable (absolute value)     조작된 변수의 최대값 (절대값)
    float saturation = 0.0f;
    float output = 0.0f;

    unsigned long currentTime = 0.0;
    unsigned long previousTime = 0.0;
};
