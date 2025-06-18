#pragma once

#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <vector>

class Snake {
public:
  Snake(float x, float y, float width = mSnakeRectSize,
        float height = mSnakeRectSize);
  void grow();
  void draw(Renderer &) const;

private:
  SDL_Color mColor{0, 255, 0, 255};
  static constexpr float mSnakeRectSize = 10;
  std::vector<SDL_FRect> mBody;
};
