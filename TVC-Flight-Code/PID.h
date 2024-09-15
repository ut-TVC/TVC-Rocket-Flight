/*
 * PID-Controller
 * PID-제어기
 *
 * The orientation of the motor mount is calculated with two separate PID-Controllers
 * 모터 마운트의 방향은 두 개의 개별 PID 컨트롤러로 계산 됩니다.
 */

#include <Wire.h>
#include <Arduino.h>

class PID {
  public:
    PID(float Kp, float Ki, float Kd, float saturation);
    float update(float input);

  private:
    // Proportional gain
    float Kp = 0.0f;
    // Integral gain
    float Ki = 0.0f;
    // Derivative gain
    float Kd = 0.0f;

    // Loop interval time
    float deltaTime = 0.0f;
    float error = 0.0f;
    float setpoint = 0.0f;
    float errorIntegral = 0.0f;
    float errorDerivative = 0.0f;
    float errorLastCycle = 0.0f;

    // Maximum value of manipulated variable (absolute value)
    float saturation = 0.0f;
    float output = 0.0f;

    unsigned long currentTime = 0.0;
    unsigned long previousTime = 0.0;
};
