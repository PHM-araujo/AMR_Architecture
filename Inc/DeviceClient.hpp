#ifndef DEVICECLIENT_HPP_
#define DEVICECLIENT_HPP_

#include "BouncingDevice.hpp"
#include "DebouncingTimer.hpp"
#include "ApplicationClient.hpp"

class DeviceClient
{
public:
    DeviceClient(char port, int pin, ApplicationClient *appClient);
    void eventReceive();

private:
    BouncingDevice device;
    unsigned char oldState;
    ApplicationClient *itsApplicationClient;
    DebouncingTimer itsDebouncingTimer;
};

#endif // DEVICECLIENT_HPP_
