#include "AnalogOperation.h"

#include <stdio.h>

#include "HAL.hpp"
#include "MemoryMap.hpp"
#include "Notify/Notify.h"

namespace analog {

AnalogOperation::AnalogOperation(const unsigned int& pin,
                                 const unsigned int& adc,
                                 const unsigned int& channel, const bool bypass)
    : adc_(adc), channel_(channel), pin_(pin), bypass_(bypass) {
  if (adc < 1 || channel < 1) {
    printf("Invalid parameters on AnalogOperation constructor\n");
    return;
  }
  if (!bypass_) {
    HAL::configureADC(pin_, adc_, channel_);
  }
}

auto AnalogOperation::Read() -> std::optional<uint32_t> {
  std::optional<uint32_t> register_value;
  if (!bypass_) {
    register_value = HAL::obtenhaADCvalue(pin_, adc_, channel_);
  } else {
    register_value = 10;
  }
  if (register_value.has_value()) {
    // Aqui notifica os escutadores
    Notify::NotifyAnalogObserver(pin_, register_value.value());
  }
  return register_value;
}

auto AnalogOperation::Write(const float& value) -> bool { return false; }
}  // namespace analog
