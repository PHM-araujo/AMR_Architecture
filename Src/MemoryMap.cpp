#include "MemoryMap.hpp"

// Definição dos ponteiros globais para os periféricos
GPIO_TypeDef *GPIOA = reinterpret_cast<GPIO_TypeDef *>(GPIOA_BASE);
GPIO_TypeDef *GPIOB = reinterpret_cast<GPIO_TypeDef *>(GPIOB_BASE);
GPIO_TypeDef *GPIOC = reinterpret_cast<GPIO_TypeDef *>(GPIOC_BASE);
GPIO_TypeDef *GPIOD = reinterpret_cast<GPIO_TypeDef *>(GPIOD_BASE);
GPIO_TypeDef *GPIOE = reinterpret_cast<GPIO_TypeDef *>(GPIOE_BASE);
GPIO_TypeDef *GPIOF = reinterpret_cast<GPIO_TypeDef *>(GPIOF_BASE);
GPIO_TypeDef *GPIOG = reinterpret_cast<GPIO_TypeDef *>(GPIOG_BASE);
GPIO_TypeDef *GPIOH = reinterpret_cast<GPIO_TypeDef *>(GPIOH_BASE);
GPIO_TypeDef *GPIOI = reinterpret_cast<GPIO_TypeDef *>(GPIOI_BASE);
RCC_TypeDef *RCC = reinterpret_cast<RCC_TypeDef *>(RCC_BASE);
EXTI_TypeDef *EXTI = reinterpret_cast<EXTI_TypeDef *>(EXTI_BASE);
SYSCFG_TypeDef *SYSCFG = reinterpret_cast<SYSCFG_TypeDef *>(SYSCFG_BASE);
TIM_TypeDef *TIM2 = reinterpret_cast<TIM_TypeDef *>(TIM2_BASE);
volatile uint32_t *NVIC_ISER = reinterpret_cast<volatile uint32_t *>(NVIC_BASE);
