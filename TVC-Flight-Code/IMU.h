/*
 * Absolute Orientation Sensor BNO055     BNO055을 IMU 센서로 사용
 * https://www.adafruit.com/product/4646  
 * 
 * IMU = inertial measurement unit        IMU = 관성 측정 장치
 * 
 * Outputs the following data: angular velocity, acceleration and absolute orientation      다음 데이터를 출력: 각속도, 가속도, 절대 방향
 */

#include <Adafruit_BNO055.h>      //include는 무엇을 뜻하는가?
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include "VectorDefinition.h"

class IMU {
  public:
    IMU();
    Vector3 getGyros();
    Vector3 getAcceleration();
    Vector3 getOrientation();

  private:
    Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire1);
    sensors_event_t angVelocityData;
    sensors_event_t linearAccelerationData;
    sensors_event_t orientationData;
};
