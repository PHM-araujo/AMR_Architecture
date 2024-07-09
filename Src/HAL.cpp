/*
 * HAL.cpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */
#include "HAL.hpp"
#include "MemoryMap.hpp"

void HAL::enableClock(uint32_t peripheral){
	if (peripheral == RCC_AHB1ENR_GPIOAEN) {
		RCC->AHB1ENR |= peripheral;
	} else if (peripheral == RCC_APB2ENR_SYSCFGEN) {
		RCC->APB2ENR |= peripheral;
	} else if (peripheral == RCC_APB1ENR_TIM2EN) {
		RCC->APB1ENR |= peripheral;
	}
}

void HAL::configureGPIO(uint32_t gpio_base, uint32_t pin, bool is_input){
	GPIO_TipeDef GPIOx = (GPIO_TypeDef*)gpio_base;
	if (is_input) {
		GPIOx->MODER &= ~(0x3 << (pin * 2));
	} else {
		GPIOx->MODER |= (0x1 << (pin * 2));
	}
}

void HAL::configureEXTI(uint32_t exti_line, uint32_t gpio_base, uint32_t pin){
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
































