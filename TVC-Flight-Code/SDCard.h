/*
 * SD-Card
 * SD 카드 관련 코드 입니다.
 * 
 * During the ascent and descent states important flight data is saved on the SD-Card
 * 상승 ~ 항강 상태에서 중요한 비행 데이터들을 SD 카드에 기록합니다.
 */

#include <SD.h>
#include <SPI.h>
#include "LED.h"
#include "Buzzer.h"

class SDCard {
  public:
    SDCard();

    LED led;
    Buzzer buzzer;
    
    void logData(float flightTime, float gyroX, float gyroY, float gyroZ, float accelerationX, float accelerationY, float accelerationZ, float orientationX, float orientationY, float orientationZ, float temperature, float pressure, float altitude, float yServo, float zServo, float voltage, String state);
    
  private:
    // Use the built in SD-Card slot of the Teensy 4.1
    const int chipSelect = BUILTIN_SDCARD;
};
