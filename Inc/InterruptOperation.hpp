/*
 * InterruptOperation.hpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */

#ifndef INTERRUPTOPERATION_HPP_
#define INTERRUPTOPERATION_HPP_

#include "ButtonInterrupt.hpp"
#include "TimerInterrupt.hpp"
#include "MemoryMap.hpp"

class InterruptOperation {
public:
	InterruptOperation();
	void init();
private:
	ButtonInterrupt* button_interrupt;
	static TimerInterrupt* timer_interrupt;

	static int var;
	static volatile int debouncer_flag;
};


#endif /* INTERRUPTOPERATION_HPP_ */
