/*
 * InterruptManager.cpp
 *
 *  Created on: Jul 9, 2024
 *      Author: Pedro
 */
#include "InterruptManager.hpp"

std::array<std::function<void()>, 240> InterruptManager::interruptVectorTable = {};

void InterruptManager::installInterruptHandler(uint32_t irq_number, std::function<void()> handler) {
    if (irq_number < interruptVectorTable.size()) {
        interruptVectorTable[irq_number] = handler;
    }
}

void InterruptManager::uninstallInterruptHandler(uint32_t irq_number) {
    if (irq_number < interruptVectorTable.size()) {
        interruptVectorTable[irq_number] = nullptr;
    }
}
