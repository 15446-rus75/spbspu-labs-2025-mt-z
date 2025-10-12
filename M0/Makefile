CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++20

TARGET = program

SOURCE = main.cpp

all: build

build: $(TARGET)

$(TARGET): $(SOURCE)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -f $(TARGET)

.PHONY: all build run clean
