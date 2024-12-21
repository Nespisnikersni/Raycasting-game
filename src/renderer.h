#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>
#include "map.h"
#include "player.h"

constexpr float SCREEN_W = 1200.0;
constexpr float SCREEN_H = 600.0f;

class Renderer{
  public:
    void drawRays(sf::RenderTarget &target,const Player &player,const Map &map);
    void draw3dView(sf::RenderTarget &target,const Player &player,const Map &map);
  private:
};
#endif // RENDERER_H
