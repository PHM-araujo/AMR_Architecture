/*
 * TimerInterrupt.cpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */
#include "TimerInterrupt.hpp"
#include "HAL.hpp"
#include "MemoryMap.hpp"
#include "InterruptManager.hpp"

TimerInterrupt* TimerInterrupt::instance = nullptr;
std::function<void()> TimerInterrupt::handler = nullptr;

TimerInterrupt::TimerInterrupt(uint32_t timer_base, uint32_t irq_number)
: timer_base(timer_base), irq_number(irq_number) {
	instance = this;
}

void TimerInterrupt::init(uint32_t prescaler, uint32_t auto_reload) {
	HAL::enableClock(HAL::RCC_APB1ENR_TIM2EN);
	TIM_TypeDef* TIMx = (TIM_TypeDef*)timer_base;
	TIMx->PSC = prescaler - 1;  // Prescaler
	TIMx->ARR = auto_reload - 1;   // Auto-reload
	TIMx->DIER |= 0x1;      // Habilitar interrupção de atualização
	TIMx->CR1 |= 0x1;       // Habilitar TIM2

	HAL::enableInterrupt(irq_number);
	InterruptManager::installInterruptHandler(irq_number, TIM2_IRQHandler);
}

void TimerInterrupt::setInterruptHandler(std::function<void()> handler) {
    this->handler = handler;
}

void TimerInterrupt::start() {
    HAL::resetTimerCounter(instance->timer_base);
    HAL::startTimer(instance->timer_base);
}


void TimerInterrupt::TIM2_IRQHandler() {
    HAL::clearTimerPendingFlag(instance->timer_base);
    if (handler) {
        handler();
    }
}

extern "C" void TIM2_IRQHandler() {
	TimerInterrupt::TIM2_IRQHandler();
}










