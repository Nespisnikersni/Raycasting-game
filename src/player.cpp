#include "player.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>

constexpr float PI = 3.14159f;
constexpr float TURN_SPEED = 120.0f;
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
void Player::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        angle -= TURN_SPEED * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        angle += TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        float radians = angle * PI / 180.0f;
        pos.x += cos(radians) * MOVE_SPEED * deltaTime;
        pos.y += sin(radians) * MOVE_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        float radians = angle * PI / 180.0f;
        pos.x -= cos(radians) * MOVE_SPEED * deltaTime;
        pos.y -= sin(radians) * MOVE_SPEED * deltaTime;
    }
}

