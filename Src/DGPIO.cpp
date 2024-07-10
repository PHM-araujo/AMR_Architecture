#include "DGPIO.hpp"
#include "MemoryMap.hpp"

DGPIO::DGPIO(char port, int pin, int mode) : pin(pin)
{
    switch (port)
    {
    case 'A':
        base = GPIOA;
        enableClock(port);
        break;
    case 'B':
        base = GPIOB;
        enableClock(port);
        break;
    case 'C':
        base = GPIOC;
        enableClock(port);
        break;
    case 'D':
        base = GPIOD;
        enableClock(port);
        break;
    case 'E':
        base = GPIOE;
        enableClock(port);
        break;
    case 'F':
        base = GPIOF;
        enableClock(port);
        break;
    case 'G':
        base = GPIOG;
        enableClock(port);
        break;
    case 'H':
        base = GPIOH;
        enableClock(port);
        break;
    case 'I':
        base = GPIOI;
        enableClock(port);
        break;
    default:
        base = nullptr;
        break;
    }

    if (base != nullptr)
    {
        pinMode(mode);
    }
}

void DGPIO::enableClock(char port)
{
    switch (port)
    {
    case 'A':
        RCC->AHB1ENR |= (1 << 0);
        break;
    case 'B':
        RCC->AHB1ENR |= (1 << 1);
        break;
    case 'C':
        RCC->AHB1ENR |= (1 << 2);
        break;
    case 'D':
        RCC->AHB1ENR |= (1 << 3);
        break;
    case 'E':
        RCC->AHB1ENR |= (1 << 4);
        break;
    case 'F':
        RCC->AHB1ENR |= (1 << 5);
        break;
    case 'G':
        RCC->AHB1ENR |= (1 << 6);
        break;
    case 'H':
        RCC->AHB1ENR |= (1 << 7);
        break;
    case 'I':
        RCC->AHB1ENR |= (1 << 8);
        break;
    default:
        break;
    }
}

void DGPIO::pinMode(int mode)
{
    if (base != nullptr)
    {
        base->MODER &= ~(0x3 << (pin * 2)); // Limpar os bits
        base->MODER |= (mode << (pin * 2)); // Configurar o modo
    }
}

void DGPIO::digitalWrite(int value)
{
    if (base != nullptr)
    {
        if (value)
        {
            base->BSRR = (1 << pin); // Set bit
        }
        else
        {
            base->BSRR = (1 << (pin + 16)); // Reset bit
        }
    }
}

int DGPIO::digitalRead()
{
    if (base != nullptr)
    {
        return (base->IDR & (1 << pin)) ? 1 : 0;
    }
    return 0;
}

void delay(volatile unsigned int count)
{
    while (count--)
        ;
}
