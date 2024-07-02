#include "AnalogOperation.h"

namespace {
#define MAX_CHANNEL_SUPPORT			20
#define FLASH_SIZE					0x1FFF7A22
#define RCC_AHB1					0x40023800
#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))

#define GPIOA_BASE                  0x40020000
#define GPIOB_BASE                  0x40020400
#define RCC_BASE                    0x40023800
#define ADC1_BASE                   0x40012000
#define ADC2_BASE                   0x40012100

#define GPIO_MODER_OFFSET           0x00
#define RCC_AHB1ENR_OFFSET          0x30
#define RCC_APB2ENR_OFFSET          0x44
#define ADC_SR_OFFSET               0x00
#define ADC_CR1_OFFSET              0x04
#define ADC_CR2_OFFSET              0x08
#define ADC_SMPR1_OFFSET            0x0C
#define ADC_SMPR2_OFFSET            0x10
#define ADC_SQR1_OFFSET             0x2C
#define ADC_SQR3_OFFSET             0x34
#define ADC_DR_OFFSET               0x4C

#define ADC_SR_EOC                  (1 << 1)
#define ADC_CR2_ADON                (1 << 0)
#define ADC_CR2_SWSTART             (1 << 30)

volatile uint32_t *get_gpio_base(unsigned int pin) {
    if (pin < 8) {
        return (volatile uint32_t *)GPIOA_BASE;
    } else if (pin < 16) {
        return (volatile uint32_t *)GPIOB_BASE;
    } else {
        return nullptr;
    }
}

volatile uint32_t *get_adc_base(unsigned int adc) {
    if (adc == 1) {
        return (volatile uint32_t *)ADC1_BASE;
    } else if (adc == 2) {
        return (volatile uint32_t *)ADC2_BASE;
    } else {
        return nullptr;
    }
}

//void enable_gpio_clock(unsigned int pin) {
//    if (pin < 8) {
//        ESC_REG(RCC_BASE + RCC_AHB1ENR_OFFSET) |= (1 << 0); // Enable GPIOA clock
//    } else if (pin < 16) {
//        ESC_REG(RCC_BASE + RCC_AHB1ENR_OFFSET) |= (1 << 1); // Enable GPIOB clock
//    }
//}

void enable_adc_clock(unsigned int adc) {
    if (adc == 1) {
        ESC_REG(RCC_BASE + RCC_APB2ENR_OFFSET) |= (1 << 8); // Enable ADC1 clock
    } else if (adc == 2) {
        ESC_REG(RCC_BASE + RCC_APB2ENR_OFFSET) |= (1 << 9); // Enable ADC2 clock
    }
}

}


AnalogOperation::AnalogOperation(const unsigned int & pin, const unsigned int & adc, const unsigned int & channel) : adc_(adc), channel_(channel), pin_(pin) {
	if (adc < 1 || channel < 1 || channel > MAX_CHANNEL_SUPPORT ){
		printf("Invalid parameters on AnalogOperation constructor\n");
	}
	Init();
}


auto AnalogOperation::Read() -> std::optional<uint32_t> {
	auto value = LowLevelRead();
	if (value.has_value()){
		return  value.value();
	}
	return {};
}


auto AnalogOperation::Write(const float & value) -> bool {
	auto value_converted = static_cast<uint16_t>(value);
	return LowLevelWrite(value_converted);
}


auto AnalogOperation::LowLevelRead() -> std::optional<uint32_t> {
    auto adcx = get_adc_base(adc_);
    if (!adcx) return {};

    adcx[ADC_CR2_OFFSET / 4] |= ADC_CR2_SWSTART; // Start conversion

    while (!(adcx[ADC_SR_OFFSET / 4] & ADC_SR_EOC)); // Wait for conversion to complete

    return adcx[ADC_DR_OFFSET / 4]; // Read the ADC value
}


auto AnalogOperation::LowLevelWrite(const uint32_t & value) -> bool {
	return false;
}

auto AnalogOperation::Init() -> void {
    volatile uint32_t *gpiox = get_gpio_base(pin_);
    volatile uint32_t *adcx = get_adc_base(adc_);

    if (!gpiox || !adcx) {
        printf("Error on set parameters\n");
        return;
    }

    //enable_gpio_clock(pin_);
    enable_adc_clock(adc_);

    gpiox[GPIO_MODER_OFFSET / 4] |= (3 << (pin_ * 2)); // Set pin to analog mode

    adcx[ADC_CR1_OFFSET / 4] &= ~(1 << 8); // SCAN mode disabled
    adcx[ADC_CR1_OFFSET / 4] &= ~(3 << 24); // 12-bit resolution
    adcx[ADC_SQR1_OFFSET / 4] &= ~(0x0F << 20); // Single conversion
    adcx[ADC_SQR3_OFFSET / 4] &= ~(0x3FFFFFFF); // Clear regular sequence register
    adcx[ADC_SQR3_OFFSET / 4] |= channel_; // Set the ADC channel
    adcx[ADC_CR2_OFFSET / 4] &= ~(1 << 1); // Single conversion mode
    adcx[ADC_CR2_OFFSET / 4] &= ~(1 << 11); // Right alignment

    if (channel_ < 10) {
        adcx[ADC_SMPR2_OFFSET / 4] |= (7 << (channel_ * 3)); // Set sample time for channels 0-9
    } else {
        adcx[ADC_SMPR1_OFFSET / 4] |= (7 << ((channel_ - 10) * 3)); // Set sample time for channels 10-18
    }

    adcx[ADC_CR2_OFFSET / 4] |= ADC_CR2_ADON; // Enable ADC
}

