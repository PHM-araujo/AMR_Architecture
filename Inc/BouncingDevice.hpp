#ifndef BOUNCINGDEVICE_HPP_
#define BOUNCINGDEVICE_HPP_

#include "DGPIO.hpp"

class BouncingDevice
{
public:
    BouncingDevice(char port, int pin);
    unsigned char getState();
    void sendEvent();

private:
    DGPIO device;
    unsigned char deviceState;
};

#endif // BOUNCINGDEVICE_HPP_
