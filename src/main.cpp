#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include "map.h"
#include "player.h"
#include "renderer.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Raycasting");
    window.setFramerateLimit(30);
    std::string strings[] = {
        "serfs",
        "g   g",
        "g   g",
        "g   g",
        "ggggg"
    };
    
    const int numRows = sizeof(strings) / sizeof(strings[0]);
    std::vector<std::vector<char>> grid(numRows);
    for (int i = 0; i < numRows; ++i) {
        grid[i] = std::vector<char>(strings[i].begin(), strings[i].end());
    }
    Map map(32.0f, grid);
    sf::Clock clock;
    Player player;
    player.pos = sf::Vector2f(60,60);
    Renderer renderer;
    float currentTime,lastFrameTime,deltaTime;
    while (window.isOpen()) {
        currentTime = clock.getElapsedTime().asSeconds();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        player.update(deltaTime);
        window.clear();
        map.draw(window);
        player.draw(window);
        window.display();
    }

    return 0;
}
