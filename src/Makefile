CXX = g++
CXXFLAGS = -std=c++17 -Wall -g $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
LDFLAGS = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)
TARGET = output
SRC = main.cpp map.cpp player.cpp renderer.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)