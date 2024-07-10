#include "DeviceClient.hpp"

DeviceClient::DeviceClient(char port, int pin, ApplicationClient *appClient)
    : device(port, pin), oldState(0), itsApplicationClient(appClient) {}

void DeviceClient::eventReceive()
{
    unsigned char newState = device.getState();
    if (newState != oldState)
    {
        itsDebouncingTimer.delay(50); // Delay para debouncing
        newState = device.getState(); // Leia o estado novamente após o delay
        if (newState != oldState)
        {
            oldState = newState;
            itsApplicationClient->deviceEventReceive(newState);
        }
    }
}
