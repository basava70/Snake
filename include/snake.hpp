#pragma once

#include "config.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <vector>

struct SnakeSegment {
  SDL_FRect mRect{0.0f, 0.0f, GameConfig::GridCellSize,
                  GameConfig::GridCellSize};
  SDL_FPoint mDirection{1.0f, 0.0f};
};

class Snake {
public:
  Snake();
  Snake(float x, float y, float width = GameConfig::GridCellSize,
        float height = GameConfig::GridCellSize);
  void draw(Renderer &) const;

  void setDirection(float, float);
  void update(float);
  SDL_FRect getHead() const;
  void setHead(SDL_FRect const &);
  void grow();

private:
  bool mShouldGrow = false;
  bool mRevertHeadBack = false;
  void moveSegment(SnakeSegment &, float);
  SDL_Color mColor{0, 255, 0, 255};
  std::vector<SnakeSegment> mBody;
  SDL_FPoint mVelocity{1.0f * GameConfig::SnakeSpeed,
                       0.0f * GameConfig::SnakeSpeed};
};
