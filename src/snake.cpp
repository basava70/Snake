#include "snake.hpp"
#include "config.hpp"
#include <SDL3/SDL_rect.h>
#include <cmath>

// TODO:
/* Have to add direction to PathTrails so we get very smooth
 * movement.
 */

Snake::Snake() {
  mBody.emplace_back(SDL_FRect{GameConfig::LogicalWidth / 2.0f,
                               GameConfig::LogicalHeight / 2.0f, mSegmentSize,
                               mSegmentSize});
}

void Snake::draw(Renderer &renderer) const {
  for (auto const &segment : mBody) {
    renderer.drawRect(segment.mRect, mColor);
  }
}

void Snake::setDirection(float dx, float dy) {
  mDirection.x = dx;
  mDirection.y = dy;
}

SDL_FRect Snake::getHead() const { return mBody.front().mRect; }

void Snake::grow() { mShouldGrow = true; }

void Snake::wrapSegment(SnakeSegment &segment) {
  float &x = segment.mRect.x;
  float &y = segment.mRect.y;
  float w = segment.mRect.w;
  float h = segment.mRect.h;
  int maxX = GameConfig::LogicalWidth;
  int maxY = GameConfig::LogicalHeight;

  if (x >= maxX)
    x = 0;
  else if (x + w <= 0)
    x = maxX - w;

  if (y >= maxY)
    y = 0;
  else if (y + h <= 0)
    y = maxY - h;
}

void Snake::moveHead(float dt) {
  mBody[0].mRect.x += mDirection.x * mSpeed * dt;
  mBody[0].mRect.y += mDirection.y * mSpeed * dt;
  wrapSegment(mBody[0]);
  mTrail.emplace_front(SDL_FPoint{mBody[0].mRect.x, mBody[0].mRect.y});
}

void Snake::moveSegment(int segmentId, float dt) {
  SnakeSegment &segment = mBody[segmentId];
  // not checking for correctness
  segment.mRect.x = mTrail[segmentId * mSegmentSize].position.x;
  segment.mRect.y = mTrail[segmentId * mSegmentSize].position.y;
}

void Snake::addSegment() {
  SnakeSegment tail;
  SDL_FPoint direction = mDirection;

  if (mBody.size() >= 2) {
    SDL_FRect last = mBody.back().mRect;
    SDL_FRect secondLast = mBody[mBody.size() - 2].mRect;
    SDL_FPoint direction{last.x - secondLast.x, last.y - secondLast.y};

    // Normalize direction
    float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.0f) {
      direction.x /= length;
      direction.y /= length;
    }
  }
  tail.mRect.x += direction.x * mSegmentSize;
  tail.mRect.y += direction.y * mSegmentSize;
  tail.mRect.w = mSegmentSize;
  tail.mRect.h = mSegmentSize;
  mBody.push_back(tail);
}

void Snake::update(float dt) {
  moveHead(dt);
  for (int i = 1; i < mBody.size(); i++)
    moveSegment(i, dt);

  if (mShouldGrow) {
    for (int i = 0; i < GameConfig::GridCellSize / mSegmentSize; i++)
      addSegment();
    mShouldGrow = false;
  }
}
