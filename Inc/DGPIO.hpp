#ifndef DGPIO_H
#define DGPIO_H

#include <cstdint>
#include "MemoryMap.hpp"

// Definição dos modos
constexpr int INPUT = 0x0;
constexpr int OUTPUT = 0x1;

class DGPIO
{
public:
    DGPIO(char port, int pin, int mode);
    void pinMode(int mode);
    void digitalWrite(int value);
    int digitalRead();

private:
    GPIO_TypeDef *base;
    int pin;
    void enableClock(char port);
};

void delay(volatile unsigned int count);

#endif // DGPIO_H
