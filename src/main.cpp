#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include "map.h"
#include "player.h"
#include "renderer.h"
#include <SFML/Window/Mouse.hpp>
#include <yaml.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Raycasting");
    window.setFramerateLimit(144);
    window.setMouseCursorVisible(false);
    std::string strings[] = {
        "serfssefsefsfesfsf",
        "g                g",
        "gfesfefesf      gg",
        "g                g",
        "g  ff     fesfesfg",
        "g   ff           g",
        "g    ff          g",
        "g     ff         g",
        "g                g",
        "gfff     f       g",
        "g        f       g",
        "g        f       g",
        "g        f       g",
        "gggggggggggggggggg"
    };
    
    const int numRows = sizeof(strings) / sizeof(strings[0]);
    std::vector<std::vector<char>> grid(numRows);
    for (int i = 0; i < numRows; ++i) {
        grid[i] = std::vector<char>(strings[i].begin(), strings[i].end());
    }
    Map map(32.0f, grid);
    sf::Clock clock;
    Player player;
    player.pos = sf::Vector2f(50,50);
    Renderer renderer;
    float currentTime,lastFrameTime,deltaTime;
    std::optional<sf::Vector2i> previousMousePosition;
    sf::CircleShape cursor(3);
    cursor.setPosition(sf::Vector2f(window.getSize().x / 2,window.getSize().y / 2));
    while (window.isOpen()) {
        currentTime = clock.getElapsedTime().asSeconds();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    if (window.hasFocus()) {
        sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
        std::optional<sf::Vector2i> mouseDelta;
        
        if (previousMousePosition) {
            mouseDelta = currentMousePosition - center;
        }

        previousMousePosition = center;

        sf::Mouse::setPosition(center, window);

        player.update(deltaTime, mouseDelta,map);
    }
     
    window.clear();
    renderer.draw3dView(window, player, map);
    map.draw(window);
    player.draw(window);
    window.draw(cursor);
    window.display();
}
    return 0;
}
