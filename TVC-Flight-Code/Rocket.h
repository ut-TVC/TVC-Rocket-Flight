/*
 * Rocket code file
 * 로켓 코드 
 *
 * Contains code that will be run in a specific state
 * Functions are called in StateMachine.cpp
 * Header file contains all constants that are specific to the model rocket
 *
 * 각 상세 상태값들에대해 포함되어 있습니다.
 * 실제 기능들을 `SatateMachine.cpp` 으로부터 불러옵니다.
 * 헤더 파일에는 모델 로켓에 고유한 모든 상수가 포함되어 있습니다.
 */

#include <Wire.h>
#include <Arduino.h>
#include <Servo.h>
#include "IMU.h"
#include "BMP.h"
#include "PID.h"
#include "SDCard.h"
#include "VoltageDivider.h"

#define Y_SERVO_PIN 3               // Y Servo (y axis labeled on IMU) = Y Servo (labeled on pcb) IMU 에 라벨링된 Y servo = PCB에 라벨링된 Y servo
#define Z_SERVO_PIN 2               // Z Servo (z axis labeled on IMU) = X Servo (labeled on pcb) IMU 에 라벨링된 Z servo = PCB에 라벨링된 Z servo

#define Y_SERVO_MIDDLE 78           // Y Servo horn vertical position (motor mount is vertical) Y servo 모터의 수직 위치 (모터 마운트는 수직)
#define Z_SERVO_MIDDLE 87           // Z Servo horn vertical position (motor mount is vertical) Z servo 모터의 수직 위치 (모터 마운트는 수직)

// Servo ratio is calculated by making multiple images of different servo horn angles and comparing the orientation of the horn and the motor mount
//servo 비율은 서로 다른 servo 혼 각도의 여러 이미지를 만들고 혼과 모터 마운트의 방향을 비교하여 계산됩니다.
#define SERVO_RATIO 3.1             // Servo horn to motor mount ratio (if horn is turned 1 deg, motor mount will turn 3 deg) horn 을 1도 회전시 mount는 3도 회전합니다. 
#define MAX_SERVO_ROTATION 30       // Motor mount can only be rotated 10 deg => the servos are allowed to rotate 30 deg  // 모터 마운트 10도 까지만 회전 할 수 있습니다.-> 서보는 30도 까지만 회전 할 수 있습니다.

#define PARACHUTE_SERVO_PIN 5       // Parachute Servo = Servo 3 (labeled on pcb)
#define PARACHUTE_CLOSED 0          // Position of the parachute servo before ejection (in deg) 사용전 낙하산 servo 위치
#define PARACHUTE_EJECT 175         // Position of the parachute servo after ejection (in deg) 사용후 낙하산 servo 위치

#define DEG2RAD 0.01745329251f      // Convert degrees to radians by multiplying with this number 각도를 이값에 곱하여 차수를 라디안으로 변환합니다.
#define RAD2DEG 57.2957795131f      // Convert radians to degrees by multiplying with this number 라디안을 이값에 곱하여 차수로 변환합니다.

#define MIN_VOLTAGE 4               // Minimum board voltage to complete startup (in V) 최저 전력

#define SEA_LEVEL_PRESSURE 1013.25  // Standard atmospheric pressure at sea level (in hPa) 해수면에 따른 표준대기압 사용

class Rocket {
  public:
    Rocket();

    SDCard sdCard;

    // Angular Velocity Vector 각속도 벡터
    // Three axis of rotation speed in radians per second (rad/s) 세 축의 회전 속도(초당 라디안(rad/s) 단위)
    Vector3 gyros;

    // Acceleration Vector 가속도 벡터
    // Three axis of acceleration (gravity + linear motion) in m/s^2 // 가속도 3축(중력 + 직선 운동)(m/s^2 단위)
    Vector3 acceleration;

    // Absolute Orientation Vector 절대 방향 벡터
    // Three axis orientation data based on a 360° sphere (Euler Vector in deg) // 360° 구를 기준으로 한 3축 방향 데이터(도 단위는 오일러 벡터를 사용합니다.)
    Vector3 orientation;

    // Relative Orientation Vector 상대 방향 벡터
    // Three axis orientation data (roll, pitch and yaw) in rad // 세 축 방향 데이터(롤, 피치, 요), 반경 단위
    Vector3 relativeOrientation;

    float flightTime = 0.0f; // in s -- 초단위로 표현됩니다.
    float flightStartTime = 0.0f; // in ms -- 초단위로 표현 됩니다.
    
    void padIdle();
    void ascent();
    void maxApogee();
    void descent();
    void landed();

  private:
    IMU imu;
    BMP bmp;
    VoltageDivider voltageDivider;
    
    // PID Values were tuned with a Simulink simulation and verified with AeroVECTOR https://github.com/GuidodiPasquo/AeroVECTOR
    // 시뮬레이션 링크 시뮬레이션을 통해 PID 값을 조정하고 에어로벡터로 검증했습니다
    // PID-Controller for calculation of motor mount orientation on y-axis
    // Y축 모터 마운트 방향 계산을 위한 PID 컨트롤러
    PID yPID = PID(0.6f, 0.05f, 0.125f, 10.0f);
    // PID-Controller for calculation of motor mount orientation on z-axis
    // Z축 모터 마운트 방향 계산을 위한 PID 컨트롤러
    PID zPID = PID(0.6f, 0.05f, 0.125f, 10.0f);

    Servo yServo;
    Servo zServo;
    Servo parachuteServo;
    
    unsigned long currentTime = 0.0;
    unsigned long previousTime = 0.0;
    float deltaTime = 0.0f;
};
