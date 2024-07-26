#ifndef ANALOGOPERATION_H_
#define ANALOGOPERATION_H_

#include <stdint.h>

#include <optional>

namespace analog {

class AnalogOperation {
 public:
  AnalogOperation(const unsigned int& pin, const unsigned int& adc,
                  const unsigned int& channel, const bool bypass = false);

  auto Read() -> std::optional<uint32_t>;

  auto Write(const float& value) -> bool;

 private:
  auto LowLevelRead() -> std::optional<uint32_t>;

  auto LowLevelWrite(const uint32_t& value) -> bool;

  auto Init() -> void;

  unsigned int adc_;

  unsigned int channel_;

  unsigned int pin_;

  bool bypass_;
};

}  // namespace analog

#endif /* ANALOGOPERATION_H_ */
