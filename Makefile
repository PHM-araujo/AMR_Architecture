# Compiler
CXX := g++

# Directories
SRC_DIR := Src
INC_DIR := Inc
EXAMPLES_DIR := Inc/Examples
BUILD_DIR := .build

# Source files
SRC_FILES := $(SRC_DIR)/AnalogOperation.cpp $(SRC_DIR)/Notify.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/MemoryMap.cpp $(SRC_DIR)/HAL.cpp

# Header directories
INC_DIRS := -I $(INC_DIR)/Notify -I $(INC_DIR)/Examples -I $(INC_DIR)

# Output binary
TARGET := $(BUILD_DIR)/run_example

# Compiler flags
CXXFLAGS := -std=c++20 -Wall

# Create build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Default target: build and run
all: $(BUILD_DIR) $(TARGET)
	@echo "Running the program..."
	@./$(TARGET)

# Build target
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -o $@ $^

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)
