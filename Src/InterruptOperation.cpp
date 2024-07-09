/*
 * InterruptOperation.cpp
 *
 *  Created on: Jul 1, 2024
 *      Author: Pedro
 */
// Definições de registradores e macros
#include "InterruptOperation.hpp"
#include <stdint.h>
#include "MemoryMap.hpp"

int InterruptOperation::var = 0;
volatile int InterruptOperation::debouncer_flag = 0;

void InterruptOperation::init(){
	init_button_interrupt();
	init_timer2();
}

void InterruptOperation::EXTI0_IRQHandler() {
	if (EXTI->PR & 0x1) {
		EXTI->PR |= 0x1; // Limpar flag de interrupção

		TIM2->CNT = 0;   // Reinicia contador
		TIM2->CR1 |= 0x1; // Inicia timer

		if (!debouncer_flag) {
			var++;
		}
		debouncer_flag = 1; // Sinalizar período de debounce
	}
}

void InterruptOperation::TIM2_IRQHandler() {
	if (TIM2->SR & 0x1) {
		TIM2->SR &= ~0x1; // Limpar flag de interrupção
		debouncer_flag = 0; // Sinalizar fim do período de debounce
	}
}

void InterruptOperation::init_button_interrupt() {
	// Habilitar clock GPIOA e SYSCFG
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB2ENR |= (1 << 14);

	// Configurar PA0 como entrada (IDR)
	GPIOA->MODER &= ~(0x3);

	// Configurar EXTI0 para o PA0
	SYSCFG->EXTICR[0] &= ~0xF;
	SYSCFG->EXTICR[0] |= (0x0);

	// Configurar EXTI0 para a borda de subida
	EXTI->IMR |= 0x1;
	EXTI->RTSR |= 0x1;

	// Habilitar a interrupção EXTI0 no NVIC
	NVIC->ISER[0] |= (1 << 6);
}

void InterruptOperation::init_timer2() {
	// Habilita o clock para o timer 2
	RCC->APB1ENR |= (1 << 0);

	// Configurar o timer 2
	TIM2->PSC = 16000 - 1;	// Prescaler
	TIM2->ARR = 1000 - 1;  	// Auto-reload
	TIM2->DIER |= 0x1;     	// Habilitar interrupção de atualização
	TIM2->CR1 |= 0x1;      // Habilitar TIM2

	// Habilitar interrupção TIM2 no NVIC
	NVIC->ISER[0] |= (1 << 28);
}

extern "C" void EXTI0_IRQHandler() {
	InterruptOperation::EXTI0_IRQHandler();
}

extern "C" void TIM2_IRQHandler() {
	InterruptOperation::TIM2_IRQHandler();
}




