CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = td4m_emulator
BUILD_DIR = build/Debug

SOURCES = TD4M_Emulator.cpp Core.cpp registers.cpp other_func.cpp securety_func.cpp files.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(BUILD_DIR)/*.o

.PHONY: clean
