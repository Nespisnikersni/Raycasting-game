
#include "raycast.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "map.h"
#include "renderer.h"

constexpr float PI = 3.141592653589793f;
constexpr float PLAYER_FOV = 60.0f;
constexpr size_t MAX_RAYCAST_DEPTH = 64;
constexpr int NUM_RAYS = 1200;
constexpr float COLUMN_WIDTH = SCREEN_W / (float)NUM_RAYS;

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

    if (std::sin(angle) > 0.001f) {
        hRayPos.y = std::floor(start.y / cellSize) * cellSize + cellSize;
        hRayPos.x = (start.y - hRayPos.y) * htan + start.x;
        offset.y = cellSize;
        offset.x = -offset.y * htan;
    } else if (std::sin(angle) < -0.001f) {
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

    bool isVertical = false;
    
    return Ray{vRayPos, std::min(hdist, vdist), hit, isVertical};
}
