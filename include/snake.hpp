#pragma once

#include "config.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <deque>
#include <vector>

struct PathTrails {
  SDL_FPoint position{0.0f, 0.0f};
};

class Snake {
public:
  Snake(Renderer &);
  void draw() const;
  void initTexture(char const *, char const *);
  void setDirection(float, float);
  void update(float);
  SDL_FRect getHead() const;
  void setHead(SDL_FRect const &);
  void grow();

private:
  void moveHead(float);
  void addSegment();
  void wrapSegment(SDL_FRect &);
  bool mShouldGrow = false;
  bool mRevertHeadBack = false;
  void moveSegment(int, float);
  SDL_Color mColor{0, 255, 0, 255};
  std::vector<SDL_FRect> mBody;
  std::deque<PathTrails> mTrail;
  constexpr static int mSpeed{GameConfig::SnakeSpeed};
  constexpr static int mSegmentSize{GameConfig::SnakeSegmentSize};
  constexpr static int mHeadSize{GameConfig::SnakeHeadSize};
  constexpr static int mSegmentsPerBody = 1;
  SDL_FPoint mDirection{1.0f, 0.0f};
  Renderer &mRenderer;
  SDL_Texture *mHeadTexture{nullptr};
  SDL_Texture *mBodyTexture{nullptr};
};
