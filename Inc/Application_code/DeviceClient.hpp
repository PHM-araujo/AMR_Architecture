#ifndef DEVICECLIENT_HPP_
#define DEVICECLIENT_HPP_

#include "Middleware/BouncingDevice.hpp"
#include "Application_code/ApplicationClient.hpp"
#include "Middleware/DebouncingTimer.hpp"

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
