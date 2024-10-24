#include "renderer.h"
#include "map.h"
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

struct Ray{
	sf::Vector2f hitPos;
	float distance;
	bool hit;
	bool isVerticle;
};
static Ray castRay(sf::Vector2f start,float angleInDegrees,const Map &map);
void Renderer::draw3dView(sf::RenderTarget &target, const Player &player, const Map &map) {
	float horizonOffset = std::tan(player.angleY * PI / 180.0f) * SCREEN_H / 2.0f;
    sf::RectangleShape sky(sf::Vector2f(SCREEN_W, SCREEN_H / 2.0f));
    sky.setFillColor(sf::Color(100, 100, 255));
    sky.setPosition(0, -horizonOffset);
    target.draw(sky);
    sf::RectangleShape ground(sf::Vector2f(SCREEN_W, SCREEN_H / 2.0f));
    ground.setFillColor(sf::Color(131, 131, 131));
    ground.setPosition(0, SCREEN_H / 2.0f - horizonOffset);  // Смещаем пол
    target.draw(ground);
	float angle = player.angle - PLAYER_FOV / 2.0f;
	float angleIncrement = PLAYER_FOV / (float) NUM_RAYS;
	float maxRenderDistance = MAX_RAYCAST_DEPTH * map.cellSize;
	for (size_t i = 0; i < NUM_RAYS;i++,angle += angleIncrement) {
		Ray ray = castRay(player.pos, angle,map);
		if (ray.hit) {
			ray.distance *= cos((player.angle - angle) * PI / 180.0f);
			float wallHeight = (map.cellSize * SCREEN_H) / ray.distance;
			if(wallHeight > SCREEN_H){
				wallHeight = SCREEN_H;
			}
			float blightness = 1.0f - (ray.distance / maxRenderDistance);
			float shading = (ray.isVerticle ? 0.8f : 1.0f) * blightness;
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
Ray castRay(sf::Vector2f start, float angleInDegrees, const Map &map) {
  float angle = angleInDegrees * PI / 180.0f;
  float vtan = -std::tan(angle), htan = -1.0f / std::tan(angle);
  float cellSize = map.cellSize;
  bool hit = false;
  size_t vdof = 0, hdof = 0;
  float vdist = std::numeric_limits<float>::max();
  float hdist = std::numeric_limits<float>::max();
  sf::Vector2f vRayPos, hRayPos, offset;
  if (std::cos(angle) > 0.001f) {
    vRayPos.x = std::floor(start.x / cellSize) * cellSize + cellSize;
    vRayPos.y = (start.x - vRayPos.x) * vtan + start.y;
    offset.x = cellSize;
    offset.y = -offset.x * vtan;
  } else if (std::cos(angle) < -0.001f) {
    vRayPos.x = std::floor(start.x / cellSize) * cellSize - 0.01f;
    vRayPos.y = (start.x - vRayPos.x) * vtan + start.y;
    offset.x = -cellSize;
    offset.y = -offset.x * vtan;
  } else {
    vdof = MAX_RAYCAST_DEPTH;
  }
  const auto &grid = map.grid;
  for (; vdof < MAX_RAYCAST_DEPTH; vdof++) {
    int mapX = (int)(vRayPos.x / cellSize);
    int mapY = (int)(vRayPos.y / cellSize);
    if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX] != ' ') {
      hit = true;
      vdist = std::sqrt((vRayPos.x - start.x) * (vRayPos.x - start.x) +
                        (vRayPos.y - start.y) * (vRayPos.y - start.y));
      break;
    }
    vRayPos += offset;
  }
  if (sin(angle) > 0.001f) {
    hRayPos.y = std::floor(start.y / cellSize) * cellSize + cellSize;
    hRayPos.x = (start.y - hRayPos.y) * htan + start.x;
    offset.y = cellSize;
    offset.x = -offset.y * htan;
  } else if (sin(angle) < -0.001f) {
    hRayPos.y = std::floor(start.y / cellSize) * cellSize - 0.01f;
    hRayPos.x = (start.y - hRayPos.y) * htan + start.x;
    offset.y = -cellSize;
    offset.x = -offset.y * htan;
  } else {
    hdof = MAX_RAYCAST_DEPTH;
  }
  for (; hdof < MAX_RAYCAST_DEPTH; hdof++) {
    int mapX = (int)(hRayPos.x / cellSize);
    int mapY = (int)(hRayPos.y / cellSize);
    if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX] != ' ') {
      hit = true;
      hdist = std::sqrt((hRayPos.x - start.x) * (hRayPos.x - start.x) +
                        (hRayPos.y - start.y) * (hRayPos.y - start.y));
      break;
    }
    hRayPos += offset;
  }
  return Ray{hdist < vdist ? hRayPos : vRayPos, std::min(hdist, vdist), hit, vdist < hdist};
}
