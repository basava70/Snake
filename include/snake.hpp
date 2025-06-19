#pragma once

#include "config.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <vector>

class Snake {
public:
  Snake(float x, float y, float width = GameConfig::GridCellSize,
        float height = GameConfig::GridCellSize);
  void grow();
  void draw(Renderer &) const;

  void setDirection(float, float);
  void update(float);

private:
  SDL_Color mColor{0, 255, 0, 255};
  std::vector<SDL_FRect> mBody;
  SDL_FPoint mVelocity{1.0f * GameConfig::SnakeSpeed,
                       0.0f * GameConfig::SnakeSpeed};
};
