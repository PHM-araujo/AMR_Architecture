/*
 * AMR.hpp
 *
 *  Created on: Jul 2, 2024
 *      Author: Pedro
 */

#ifndef AMRROBOT_HPP_
#define AMRROBOT_HPP_

//#include "DGPIO.hpp"
#include "AnalogOperation.h"
#include "InterruptOperation.hpp"

class AMRRobot {
public:
	AMRRobot();
	void Init();
	void Run();

private:
	 // DGPIO* dgpio_teste;
	InterruptOperation interrupt_operation;
};



#endif /* AMRROBOT_HPP_ */
