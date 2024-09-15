#include "BMP.h"

BMP::BMP() {
  if (!bmp.begin()) {
    Serial.println("ERROR: BMP280 initialisation failed!");
  }

  // Default settings from datasheet https://cdn-shop.adafruit.com/datasheets/BST-BMP280-DS001-11.pdf
  // 오버샘플링(oversampling)은 두 배 이상의 대역폭, 또는 샘플링할 수 있는 최고의 샘플링 주파수로 신호를 샘플링하는 과정이다. 오버샘플링은 에일리어싱 방지, 해상도 향상, 노이즈 감소에 효과적이다.
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. 작동모드 */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling 온도 오버샘플링 */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling 압력 오버샘플링 */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. 필터링 */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. 대기 시간 */
}

float BMP::readTemperature() {
  return bmp.readTemperature();
}

float BMP::readPressure() {
  return bmp.readPressure();
}

float BMP::readAltitude(float seaLevelhPa) {
  return bmp.readAltitude(seaLevelhPa);
}
