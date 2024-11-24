# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable
TARGET = simulation

# Source files
SOURCES = main.cpp animal.cpp prey.cpp predator.cpp generate_predators.cpp generate_preys.cpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean target to remove the executable
clean:
	rm -f $(TARGET)