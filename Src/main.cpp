
#define POTENCIOMETRO_EXAMPLE

#ifdef POTENCIOMETRO_EXAMPLE
#include <stdio.h>

#include <cinttypes>

#include "Inc/AnalogOperation.h"
#include "Inc/Examples/ApplyObserver.h"

int main(void) {
  ApplyObserver elemento_que_ouve;
  constexpr auto pin_micro = 0;
  constexpr auto adc_micro = 1;
  constexpr auto canal_micro = 8;
  constexpr auto bypass = true;
  analog::AnalogOperation analog_operation(pin_micro, adc_micro, canal_micro,
                                           bypass);

  while (true) {
    auto value = analog_operation.Read();
    if (value.has_value()) {
      printf("Value from loop = %" PRIu32 "\n", value.value());
    } else {
      printf("deu ruim\n");
    }

    for (auto counter = 0; counter < 200000; counter++);
  }

  return 0;
}

#endif

#ifdef AMR_ROBOT
#include <stdint.h>

#include "AMRRobot.hpp"

int main() {
  AMRRobot amr;
  amr.Init();
  amr.Run();
  return 0;
}

#endif
