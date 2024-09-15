#include "Rocket.h"

Rocket::Rocket() {
  // Attach and initialize servos     서보 연결 및 초기화
  yServo.attach(Y_SERVO_PIN);
  zServo.attach(Z_SERVO_PIN);
  parachuteServo.attach(PARACHUTE_SERVO_PIN);

  yServo.write(Y_SERVO_MIDDLE);
  zServo.write(Z_SERVO_MIDDLE);
  parachuteServo.write(PARACHUTE_CLOSED);

  // Check on-board voltage     온보드 전압 체크
  if(voltageDivider.getBoardVoltage() < MIN_VOLTAGE) {
    Serial.println("Error: on-board voltage too low");
    while (true) {
      // on-board voltage too low, so do not do anything more - stay stuck here and play alarm
      // 온보드의 전압이 너무 낮을 시, 더이상 아무것도 하지 않음 - 그냥 가만히 알람을 울림.
      sdCard.buzzer.tooLowOnBoardVoltageAlert();
      
      sdCard.led.red();
      delay(500);
      sdCard.led.off();
    }
  }
}

void Rocket::padIdle() {
  // Update acceleration for lift off check     이륙 체크를 위한 가속 업데이트
  acceleration = imu.getAcceleration();
}

void Rocket::ascent() {
  // Calculate flight time in s     비행 시간을 초단위(s)로 계산
  flightTime = (millis() - flightStartTime) / 1000.0f;

  // ----- TVC ALGORITHM -----      ----- TVC 알고리즘 -----
  // Calculate delta time     시간차 계산
  currentTime = micros();
  deltaTime = (currentTime - previousTime) / 1000000.0f;

  // Update gyro values     자이로 값 업데이트
  gyros = imu.getGyros();

  // Integrate angular velocity for relative orientation (roll, pitch and yaw) in rad
  // 라디안의 상대 방향(롤, 피치 및 요)에 대한 각속도 적분
  relativeOrientation += gyros * deltaTime;

  // Send the yaw and pitch to their respective PID Controller and recieve output
  // yaw와 pitch를 각 PID 컨트롤러로 보내고 출력을 받습니다
  float yPIDoutput = yPID.update(relativeOrientation.y);
  float zPIDoutput = zPID.update(relativeOrientation.z);

  // Convert the relative orientation in rad to deg
  // rad의 상대 방향을 deg로 변환합니다
  yPIDoutput = yPIDoutput * RAD2DEG;
  zPIDoutput = zPIDoutput * RAD2DEG;

  // Convert the PID output (orientation of motor mount) to servo position (relative orientation of servo horn)
  // PID 출력(모터 마운트 방향)을 서보 위치(서보 혼의 상대 방향)로 변환합니다
  float yServoRelPosition = yPIDoutput * SERVO_RATIO;
  float zServoRelPosition = zPIDoutput * SERVO_RATIO;

  // Check if the servo relative positions are greater than the max motor mount rotation
  // 서보 상대 위치가 최대 모터 마운트 회전보다 큰지 확인합니다
  // The motor mount can only be rotated 10 deg => the servos are allowed to rotate 30 deg
  // 모터 마운트는 10도만 회전할 수 있습니다 => 서보는 30도만 회전할 수 있습니다
  if(yServoRelPosition > MAX_SERVO_ROTATION) {
    yServoRelPosition = MAX_SERVO_ROTATION;
  }
  else if(yServoRelPosition < -MAX_SERVO_ROTATION) {
    yServoRelPosition = -MAX_SERVO_ROTATION;
  }

  if(zServoRelPosition > MAX_SERVO_ROTATION) {
    zServoRelPosition = MAX_SERVO_ROTATION;
  }
  else if(zServoRelPosition < -MAX_SERVO_ROTATION) {
    zServoRelPosition = -MAX_SERVO_ROTATION;
  }

  // Set the position of the servos
  // 서보의 포지션을 설정
  // To get the absolute position of the servo horns, the middle servo horn position is added to the relative orientation
  // 서보 혼의 절대 위치를 얻으려면 중간 서보 혼 위치를 상대 방향에 추가합니다
  yServo.write(yServoRelPosition + Y_SERVO_MIDDLE);
  zServo.write(zServoRelPosition + Z_SERVO_MIDDLE);

  // Save current time for next cycle     다음 사이클을 위해 현재 시간 저장     
  previousTime = currentTime;

  // ----- DATA LOGGING -----     ----- 데이터 로그 생성 -----
  acceleration = imu.getAcceleration();
  orientation = imu.getOrientation();

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(SEA_LEVEL_PRESSURE);

  float voltage = voltageDivider.getBoardVoltage();
  
  sdCard.logData(flightTime, gyros.x, gyros.y, gyros.z, acceleration.x, acceleration.y, acceleration.z, orientation.x, orientation.y, orientation.z, temperature, pressure, altitude, yServoRelPosition + Y_SERVO_MIDDLE, zServoRelPosition + Z_SERVO_MIDDLE, voltage, "ASCENT");
}

void Rocket::maxApogee() {
  // Eject Parachute      낙하산 사출
  parachuteServo.write(PARACHUTE_EJECT);

  // Set tvc servos to middle position      TVC서보를 중간 포지션으로 설정
  yServo.write(Y_SERVO_MIDDLE);
  zServo.write(Z_SERVO_MIDDLE);
}

void Rocket::descent() {
  // Calculate flight time in s     비행 시간을 초단위(s)로 계산
  flightTime = (millis() - flightStartTime) / 1000.0f;

  // ----- DATA LOGGING -----     ----- 데이터 로그 생성 -----
  acceleration = imu.getAcceleration();
  orientation = imu.getOrientation();

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(SEA_LEVEL_PRESSURE);

  float voltage = voltageDivider.getBoardVoltage();
  
  sdCard.logData(flightTime, gyros.x, gyros.y, gyros.z, acceleration.x, acceleration.y, acceleration.z, orientation.x, orientation.y, orientation.z, temperature, pressure, altitude, Y_SERVO_MIDDLE, Z_SERVO_MIDDLE, voltage, "DESCENT");

}
