#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map() : cellSize(1.0f), grid(10, std::vector<char>(10, ' ')) {}
    Map(float cellSize, int width, int height) 
        : cellSize(cellSize), grid(height, std::vector<char>(width, ' ')) {}
    Map(float cellSize, std::vector<std::vector<char>> grid) 
        : cellSize(cellSize), grid(grid) {}

    void draw(sf::RenderTarget& target) const;

    float cellSize;
    std::vector<std::vector<char>> grid; 
};

#endif
