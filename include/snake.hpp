#pragma once

#include "config.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <deque>
#include <vector>

struct SnakeSegment {
  SDL_FRect mRect{0.0f, 0.0f, GameConfig::SnakeSegmentSize,
                  GameConfig::SnakeSegmentSize};
};

struct PathTrails {
  SDL_FPoint position{0.0f, 0.0f};
};

class Snake {
public:
  Snake();
  void draw(Renderer &) const;

  void setDirection(float, float);
  void update(float);
  SDL_FRect getHead() const;
  void setHead(SDL_FRect const &);
  void grow();

private:
  void moveHead(float);
  void addSegment();
  void wrapSegment(SnakeSegment &);
  bool mShouldGrow = false;
  bool mRevertHeadBack = false;
  void moveSegment(int, float);
  SDL_Color mColor{0, 255, 0, 255};
  std::vector<SnakeSegment> mBody;
  std::deque<PathTrails> mTrail;
  int static constexpr mSpeed{GameConfig::SnakeSpeed};
  int static constexpr mSegmentSize{GameConfig::SnakeSegmentSize};
  SDL_FPoint mDirection{1.0f, 0.0f};
};
