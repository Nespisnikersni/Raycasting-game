#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "player.h"

class Renderer{
  public:
    void drawRays(sf::RenderTarget &target,const Player &player);
  private:
};
