/*
 * MemoryMap.cpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */

#include "MemoryMap.hpp"

// Definição dos ponteiros globais para os periféricos
GPIO_TypeDef* GPIOA = reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE);
GPIO_TypeDef* GPIOB = reinterpret_cast<GPIO_TypeDef*>(GPIOB_BASE);
RCC_TypeDef* RCC = reinterpret_cast<RCC_TypeDef*>(RCC_BASE);
EXTI_TypeDef* EXTI = reinterpret_cast<EXTI_TypeDef*>(EXTI_BASE);
SYSCFG_TypeDef* SYSCFG = reinterpret_cast<SYSCFG_TypeDef*>(SYSCFG_BASE);
TIM_TypeDef* TIM2 = reinterpret_cast<TIM_TypeDef*>(TIM2_BASE);
ADC_TypeDef* ADC = reinterpret_cast<ADC_TypeDef*>(ADC1_BASE);
volatile uint32_t* NVIC_ISER = reinterpret_cast<volatile uint32_t*>(NVIC_BASE);
