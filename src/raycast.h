#ifndef RAYCAST_H
#define RAYCAST_H 

#include <SFML/Graphics/RenderTarget.hpp>
#include "map.h"
struct Ray{
	sf::Vector2f hitPos;
	float distance;
	bool hit;
	bool isVerticale;
};
#endif //RAYCAST_H
