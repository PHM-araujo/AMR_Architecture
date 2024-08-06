#ifndef MEMORYMAP_HPP_
#define MEMORYMAP_HPP_

#include <cstdint>

// Endereços base
constexpr uint32_t PERIPHERAL_BASE =
    0x40000000;  // Endereço base para todos os periféricos
constexpr uint32_t AHB1PERIPH_BASE =
    PERIPHERAL_BASE + 0x00020000;  // Seção de memória dos periféricos AHB1
constexpr uint32_t APB2PERIPH_BASE =
    PERIPHERAL_BASE + 0x00010000;  // Seção de memória dos periféricos APB2
constexpr uint32_t APB1PERIPH_BASE =
    PERIPHERAL_BASE;  // Seção de memória dos periféricos APB1

// Endereços base para a GPIOA
constexpr uint32_t GPIOA_BASE = AHB1PERIPH_BASE + 0x0000;
constexpr uint32_t GPIOB_BASE = AHB1PERIPH_BASE + 0x0400;

// Endereço base para o RCC
constexpr uint32_t RCC_BASE = AHB1PERIPH_BASE + 0x3800;

// Endereço base para o EXTI
constexpr uint32_t EXTI_BASE = APB2PERIPH_BASE + 0x3C00;

// Endereço base para o SYSCFG
constexpr uint32_t SYSCFG_BASE = APB2PERIPH_BASE + 0x3800;

// Endereço base para o timer 2
constexpr uint32_t TIM2_BASE = APB1PERIPH_BASE + 0x0000;

// Endereço base para a NVIC
constexpr uint32_t NVIC_BASE = 0xE000E100;

// Endereço base para o ADC1
constexpr uint32_t ADC1_BASE = APB2PERIPH_BASE + 0x2000;

// Struct para a GPIO
struct GPIO_TypeDef {
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
};

// Struct para o RCC
struct RCC_TypeDef {
  volatile uint32_t CR;
  volatile uint32_t PLLCFGR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t AHB3RSTR;
  uint32_t RESERVED0;
  volatile uint32_t APB1RSTR;
  volatile uint32_t APB2RSTR;
  uint32_t RESERVED1[2];
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  volatile uint32_t AHB3ENR;
  uint32_t RESERVED2;
  volatile uint32_t APB1ENR;
  volatile uint32_t APB2ENR;
};

// Struct para EXTI
struct EXTI_TypeDef {
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
};

// Struct para o SYSCGF
struct SYSCFG_TypeDef {
  volatile uint32_t MEMRMP;
  volatile uint32_t PMC;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED[2];
  volatile uint32_t CMPCR;
};

// Struct para o timer
struct TIM_TypeDef {
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  uint32_t RESERVED1;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  uint32_t RESERVED2;
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
};

// Struct para o ADC
struct ADC_TypeDef {
  volatile uint32_t SR;     // Status register
  volatile uint32_t CR1;    // Control register 1
  volatile uint32_t CR2;    // Control register 2
  volatile uint32_t SMPR1;  // Sample time register 1
  volatile uint32_t SMPR2;  // Sample time register 2
  volatile uint32_t JOFR1;  // Injected channel data offset register 1
  volatile uint32_t JOFR2;  // Injected channel data offset register 2
  volatile uint32_t JOFR3;  // Injected channel data offset register 3
  volatile uint32_t JOFR4;  // Injected channel data offset register 4
  volatile uint32_t HTR;    // Higher threshold register
  volatile uint32_t LTR;    // Lower threshold register
  volatile uint32_t SQR1;   // Regular sequence register 1
  volatile uint32_t SQR2;   // Regular sequence register 2
  volatile uint32_t SQR3;   // Regular sequence register 3
  volatile uint32_t JSQR;   // Injected sequence register
  volatile uint32_t JDR1;   // Injected data register 1
  volatile uint32_t JDR2;   // Injected data register 2
  volatile uint32_t JDR3;   // Injected data register 3
  volatile uint32_t JDR4;   // Injected data register 4
  volatile uint32_t DR;     // Data register
};

// Definição dos ponteiros globais para os periféricos
// Declarações dos ponteiros globais para os periféricos
extern GPIO_TypeDef* GPIOA;
extern GPIO_TypeDef* GPIOB;
extern RCC_TypeDef* RCC;
extern EXTI_TypeDef* EXTI;
extern SYSCFG_TypeDef* SYSCFG;
extern TIM_TypeDef* TIM2;
extern ADC_TypeDef* ADC;
extern volatile uint32_t* NVIC_ISER;

#endif /* MEMORYMAP_HPP_ */
