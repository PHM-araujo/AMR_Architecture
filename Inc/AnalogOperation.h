#ifndef ANALOGOPERATION_H_
#define ANALOGOPERATION_H_

#include <optional>
#include <stdint.h>
#include <stdio.h>

namespace analog {

class AnalogOperation {
public:
	AnalogOperation(const unsigned int & pin, const unsigned int & adc, const unsigned int & channel);

	auto Read() -> std::optional<uint32_t>;

	auto Write(const float & value) -> bool;

	static auto ExamplePotenciometro() -> void;

private:
	auto LowLevelRead() -> std::optional<uint32_t>;

	auto LowLevelWrite(const uint32_t & value) -> bool;

	auto Init() -> void;

	unsigned int adc_;

	unsigned int channel_;

	unsigned int pin_;
};

}

#endif /* ANALOGOPERATION_H_ */
