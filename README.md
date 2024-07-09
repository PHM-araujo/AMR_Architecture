# AMR_Architecture

Este repositório contém a implementação de uma arquitetura para robôs móveis autônomos (AMR) utilizando a placa STM32F407G-DISC1. Este projeto faz parte da disciplina de Mestrado em Arquitetura e Padrões de Projeto de Software.

## Estrutura do Projeto

- **AMR_Architecture Debug.launch**
- **Inc**
  - AMRRobot.hpp
  - AnalogOperation.h
  - DGPIO.hpp
  - InterruptOperation.hpp
- **README.md**
- **STM32F407VGTX_FLASH.ld**
- **STM32F407VGTX_RAM.ld**
- **Src**
  - AMRRobot.cpp
  - AnalogOperation.cpp
  - DGPIO.cpp
  - InterruptOperation.cpp
  - main.cpp
  - syscalls.c
  - sysmem.c
- **Startup**
  - startup_stm32f407vgtx.s

## Descrição dos Arquivos

- **Inc/**: Contém os arquivos de cabeçalho (.h e .hpp) com declarações de classes e funções.
  - `AMRRobot.hpp`: Declarações relacionadas ao robô AMR.
  - `AnalogOperation.h`: Declarações para operações analógicas.
  - `DGPIO.hpp`: Declarações para operações de GPIO digital.
  - `InterruptOperation.hpp`: Declarações para operações de interrupções.

- **Src/**: Contém os arquivos de código-fonte (.cpp e .c) com a implementação das classes e funções.
  - `AMRRobot.cpp`: Implementação das funcionalidades do robô AMR.
  - `AnalogOperation.cpp`: Implementação das operações analógicas.
  - `DGPIO.cpp`: Implementação das operações de GPIO digital.
  - `InterruptOperation.cpp`: Implementação das operações de interrupções.
  - `main.cpp`: Função principal do programa.
  - `syscalls.c`: Implementações de syscalls.
  - `sysmem.c`: Implementação da memória do sistema.

- **Startup/**: Contém o arquivo de inicialização.
  - `startup_stm32f407vgtx.s`: Arquivo de inicialização para a placa STM32F407VGTX.

- **STM32F407VGTX_FLASH.ld**: Script de link para a memória flash da STM32F407VGTX.
- **STM32F407VGTX_RAM.ld**: Script de link para a memória RAM da STM32F407VGTX.

## Objetivo do Projeto

O objetivo deste projeto é desenvolver uma arquitetura para um robô móvel autônomo, abordando as seguintes funcionalidades:

1. **Leitura e Escrita de um Sinal Analógico**: Implementação de funções para leitura e escrita de sinais analógicos.
2. **Leitura e Escrita de um Sinal Digital**: Implementação de funções para leitura e escrita de sinais digitais.
3. **Gerenciamento de Interrupções**: Implementação de rotinas de interrupção para lidar com eventos assíncronos.
4. **Implementação sem uso de bibliotecas externas**: O código deve ser escrito sem a utilização de bibliotecas como HAL (Hardware Abstraction Layer) ou outras bibliotecas externas, utilizando apenas C, C++ ou Rust.

## Instalação


- Clone este repositório:
   ```sh
   git clone https://github.com/PHM-araujo/AMR_Architecture.git
   ```

