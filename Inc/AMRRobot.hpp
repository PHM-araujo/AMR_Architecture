/*
 * AMR.hpp
 *
 *  Created on: Jul 2, 2024
 *      Author: Pedro
 */

#ifndef AMRROBOT_HPP_
#define AMRROBOT_HPP_

#include "InterruptOperation.hpp"
#include "DGPIO.hpp"
#include "AnalogOperation.h"

class AMRRobot {
public:
	AMRRobot();
	void Init();
	void Run();

private:
	 InterruptOperation interrupt;
	 DGPIO* dgpio_teste;
};



#endif /* AMRROBOT_HPP_ */
