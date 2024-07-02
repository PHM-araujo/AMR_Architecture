#include "DGPIO.hpp"

DGPIO::DGPIO(char port, int pin, int mode) : pin(pin) {
    switch (port) {
        case 'A':
            base = reinterpret_cast<volatile uint32_t*>(GPIOA_BASE);
            *RCC_AHB1ENR |= (1 << 0);  // Habilitar clock para GPIOA
            break;
        case 'B':
            base = reinterpret_cast<volatile uint32_t*>(GPIOB_BASE);
            *RCC_AHB1ENR |= (1 << 1);  // Habilitar clock para GPIOB
            break;
        case 'C':
            base = reinterpret_cast<volatile uint32_t*>(GPIOC_BASE);
            *RCC_AHB1ENR |= (1 << 2);  // Habilitar clock para GPIOC
            break;
        case 'D':
            base = reinterpret_cast<volatile uint32_t*>(GPIOD_BASE);
            *RCC_AHB1ENR |= (1 << 3);  // Habilitar clock para GPIOD
            break;
        case 'E':
            base = reinterpret_cast<volatile uint32_t*>(GPIOE_BASE);
            *RCC_AHB1ENR |= (1 << 4);  // Habilitar clock para GPIOE
            break;
        case 'F':
            base = reinterpret_cast<volatile uint32_t*>(GPIOF_BASE);
            *RCC_AHB1ENR |= (1 << 5);  // Habilitar clock para GPIOF
            break;
        case 'G':
            base = reinterpret_cast<volatile uint32_t*>(GPIOG_BASE);
            *RCC_AHB1ENR |= (1 << 6);  // Habilitar clock para GPIOG
            break;
        case 'H':
            base = reinterpret_cast<volatile uint32_t*>(GPIOH_BASE);
            *RCC_AHB1ENR |= (1 << 7);  // Habilitar clock para GPIOH
            break;
        case 'I':
            base = reinterpret_cast<volatile uint32_t*>(GPIOI_BASE);
            *RCC_AHB1ENR |= (1 << 8);  // Habilitar clock para GPIOI
            break;
        default:
            // Tratar erro de GPIO desconhecido
            base = nullptr;
            break;
    }

    if (base != nullptr) {
        // Configurar o pino
        pinMode(mode);
    }
}

void DGPIO::pinMode(int mode) {
    if (base != nullptr) {
        base[0] &= ~(0x3 << (pin * 2));  // Limpar os bits
        base[0] |= (mode << (pin * 2));  // Configurar o modo
    }
}

void DGPIO::digitalWrite(int value) {
    if (base != nullptr) {
        if (value) {
            base[6] = (1 << pin);  // Set bit
        } else {
            base[6] = (1 << (pin + 16));  // Reset bit
        }
    }
}

int DGPIO::digitalRead() {
    if (base != nullptr) {
        return (base[4] & (1 << pin)) ? 1 : 0;
    }
    return 0;
}

void delay(volatile unsigned int count) {
    while (count--);
}
