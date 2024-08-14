/*
 * BouncingDevice.cpp
 *
 *  Created on: Jul 13, 2024
 *      Author: Manoel
 */
#include "Middleware/BouncingDevice.hpp"

BouncingDevice::BouncingDevice(char port, int pin) : device(port, pin, INPUT), deviceState(0) {}

unsigned char BouncingDevice::getState()
{
    return device.digitalRead();
}

void BouncingDevice::sendEvent()
{
    // Implementar o envio do evento, pode ser chamar um método em DeviceClient
}




