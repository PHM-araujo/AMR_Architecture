/*
 * HAL.cpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */
#include "HAL.hpp"

#include "MemoryMap.hpp"

void HAL::enableClock(uint32_t peripheral) {
  if (peripheral == RCC_AHB1ENR_GPIOAEN) {
    RCC->AHB1ENR |= peripheral;
  } else if (peripheral == RCC_APB2ENR_SYSCFGEN) {
    RCC->APB2ENR |= peripheral;
  } else if (peripheral == RCC_APB1ENR_TIM2EN) {
    RCC->APB1ENR |= peripheral;
  }
}

void HAL::configureGPIO(uint32_t gpio_base, uint32_t pin, bool is_input) {
  GPIO_TypeDef* GPIOx = reinterpret_cast<GPIO_TypeDef*>(gpio_base);
  if (is_input) {
    GPIOx->MODER &= ~(0x3 << (pin * 2));
  } else {
    GPIOx->MODER |= (0x1 << (pin * 2));
  }
}

void HAL::configureEXTI(uint32_t exti_line, uint32_t gpio_base, uint32_t pin) {
  uint32_t port_index = (gpio_base - AHB1PERIPH_BASE) / 0x400;
  SYSCFG->EXTICR[exti_line / 4] &= ~(0xF << ((exti_line % 4) * 4));
  SYSCFG->EXTICR[exti_line / 4] |= (port_index << ((exti_line % 4) * 4));
}

void HAL::configureEXTIRisingEdge(uint32_t exti_line) {
  EXTI->IMR |= (1 << exti_line);
  EXTI->RTSR |= (1 << exti_line);
}

void HAL::enableInterrupt(uint32_t irq_number) {
  NVIC_ISER[irq_number / 32] |= (1 << (irq_number % 32));
}

void HAL::clearEXTIPendingFlag(uint32_t exti_line) {
  EXTI->PR |= (1 << exti_line);
}

void HAL::resetTimerCounter(uint32_t timer_base) {
  TIM_TypeDef* TIMx = (TIM_TypeDef*)timer_base;
  TIMx->CNT = 0;
}

void HAL::startTimer(uint32_t timer_base) {
  TIM_TypeDef* TIMx = (TIM_TypeDef*)timer_base;
  TIMx->CR1 |= 0x1;
}

void HAL::clearTimerPendingFlag(uint32_t timer_base) {
  TIM_TypeDef* TIMx = (TIM_TypeDef*)timer_base;
  TIMx->SR &= ~0x1;
}

// Inicializa periféricos do ADC
void HAL::configureADC(unsigned int& pin, unsigned int& adc,
                       unsigned int& channel) {
  // 1. Habilitar o Clock para GPIOB e ADC1
  RCC->AHB1ENR |= (1 << 1);  // Habilita o clock para GPIOB (bit 1)
  RCC->APB2ENR |= (1 << 8);  // Habilita o clock para ADC1 (bit 8)

  // 2. Configurar o pino PB0 como entrada analógica
  GPIOB->MODER |= (3 << (2 * pin));  // Configura PB0 como analógico (11b)

  // 3. Configurar o ADC1
  ADC_TypeDef* ADC1 = reinterpret_cast<ADC_TypeDef*>(
      APB2PERIPH_BASE + 0x2000);  // Endereço base do ADC1

  ADC1->CR1 = 0;  // Reseta CR1
  ADC1->CR2 = 0;  // Reseta CR2

  ADC1->CR1 |= (1 << 24);  // Resolução 10 bits (01b no bit 24)
  ADC1->SQR3 = channel;
  ADC1->CR2 |= (1 << 0);  // Liga o ADC1 (bit 0)

  // 4. Calibração do ADC (opcional)
  ADC1->CR2 |= (1 << 2);         // Inicia calibração (bit 2)
  while (ADC1->CR2 & (1 << 2));  // Espera a calibração terminar
}

// Obtenha os dados do canal adc
uint32_t HAL::obtenhaADCvalue(unsigned int& pin, unsigned int& adc,
                              unsigned int& channel) {
  ADC_TypeDef* ADC1 = reinterpret_cast<ADC_TypeDef*>(APB2PERIPH_BASE + 0x2000);

  // 1. Inicia a conversão do ADC
  ADC1->CR2 |= (1 << 30);  // Inicia a conversão de software (bit 30)

  // 2. Espera a conversão terminar
  while (!(ADC1->SR & (1 << 1)));  // Espera pelo EOC (End Of Conversion)

  // 3. Retorna o valor convertido
  return ADC1->DR;
}
