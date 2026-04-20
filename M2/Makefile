CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -fopenmp
TARGET := program
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

all: build

build: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET) $(ARGS)

clean:
	@rm -f $(OBJECTS) $(TARGET)

.PHONY: all build run clean
