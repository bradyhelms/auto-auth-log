CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SOURCES = $(SRC_DIR)/LogLine.cpp $(SRC_DIR)/main.cpp

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

EXEC = $(BUILD_DIR)/log_parser

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC)

.PHONY: all clean
