CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = td4m_emulator

# Правильные имена файлов из вашей директории
SOURCES = Core.cpp registers.cpp securely_func.cpp "TD4M Emulator.cpp"
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: cleanm