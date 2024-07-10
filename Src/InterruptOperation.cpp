/*
 * InterruptOperation.cpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */
#include "InterruptOperation.hpp"

int InterruptOperation::var = 0;
volatile int InterruptOperation::debouncer_flag = 0;
TimerInterrupt* InterruptOperation::timer_interrupt = nullptr;

InterruptOperation::InterruptOperation() {
	button_interrupt = new ButtonInterrupt(GPIOA_BASE, 0, 0, 6);
	timer_interrupt = new TimerInterrupt(TIM2_BASE, 28);
}

void InterruptOperation::init() {
	button_interrupt->init();
	timer_interrupt->init(16000, 1000);

	button_interrupt->setInterruptHandler([](){
        if (!debouncer_flag) {
            var++;
        }
        debouncer_flag = 1; // Sinalizar período de debounce
        timer_interrupt->start();
    });

	timer_interrupt->setInterruptHandler([](){
        debouncer_flag = 0; // Sinalizar fim do período de debounce
    });
}


