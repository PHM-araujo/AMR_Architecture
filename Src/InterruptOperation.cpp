/*
 * InterruptOperation.cpp
 *
 *  Created on: Jul 1, 2024
 *      Author: Pedro
 */
// Definições de registradores e macros
#include "InterruptOperation.hpp"

#include <stdint.h>

#define RCC_AHB1ENR     (*((volatile uint32_t *)0x40023830))
#define RCC_APB2ENR     (*((volatile uint32_t *)0x40023844))
#define RCC_APB1ENR     (*((volatile uint32_t *)0x40023840))
#define GPIOA_MODER     (*((volatile uint32_t *)0x40020000))
#define GPIOA_IDR       (*((volatile uint32_t *)0x40020010))
#define SYSCFG_EXTICR1  (*((volatile uint32_t *)0x40013808))
#define EXTI_IMR        (*((volatile uint32_t *)0x40013C00))
#define EXTI_RTSR       (*((volatile uint32_t *)0x40013C08))
#define EXTI_PR         (*((volatile uint32_t *)0x40013C14))
#define NVIC_ISER0      (*((volatile uint32_t *)0xE000E100))
#define TIM2_CR1        (*((volatile uint32_t *)0x40000000))
#define TIM2_DIER       (*((volatile uint32_t *)0x4000000C))
#define TIM2_SR         (*((volatile uint32_t *)0x40000010))
#define TIM2_CNT        (*((volatile uint32_t *)0x40000024))
#define TIM2_PSC        (*((volatile uint32_t *)0x40000028))
#define TIM2_ARR        (*((volatile uint32_t *)0x4000002C))

// Configuração do clock
#define RCC_CR             (*((volatile uint32_t *)0x40023800))
#define RCC_PLLCFGR        (*((volatile uint32_t *)0x40023804))
#define RCC_CFGR           (*((volatile uint32_t *)0x40023808))
#define FLASH_ACR          (*((volatile uint32_t *)0x40023C00))

#define GPIOAEN         (1 << 0)
#define SYSCFGEN        (1 << 14)
#define TIM2EN          (1 << 0)
#define EXTI0_PA0       (0x0)


int InterruptOperation::var = 0;
volatile int InterruptOperation::debouncer_flag = 0;

void InterruptOperation::init(){
	init_button_interrupt();
	init_timer2();
}

void InterruptOperation::EXTI0_IRQHandler() {
	if (EXTI_PR & 0x1) {
		EXTI_PR |= 0x1; // Limpar flag de interrupção

		TIM2_CNT = 0;   // Reinicia contador
		TIM2_CR1 |= 0x1; // Inicia timer

		if (!debouncer_flag) {
			var++;
		}
		debouncer_flag = 1; // Sinalizar período de debounce
	}
}

void InterruptOperation::TIM2_IRQHandler() {
	if (TIM2_SR & 0x1) {
		TIM2_SR &= ~0x1; // Limpar flag de interrupção

		TIM2_CR1 &= ~0x1; // Para o timer

		if (GPIOA_IDR & 0x1) {
			// Verificar se o botão ainda está pressionado
		}
		debouncer_flag = 0; // Sinalizar fim do período de debounce
	}
}

void InterruptOperation::init_button_interrupt() {
	RCC_AHB1ENR |= GPIOAEN;    // Habilitar clock para GPIOA
	RCC_APB2ENR |= SYSCFGEN;   // Habilitar clock para SYSCFG

	GPIOA_MODER &= ~0x3; // Configurar PA0 como entrada

	SYSCFG_EXTICR1 &= ~0xF; // Limpar bits correspondentes
	SYSCFG_EXTICR1 |= EXTI0_PA0;  // Selecionar PA0 como fonte para EXTI0

	EXTI_IMR |= 0x1;  // Não mascarar linha 0 (habilitar interrupção)
	EXTI_RTSR |= 0x1; // Selecionar borda de subida para linha 0

	NVIC_ISER0 |= (1 << 6); // Habilitar interrupção EXTI0 no NVIC
}

void InterruptOperation::init_timer2() {
    RCC_APB1ENR |= TIM2EN; // Habilitar clock para TIM2

    TIM2_PSC = (16000 - 1); // Prescaler para 1ms (assumindo clock de 16MHz)
    TIM2_ARR = (1000 - 1);  // Arranjo automático para 20 ms

    TIM2_DIER |= 0x1; // Habilitar interrupção de update

    NVIC_ISER0 |= (1 << 28); // Habilitar interrupção do TIM2 no NVIC
}

extern "C" void EXTI0_IRQHandler() {
	InterruptOperation::EXTI0_IRQHandler();
}

extern "C" void TIM2_IRQHandler() {
	InterruptOperation::TIM2_IRQHandler();
}




