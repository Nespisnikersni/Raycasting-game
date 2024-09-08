#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player {
public:
    void draw(sf::RenderTarget &target);
    void update(float deltaTime);
    sf::Vector2f pos;
private:
    float angle;
};

#endif // PLAYER_H
