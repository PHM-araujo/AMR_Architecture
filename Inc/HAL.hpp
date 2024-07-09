/*
 * HAL.hpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */

#ifndef HAL_HPP_
#define HAL_HPP_

#include <cstdint>

class HAL {
public:
	// Habilitar clock para um periférico específico
	static void enableClock(uint32_t peripheral);

	// Configurar GPIO como entrada ou saída
	static void configureGPIO(uint32_t gpio_base, uint32_t pin, bool is_input);

	// Configurar EXTI para um pino específico
	static void configureEXTI(uint32_t exti_line, uint32_t gpio_base, uint32_t pin);

	// Habilitar interrupção no NVIC
	static void enableInterrupt(uint32_t irq_number);

	// Limpar flag de interrupção do EXTI
	static void clearEXTIPendingFlag(uint32_t exti_line);

	// Iniciar timer
	static void startTimer(uint32_t timer_base);

	// Limpar flag de interrupção do timer
	static void clearTimerPendingFlag(uint32_t timer_base);

	// Configurar EXTI para a borda de subida
	static void configureEXTIRisingEdge(uint32_t exti_line);

	// Resetar contador de timer
	static void resetTimerCounter(uint32_t timer_base);

private:
	static constexpr uint32_t RCC_AHB1ENR_GPIOAEN = (1 << 0);
	static constexpr uint32_t RCC_APB2ENR_SYSCFGEN = (1 << 14);
	static constexpr uint32_t RCC_APB1ENR_TIM2EN = (1 << 0);
};

#endif /* HAL_HPP_ */
