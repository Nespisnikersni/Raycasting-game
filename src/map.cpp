#include "map.h"
#include <SFML/Graphics.hpp>

void Map::draw(sf::RenderTarget& target) const {
    if (grid.empty()) {
        return;
    }
    sf::RectangleShape background(sf::Vector2f(cellSize * grid[0].size(), cellSize * grid.size()));
    background.setFillColor(sf::Color::White);
    target.draw(background);

    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == ' ') {
                cell.setFillColor(sf::Color::Black);
            } else {
                cell.setFillColor(sf::Color::White);
            }
            cell.setPosition(x * cellSize, y * cellSize);
            target.draw(cell);
        }
    }
}
