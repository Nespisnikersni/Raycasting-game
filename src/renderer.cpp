#include "renderer.h"
#include "map.h"
#include "raycast.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include <cstddef>
#include <iostream>
constexpr float PI = 3.141592653589793f;
constexpr float PLAYER_FOV = 60.0f;
constexpr size_t MAX_RAYCAST_DEPTH = 64;
constexpr int NUM_RAYS = 1200;
constexpr float COLUMN_WIDTH = SCREEN_W / (float)NUM_RAYS;

Ray castRay(sf::Vector2f start, float angleInDegrees, const Map &map);
void Renderer::draw3dView(sf::RenderTarget &target, const Player &player, const Map &map) {
    float horizonOffset = std::tan(player.angleY * PI / 180.0f) * SCREEN_H / 2.0f;
    
    sf::RectangleShape sky(sf::Vector2f(SCREEN_W,20 * SCREEN_H));
    sky.setFillColor(sf::Color(100, 100, 255));  
    sky.setPosition(0, -10 * SCREEN_H);  
    target.draw(sky);
    
    sf::RectangleShape ground(sf::Vector2f(SCREEN_W, SCREEN_H * 10));
    ground.setFillColor(sf::Color(131, 131, 131));  
    ground.setPosition(0, SCREEN_H / 2.0f - horizonOffset);  
    target.draw(ground);
	float angle = player.angle - PLAYER_FOV / 2.0f;
	float angleIncrement = PLAYER_FOV / (float) NUM_RAYS;
	float maxRenderDistance = MAX_RAYCAST_DEPTH * map.cellSize;
	for (size_t i = 0; i < NUM_RAYS;i++,angle += angleIncrement) {
		Ray ray = castRay(player.pos, angle,map);
		if (ray.hit) {
			ray.distance *= cos((player.angle - angle) * PI / 180.0f);
			float wallHeight = (map.cellSize * SCREEN_H) / ray.distance;
			float blightness = 1.0f - (ray.distance / maxRenderDistance);
			float shading = (ray.isVerticale ? 0.8f : 1.0f) * blightness;
			float wallOffset = (SCREEN_H / 2.0f - wallHeight / 2.0f) - tan(player.angleY * PI / 180.0f) * SCREEN_H / 2.0f;
			sf::RectangleShape column(sf::Vector2f(COLUMN_WIDTH,wallHeight));
			column.setPosition(i * COLUMN_WIDTH,wallOffset);
			column.setFillColor(sf::Color(255 * shading, 255 * shading, 255 * shading));
			target.draw(column);
		}	
	}
}

void Renderer::drawRays(sf::RenderTarget &target, const Player &player, const Map &map) {
	for (float angle = player.angle - PLAYER_FOV / 2; angle < player.angle + PLAYER_FOV; angle++) {
		Ray ray = castRay(player.pos, angle,map);
		if (ray.hit) {
			sf::Vertex line[] = {
        		sf::Vertex(player.pos),
        		sf::Vertex(ray.hitPos),
  	  		};
    	target.draw(line, 2, sf::Lines);
		}	
	}
}
