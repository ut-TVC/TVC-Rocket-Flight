/*
 * Absolute Orientation Sensor BNO055     BNO055을 IMU 센서로 사용
 * https://www.adafruit.com/product/4646  
 * 
 * IMU = inertial measurement unit        IMU = 관성 측정 장치
 * 
 * Outputs the following data: angular velocity, acceleration and absolute orientation      다음 데이터를 출력: 각속도, 가속도, 절대 방향
 */

#include <Adafruit_BNO055.h>      //include는 작성된 파일의 내용을 가져와 적용 시키는 역할
#include <Adafruit_Sensor.h>      //Sensor.h는 Adafruit사의 센서 라이브러리를 사용하여 다른 센서로 교체 시 해당 센서의 라이브러리로의 교환이 필요함
#include <Wire.h>                 //Wire.h는 아두이노에서 I2C 통신을 쉽게 할 수 있도록 Wire이라는 객체를 제공함.
#include <Arduino.h>              //Arduino.h는 많은 양의 정의와 표준 항목이 있어 다른 헤더 파일들을 포함하는 포괄적인 헤더 파일임.
#include "VectorDefinition.h"     //VectorDefinition.h는 해당 TVC-Rocket-Flight에 존재하므로 해당 헤더파일에서 설명

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
