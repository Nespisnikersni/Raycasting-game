#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>

class Player {
public:
    void draw(sf::RenderTarget &target);
    void update(float deltaTime,std::optional<sf::Vector2i> mouseDelta = std::nullopt,const Map& map = Map());
    bool checkCollision(const sf::Vector2f& direction, const Map& map);
    sf::Vector2f pos;
    float angle;
	float angleY = 40;
private:
    sf::Vector2f normalize(const sf::Vector2f& v);
    sf::Vector2f getNormalAtCollision(float x, float y, const Map& map);
    void handleCollision(sf::Vector2f& movement,const Map& map);
};

#endif // PLAYER_H
