#include "AnalogOperation.h"

#include <stdio.h>

#include <cinttypes>

namespace analog {

namespace {

constexpr auto MAX_CHANNEL_SUPPORT = 20;
constexpr auto FLASH_SIZE = 0x1FFF7A22;
constexpr auto RCC_AHB1 = 0x40023800;
constexpr auto GPIOA_BASE = 0x40020000;
constexpr auto GPIOB_BASE = 0x40020400;
constexpr auto RCC_BASE = 0x40023800;
constexpr auto ADC1_BASE = 0x40012000;
constexpr auto ADC2_BASE = 0x40012100;
constexpr auto GPIO_MODER_OFFSET = 0x00;
constexpr auto RCC_AHB1ENR_OFFSET = 0x30;
constexpr auto RCC_APB2ENR_OFFSET = 0x44;
constexpr auto ADC_SR_OFFSET = 0x00;
constexpr auto ADC_CR1_OFFSET = 0x04;
constexpr auto ADC_CR2_OFFSET = 0x08;
constexpr auto ADC_SMPR1_OFFSET = 0x0C;
constexpr auto ADC_SMPR2_OFFSET = 0x10;
constexpr auto ADC_SQR1_OFFSET = 0x2C;
constexpr auto ADC_SQR3_OFFSET = 0x34;
constexpr auto ADC_DR_OFFSET = 0x4C;
constexpr auto ADC_CR2_ADON = (1 << 0);
constexpr auto ADC_CR2_SWSTART = (1 << 30);

#define ESC_REG(x) (*((volatile uint32_t*)(x)))

auto get_gpio_base(unsigned int pin) -> volatile uint32_t* {
  if (pin < 8) {
    return reinterpret_cast<volatile uint32_t*>(GPIOA_BASE);
  } else if (pin < 16) {
    return reinterpret_cast<volatile uint32_t*>(GPIOB_BASE);
  } else {
    return nullptr;
  }
}

auto get_adc_base(unsigned int adc) -> volatile uint32_t* {
  if (adc == 1) {
    return reinterpret_cast<volatile uint32_t*>(ADC1_BASE);
  } else if (adc == 2) {
    return reinterpret_cast<volatile uint32_t*>(ADC2_BASE);
  } else {
    return nullptr;
  }
}

auto enable_gpio_clock(unsigned int pin) -> void {
  if (pin < 8) {
    ESC_REG(RCC_BASE + RCC_AHB1ENR_OFFSET) |=
        (1 << 0);  // Habilita o clock para GPIOA
  } else if (pin < 16) {
    ESC_REG(RCC_BASE + RCC_AHB1ENR_OFFSET) |=
        (1 << 1);  // Habilita o clock para GPIOB
  }
}

auto enable_adc_clock(unsigned int adc) -> void {
  if (adc == 1) {
    ESC_REG(RCC_BASE + RCC_APB2ENR_OFFSET) |=
        (1 << 8);  // Habilita o clock para ADC1
  } else if (adc == 2) {
    ESC_REG(RCC_BASE + RCC_APB2ENR_OFFSET) |=
        (1 << 9);  // Habilita o clock para ADC2
  }
}

}  // namespace

AnalogOperation::AnalogOperation(const unsigned int& pin,
                                 const unsigned int& adc,
                                 const unsigned int& channel)
    : adc_(adc), channel_(channel), pin_(pin) {
  if (adc < 1 || channel < 1 || channel > MAX_CHANNEL_SUPPORT) {
    printf("Invalid parameters on AnalogOperation constructor\n");
    return;
  }
  Init();
}

auto AnalogOperation::Read() -> std::optional<uint32_t> {
  auto register_value = LowLevelRead();
  if (register_value.has_value()) {
    // Aqui notifica os escutadores
    notify_.NotifyAnalogObserver(pin_, register_value.value());
  }
  return LowLevelRead();
}

auto AnalogOperation::Write(const float& value) -> bool {
  auto value_converted = static_cast<uint16_t>(value);
  return LowLevelWrite(value_converted);
}

auto AnalogOperation::LowLevelRead() -> std::optional<uint32_t> {
  volatile uint32_t* adcx = get_adc_base(adc_);
  if (!adcx) return {};

  // Iniciar a conversão
  ESC_REG(adcx + (ADC_CR2_OFFSET / 4)) |= ADC_CR2_SWSTART;

  // Aguardar a conclusão da conversão com timeout
  uint32_t timeout = 1000000;
  while (!(ESC_REG(adcx + (ADC_SR_OFFSET / 4)) & (1 << 1)) && --timeout);

  // Verificar timeout
  if (timeout == 0) {
    return {};  // Timeout ocorreu
  }

  // Ler o valor do ADC
  uint32_t value_from_adc = ESC_REG(adcx + (ADC_DR_OFFSET / 4));
  return value_from_adc;
}

auto AnalogOperation::LowLevelWrite(const uint32_t& value) -> bool {
  return false;
}

auto AnalogOperation::Init() -> void {
  volatile uint32_t* gpiox = get_gpio_base(pin_);
  volatile uint32_t* adcx = get_adc_base(adc_);

  if (!gpiox || !adcx) {
    printf("Error on set parameters\n");
    return;
  }

  // Habilitar o clock do GPIO e do ADC
  enable_gpio_clock(pin_);
  enable_adc_clock(adc_);

  // Configurar o pino como modo analógico
  ESC_REG(gpiox + (GPIO_MODER_OFFSET / 4)) |= (3 << (pin_ * 2));

  // Configuração do ADC
  ESC_REG(adcx + (ADC_CR1_OFFSET / 4)) &= ~(1 << 8);   // SCAN mode disabled
  ESC_REG(adcx + (ADC_CR1_OFFSET / 4)) &= ~(3 << 24);  // 12-bit resolution
  ESC_REG(adcx + (ADC_SQR1_OFFSET / 4)) &=
      ~(1 << 20);  // (1 conversion, so 0b0000)
  ESC_REG(adcx + (ADC_SQR3_OFFSET / 4)) &=
      ~(0x3FFFFFFF);  // Clear regular sequence register
  ESC_REG(adcx + (ADC_SQR3_OFFSET / 4)) |= channel_;   // Set the ADC channel
  ESC_REG(adcx + (ADC_CR2_OFFSET / 4)) &= ~(1 << 1);   // Single conversion mode
  ESC_REG(adcx + (ADC_CR2_OFFSET / 4)) &= ~(1 << 11);  // Right alignment

  if (channel_ < 10) {
    ESC_REG(adcx + (ADC_SMPR2_OFFSET / 4)) |=
        (7 << (channel_ * 3));  // Set sample time for channels 0-9
  } else {
    ESC_REG(adcx + (ADC_SMPR1_OFFSET / 4)) |=
        (7 << ((channel_ - 10) * 3));  // Set sample time for channels 10-18
  }

  ESC_REG(adcx + (ADC_CR2_OFFSET / 4)) |= ADC_CR2_ADON;  // Enable ADC
}

auto AnalogOperation::RegisterObserver(std::shared_ptr<AnalogObserver> observer)
    -> void {
  notify_.Attach(observer);
}

/* ===============================================
 *                  FAKE MAIN
 * ===============================================
 */
auto AnalogOperation::ExamplePotenciometro() -> void {
  class ObjetoParaEscutar : public AnalogObserver {
   private:
    void OnAnalogObserver(const unsigned int& pin,
                          const unsigned int& value) override {
      printf("Values receveid [ %d, %d ]\n", pin, value);
    }
  };

  // Instace
  constexpr auto pin_micro = 4;
  constexpr auto adc_micro = 1;
  constexpr auto canal_micro = 4;
  auto analog_operation = std::make_shared<analog::AnalogOperation>(
      pin_micro, adc_micro, canal_micro);
  auto observer = std::make_shared<ObjetoParaEscutar>();

  // Registra objeto que ira escutar
  analog_operation->RegisterObserver(observer);

  // Loop
  while (true) {
    auto value = analog_operation->Read();
    if (value.has_value()) {
      printf("Value from loop = %" PRIu32 "\n", value.value());
    } else {
      printf("deu ruim\n");
    }

    for (auto counter = 0; counter < 20000; counter++);
  }
}

}  // namespace analog
