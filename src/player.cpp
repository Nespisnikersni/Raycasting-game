#include "player.h"
#include "raycast.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include <ostream>

constexpr float PI = 3.14159f;
constexpr float TURN_SPEED = 120.0f;
constexpr float MOUSE_TURN_SPEED = 0.018f;
constexpr float MOVE_SPEED = 120.0f;

void Player::draw(sf::RenderTarget &target){
  sf::CircleShape circle(5.0f);
  circle.setOrigin(circle.getRadius(),circle.getRadius());
  circle.setPosition(pos);
  circle.setFillColor(sf::Color::Blue);
  sf::RectangleShape line(sf::Vector2f(24.0f,2.0f));
  line.setPosition(pos);
  line.setRotation(angle);
  line.setFillColor(sf::Color::Red);
  target.draw(line);
  target.draw(circle);
}
Ray castRay(sf::Vector2f start, float angleInDegrees, const Map &map);
void Player::update(float deltaTime, std::optional<sf::Vector2i> mouseDelta, const Map& map) {
    if (mouseDelta) {
        angle += mouseDelta->x * MOUSE_TURN_SPEED;
        angleY += mouseDelta->y * MOUSE_TURN_SPEED;
    }

    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        float radians = (angle - 90) * PI / 180.0f;
        movement.x += cos(radians) * MOVE_SPEED * deltaTime;
        movement.y += sin(radians) * MOVE_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        float radians = (angle + 90) * PI / 180.0f;
        movement.x += cos(radians) * MOVE_SPEED * deltaTime;
        movement.y += sin(radians) * MOVE_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        float radians = angle * PI / 180.0f;
        movement.x += cos(radians) * MOVE_SPEED * deltaTime;
        movement.y += sin(radians) * MOVE_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        float radians = angle * PI / 180.0f;
        movement.x -= cos(radians) * MOVE_SPEED * deltaTime;
        movement.y -= sin(radians) * MOVE_SPEED * deltaTime;
    }

    if (!movement.x && !movement.y) return; 

    handleCollision(movement, map);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        angleY -= TURN_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        angleY += TURN_SPEED * deltaTime;
    }
}

void Player::handleCollision(sf::Vector2f& movement, const Map& map) {
    sf::Vector2f testX = {movement.x, 0.f};
    if (checkCollision(testX, map)) {
        movement.x = 0;  
    }
    sf::Vector2f testY = {0.f, movement.y};
    if (checkCollision(testY, map)) {
        movement.y = 0;  
    }
    pos.x += movement.x;
    pos.y += movement.y;
}
bool Player::checkCollision(const sf::Vector2f& movement, const Map& map) {
    int tileX = static_cast<int>((pos.x + movement.x) / map.cellSize);
    int tileY = static_cast<int>((pos.y + movement.y) / map.cellSize);

    return map.grid[tileY][tileX] != ' ';
}
