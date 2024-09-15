/*
 * Voltage divider (전압 분배기)
 * 
 * Calculates the on-board voltage by using a voltage divider connected to an analoge input pin of the Teensy 4.1
 * 틴시 4.1의 아날로그 입력 핀에 연결된 전압 분배기를 사용하여 온보드 전압을 계산합니다
 */

#include <Arduino.h>

#define VOLTAGEDIVIDER_PIN 38

class VoltageDivider {
  public:
    VoltageDivider();
    float getBoardVoltage();
};
