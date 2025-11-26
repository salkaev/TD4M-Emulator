CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = td4m_emulator
BUILD_DIR = build

SOURCES = Core.cpp registers.cpp other_func.cpp securely_func.cpp files.cpp TD4M_Emulator.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: clean
