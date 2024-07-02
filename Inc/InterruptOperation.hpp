/*
 * InterruptOperation.hpp
 *
 *  Created on: Jul 1, 2024
 *      Author: Pedro
 */

#ifndef INTERRUPTOPERATION_HPP_
#define INTERRUPTOPERATION_HPP_

class InterruptOperation {
public:
	void init();
	static void EXTI0_IRQHandler();
	static void TIM2_IRQHandler();

private:
	 static volatile int debouncer_flag;
	 static int var;

	 void init_button_interrupt();
	 void init_timer2();
};



#endif /* INTERRUPTOPERATION_HPP_ */
