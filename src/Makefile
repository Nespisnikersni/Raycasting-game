CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I../libs/SFML/include -I../libs/include
LDFLAGS = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

# Папка для сборки
BUILD_DIR = ../build
TARGET = $(BUILD_DIR)/output
SRC = main.cpp map.cpp player.cpp renderer.cpp
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))

# Создаем папку build, если её нет, и собираем
all: $(TARGET)
	@echo "Build complete. Running..."
	LD_LIBRARY_PATH=../libs/SFML/lib ./$(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Сборка объектных файлов
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR)
