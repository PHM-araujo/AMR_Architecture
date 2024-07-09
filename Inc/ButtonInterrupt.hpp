/*
 * ButtonInterrupt.hpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */

#ifndef BUTTONINTERRUPT_HPP_
#define BUTTONINTERRUPT_HPP_

#include <functional>
#include <cstdint>

class ButtonInterrupt {
public:
	ButtonInterrupt(uint32_t gpio_base, uint32_t pin, uint32_t exti_line, uint32_t irq_number);
	void init();
	void setInterruptHandler(std::function<void()> handler);
	static void EXTI0_IRQHandler();
private:

	uint32_t gpio_base;
	uint32_t pin;
	uint32_t exti_line;
	uint32_t irq_number;
	static std::function<void()> handler;
};
extern "C" void EXTI0_IRQHandler();

#endif /* BUTTONINTERRUPT_HPP_ */
