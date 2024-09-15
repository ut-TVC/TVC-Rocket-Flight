#include "SDCard.h"

SDCard::SDCard() {
  if(!SD.begin(chipSelect)) {
    Serial.println("Error: The SD card failed to initialize, or is not present!");
    while (true) {
      // No SD card, so do not do anything more - stay stuck here and play alarm
      // SD 카드가 없다면, 더이상 아무것도 하지 않음 - 그냥 가만히 알람을 울림
      buzzer.noSDCardAlert();
      
      led.red();
      delay(1000);
      led.off();
    }
  }

  // Create file (or open it if it already exists)      파일 생성(또는 이미 존재 한다면 열기)
  File dataFile = SD.open("datalog.CSV", FILE_WRITE);

  // Write top description line     상단 설명 줄 작성
  dataFile.println("flightTime, gyros.x, gyros.y, gyros.z, acceleration.x, acceleration.y, acceleration.z, orientation.x, orientation.y, orientation.z, temperature, pressure, altitude, yServo orientation, zServo orientation, voltage, state");
  dataFile.close();
}

void SDCard::logData(float flightTime, float gyroX, float gyroY, float gyroZ, float accelerationX, float accelerationY, float accelerationZ, float orientationX, float orientationY, float orientationZ, float temperature, float pressure, float altitude, float yServo, float zServo, float voltage, String state) {
  // Open the data logging file     데이터 로그 파일 열기
  File dataFile = SD.open("datalog.CSV", FILE_WRITE);

  // If the file is available, write to it      파일을 열 수 있는 경우, 거기에 작성
  if (dataFile) {
    dataFile.print(flightTime);
    dataFile.print(",");
    dataFile.print(gyroX);
    dataFile.print(",");
    dataFile.print(gyroY);
    dataFile.print(",");
    dataFile.print(gyroZ);
    dataFile.print(",");
    dataFile.print(accelerationX);
    dataFile.print(",");
    dataFile.print(accelerationY);
    dataFile.print(",");
    dataFile.print(accelerationZ);
    dataFile.print(",");
    dataFile.print(orientationX);
    dataFile.print(",");
    dataFile.print(orientationY);
    dataFile.print(",");
    dataFile.print(orientationZ);
    dataFile.print(",");
    dataFile.print(temperature);
    dataFile.print(",");
    dataFile.print(pressure);
    dataFile.print(",");
    dataFile.print(altitude);
    dataFile.print(",");
    dataFile.print(yServo);
    dataFile.print(",");
    dataFile.print(zServo);
    dataFile.print(",");
    dataFile.print(voltage);
    dataFile.print(",");
    dataFile.println(state);
    
    dataFile.close();
  } else {
    // If the file can not be opened, pop up an error message     파일을 열 수 없는 경우 에러 메세지 팝업
    Serial.println("Error: Can not open datalog.txt");
  }
}
