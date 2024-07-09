/*
 * InterruptManager.hpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */

#ifndef INTERRUPTMANAGER_HPP_
#define INTERRUPTMANAGER_HPP_

#include <functional>
#include <array>
#include <cstdint>

class InterruptManager {
public:
	static void installInterruptHandler(uint32_t irq_number, std::function<void()> handler);
	static void uninstallInterruptHandler(uint32_t irq_number);
private:
	static std::array<std::function<void()>, 240> interruptVectorTable;
};



#endif /* INTERRUPTMANAGER_HPP_ */
