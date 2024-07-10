/*
 * ButtonInterrupt.cpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */
#include "ButtonInterrupt.hpp"
#include "HAL.hpp"
#include "InterruptManager.hpp"

std::function<void()> ButtonInterrupt::handler = nullptr;

ButtonInterrupt::ButtonInterrupt(uint32_t gpio_base, uint32_t pin, uint32_t exti_line, uint32_t irq_number)
: gpio_base(gpio_base), pin(pin), exti_line(exti_line), irq_number(irq_number) {}

void ButtonInterrupt::init(){
	HAL::enableClock(HAL::RCC_AHB1ENR_GPIOAEN);
	HAL::enableClock(HAL::RCC_APB2ENR_SYSCFGEN);
	HAL::configureGPIO(gpio_base, pin, true);
	HAL::configureEXTI(exti_line, gpio_base, pin);
	HAL::configureEXTIRisingEdge(exti_line);
	HAL::enableInterrupt(irq_number);
	InterruptManager::installInterruptHandler(irq_number, EXTI0_IRQHandler);
}

void ButtonInterrupt::setInterruptHandler(std::function<void()> handler) {
    this->handler = handler;
}

void ButtonInterrupt::EXTI0_IRQHandler(){
	HAL::clearEXTIPendingFlag(0);
	if(handler) {
		handler();
	}
}

extern "C" void EXTI0_IRQHandler() {
	ButtonInterrupt::EXTI0_IRQHandler();
}
;
