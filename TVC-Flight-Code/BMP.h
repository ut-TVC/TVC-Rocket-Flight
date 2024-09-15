/*
 * Barometric Pressure & Altitude Sensor BMP280
 * https://www.adafruit.com/product/2651
 * 
 * Outputs the following data: temperature, athmospheric pressure and altitude (which is calculated with the pressure at sea level)
 * 다음 데이터를 출력합니다 : 온도, 대기압 , 고도 (해수면을 기준으로 계산합니다. )
 */

#include <Adafruit_BMP280.h>
#include <Wire.h>

class BMP {
  public:
    BMP();
    
    float readTemperature();
    float readPressure();
    float readAltitude(float seaLevelhPa);

  private:
    Adafruit_BMP280 bmp;
};
