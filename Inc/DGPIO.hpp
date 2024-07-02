/*
 * DGPIO.hpp
 *
 *  Created on: Jul 1, 2024
 *      Author: manoe
 */

#ifndef DGPIO_HPP_
#define DGPIO_HPP_

#include <cstdint>

// Definições dos endereços dos registradores
const std::uintptr_t RCC_BASE = 0x40023800;
const std::uintptr_t GPIOA_BASE = 0x40020000;
const std::uintptr_t GPIOB_BASE = 0x40020400;
const std::uintptr_t GPIOC_BASE = 0x40020800;
const std::uintptr_t GPIOD_BASE = 0x40020C00;
const std::uintptr_t GPIOE_BASE = 0x40021000;
const std::uintptr_t GPIOF_BASE = 0x40021400;
const std::uintptr_t GPIOG_BASE = 0x40021800;
const std::uintptr_t GPIOH_BASE = 0x40021C00;
const std::uintptr_t GPIOI_BASE = 0x40022000;

volatile uint32_t* const RCC_AHB1ENR = reinterpret_cast<volatile uint32_t*>(RCC_BASE + 0x30);

// Definição dos modos
constexpr int INPUT = 0x0;
constexpr int OUTPUT = 0x1;

class DGPIO {
public:
    DGPIO(char port, int pin, int mode);
    void pinMode(int mode);
    void digitalWrite(int value);
    int digitalRead();

private:
    volatile uint32_t* base;
    int pin;
};

void delay(volatile unsigned int count);

#endif /* DGPIO_HPP_ */
