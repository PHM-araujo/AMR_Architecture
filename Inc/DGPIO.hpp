/*
 * DGPIO.hpp
 *
 *  Created on: Jul 1, 2024
 *      Author: manoe
 */

#ifndef DGPIO_HPP_
#define DGPIO_HPP_
#include <cstdint>
#include "MemoryMap.hpp"

// Definição dos modos
constexpr int INPUT = 0x0;
constexpr int OUTPUT = 0x1;

class DGPIO {
public:
    DGPIO(char port, int pin, int mode);
    void pinMode();
    void digitalWrite(int value);
    int digitalRead();

private:
    char port_;
    int pin_;
    int mode_;
};

void delay(unsigned int count);

#endif /* DGPIO_HPP_ */
