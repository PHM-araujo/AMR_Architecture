# STM32F407G-DISC1 Project

**Warning:** Ensure that all source files (`AnalogSignal.h`, `AnalogSignal.cpp`, `DigitalSignal.h`, `DigitalSignal.cpp`, `InterruptManager.h`, `InterruptManager.cpp`, `main.cpp`) are placed in the `Src` directory of your STM32CubeIDE project to run the code correctly.

This project demonstrates how to interface with analog and digital signals and handle interrupts on the STM32F407G-DISC1 board. The project is implemented in C++ without using any external libraries or headers like `stm32f4xx.h`.

## Project Structure

The project consists of several classes and functions organized into different files to handle various aspects of the microcontroller's functionality:

### AnalogSignal Class
- **File**: `AnalogSignal.h`, `AnalogSignal.cpp`
- **Purpose**: This class manages the reading and writing of analog signals using the ADC and DAC peripherals of the STM32F407G-DISC1.
- **Key Methods**:
  - `AnalogSignal(int pin)`: Constructor to initialize the analog signal on the specified pin.
  - `int read()`: Reads an analog value from the pin.
  - `void write(int value)`: Writes an analog value to the pin via DAC.

### DigitalSignal Class
- **File**: `DigitalSignal.h`, `DigitalSignal.cpp`
- **Purpose**: This class handles reading from and writing to digital GPIO pins.
- **Key Methods**:
  - `DigitalSignal(int pin)`: Constructor to initialize the digital signal on the specified pin.
  - `int read()`: Reads a digital value from the pin.
  - `void write(int value)`: Writes a digital value to the pin.

### InterruptManager Class
- **File**: `InterruptManager.h`, `InterruptManager.cpp`
- **Purpose**: This class manages external interrupts on a specified GPIO pin.
- **Key Methods**:
  - `InterruptManager(int pin, void (*callback)())`: Constructor to initialize the interrupt on the specified pin with a callback function.
  - `void enable()`: Enables the interrupt.
  - `void disable()`: Disables the interrupt.

### UART Functions
- **File**: `main.cpp`
- **Purpose**: These functions initialize the UART for serial communication and provide methods to send data via UART.
- **Key Functions**:
  - `void UART2_Init()`: Initializes UART2 for serial communication.
  - `void UART2_Write(char ch)`: Sends a single character via UART.
  - `void UART2_WriteString(const char* str)`: Sends a string via UART.

### Main Program
- **File**: `main.cpp`
- **Purpose**: The main program initializes the peripherals, configures the signals, and runs the main loop to monitor and control the signals.
- **Key Components**:
  - `volatile bool interruptOccurred`: Flag to indicate if an interrupt has occurred.
  - `void myInterruptHandler()`: Interrupt handler function.
  - `int main()`: Main function that initializes peripherals, sets up signals, and runs the main loop.

## How to Run the Project

1. **Set Up the Development Environment**:
   - Install STM32CubeIDE or another suitable IDE for STM32 development.
   - Ensure the STM32F407G-DISC1 board is connected to your computer.

2. **Load the Project**:
   - Open the project in STM32CubeIDE.
   - Ensure all source files (`AnalogSignal.h`, `AnalogSignal.cpp`, `DigitalSignal.h`, `DigitalSignal.cpp`, `InterruptManager.h`, `InterruptManager.cpp`, `main.cpp`) are included in the `Src` directory of the project.

3. **Build and Flash**:
   - Compile the project within the IDE.
   - Flash the compiled binary to the STM32F407G-DISC1 board.

4. **Monitor Serial Output**:
   - Open a serial terminal application (such as PuTTY).
   - Configure the terminal to the correct COM port and baud rate (9600).
   - Monitor the serial output for analog and digital signal values and interrupt occurrences.

## Monitoring the Execution

To monitor the execution of the program on the STM32F407G-DISC1 board:

1. **Connect the board to the computer via USB**.
2. **Open a serial terminal** (PuTTY, Tera Term, or the Arduino IDE serial monitor) and configure it to the correct COM port and baud rate (9600 in the example above).
3. **Observe the terminal** to see the analog and digital readings being printed periodically.

## Tests

### Digital Input
1. **Connect a button to pin PA1**.
2. Observe the changes in the digital value on the terminal as you press the button.

### Analog Input
1. **Connect a potentiometer to pin PA0**.
2. Observe the changes in the analog value on the terminal as you adjust the potentiometer.

### Interrupts
1. **Connect a button to pin PA0 configured for interrupts**.
2. Observe if the LED connected to pin PA5 toggles when you press the button.

This project provides a basic framework for handling analog and digital signals and managing interrupts on the STM32F407G-DISC1 board, serving as a starting point for more complex applications.
