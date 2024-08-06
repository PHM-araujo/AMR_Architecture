#include "DGPIO.hpp"

#include "HAL.hpp"

DGPIO::DGPIO(char port, int pin, int mode) : port_(port), pin_(pin), mode_(0) {
  pinMode();
}

void DGPIO::pinMode() { HAL::setPinMode(port_, pin_, mode_); }

void DGPIO::digitalWrite(int value) {
  HAL::digitalWriteOnPin(port_, pin_, value);
}

int DGPIO::digitalRead() { return HAL::digitalReadOnPin(port_, pin_); }

void delay(unsigned int count) {
    while (count--);
}
