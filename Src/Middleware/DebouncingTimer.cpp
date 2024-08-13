#include "Middleware/DebouncingTimer.hpp"
#include "HAL/HAL.hpp"

void DebouncingTimer::delay(unsigned int delayTime)
{
    HAL::delay(delayTime);
}




