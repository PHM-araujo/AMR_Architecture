#include "AnalogOperation.h"

#include <stdio.h>

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
    Init();
  }
}

auto AnalogOperation::Read() -> std::optional<uint32_t> {
  std::optional<uint32_t> register_value;
  if (!bypass_) {
    register_value = LowLevelRead();
  } else {
    register_value = 10;
  }
  if (register_value.has_value()) {
    // Aqui notifica os escutadores
    Notify::NotifyAnalogObserver(pin_, register_value.value());
  }
  return register_value;
}

auto AnalogOperation::Write(const float& value) -> bool {
  auto value_converted = static_cast<uint16_t>(value);
  return LowLevelWrite(value_converted);
}

auto AnalogOperation::LowLevelRead() -> std::optional<uint32_t> {
  ADC_TypeDef* ADC1 = reinterpret_cast<ADC_TypeDef*>(APB2PERIPH_BASE + 0x2000);

  // 1. Inicia a conversão do ADC
  ADC1->CR2 |= (1 << 30);  // Inicia a conversão de software (bit 30)

  // 2. Espera a conversão terminar
  while (!(ADC1->SR & (1 << 1)));  // Espera pelo EOC (End Of Conversion)

  // 3. Retorna o valor convertido
  return ADC1->DR;
}

auto AnalogOperation::LowLevelWrite(const uint32_t& value) -> bool {
  return false;
}

auto AnalogOperation::Init() -> void {
  // 1. Habilitar o Clock para GPIOB e ADC1
  RCC->AHB1ENR |= (1 << 1);  // Habilita o clock para GPIOB (bit 1)
  RCC->APB2ENR |= (1 << 8);  // Habilita o clock para ADC1 (bit 8)

  // 2. Configurar o pino PB0 como entrada analógica
  GPIOB->MODER |= (3 << (2 * pin_));  // Configura PB0 como analógico (11b)

  // 3. Configurar o ADC1
  ADC_TypeDef* ADC1 = reinterpret_cast<ADC_TypeDef*>(
      APB2PERIPH_BASE + 0x2000);  // Endereço base do ADC1

  ADC1->CR1 = 0;  // Reseta CR1
  ADC1->CR2 = 0;  // Reseta CR2

  ADC1->CR1 |= (1 << 24);  // Resolução 10 bits (01b no bit 24)
  ADC1->SQR3 = adc_channel;
  ADC1->CR2 |= (1 << 0);  // Liga o ADC1 (bit 0)

  // 4. Calibração do ADC (opcional)
  ADC1->CR2 |= (1 << 2);         // Inicia calibração (bit 2)
  while (ADC1->CR2 & (1 << 2));  // Espera a calibração terminar
}

}  // namespace analog
