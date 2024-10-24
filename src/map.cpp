#include "map.h"
#include <SFML/Graphics.hpp>

void Map::draw(sf::RenderTarget& target) const {
    if (grid.empty()) {
        return;
    }

	sf::RectangleShape cell(sf::Vector2f(cellSize * 0.95f, cellSize * 0.95f));
    
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == ' ') {
                cell.setFillColor(sf::Color::Black);
            } else {
                cell.setFillColor(sf::Color::White);
            }
			cell.setPosition(sf::Vector2f(x, y) * cellSize + sf::Vector2f(cellSize * 0.025f, cellSize * 0.025f));
            target.draw(cell);
        }
    }
}
