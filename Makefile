CXX = g++
CXXFLAGS = -std=c++17 -Wall -g  # Enable C++17, all warnings, and debug symbols
TARGET = log_parser
SRCS = main.cpp LogLine.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

distclean: clean
	rm -f *~

.PHONY: all clean distclean

