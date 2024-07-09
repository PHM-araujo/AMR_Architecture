/*
 * TimerInterrupt.hpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */

#ifndef TIMERINTERRUPT_HPP_
#define TIMERINTERRUPT_HPP_

#include <functional>
#include <cstdint>

class TimerInterrupt {
public:
	TimerInterrupt(uint32_t timer_base, uint32_t irq_number);
	void init(uint32_t prescaler, uint32_t auto_reload);
	void setInterruptHandler(std::function<void()>handler);
	void start();

	static void TIM2_IRQHandler();
private:
	uint32_t timer_base;
	uint32_t irq_number;
	static std::function<void()> handler;
	static TimerInterrupt* instance;  // Adicione esta linha
};

extern "C" void TIM2_IRQHandler();

#endif /* TIMERINTERRUPT_HPP_ */
