#include "snake.hpp"
#include "config.hpp"
#include "renderer.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <cmath>
#include <print>

// TODO:
/* Have to add direction to PathTrails so we get very smooth
 * movement.
 */

Snake::Snake(Renderer &renderer) : mRenderer(renderer) {
  mBody.emplace_back(SDL_FRect{GameConfig::LogicalWidth / 2.0f,
                               GameConfig::LogicalHeight / 2.0f, mHeadSize,
                               mHeadSize});
}

void Snake::initTexture(char const *head_path, char const *body_path) {
  mHeadTexture = mRenderer.createTextureFromImage(head_path);
  if (!mHeadTexture) {
    std::println("Error loading snake head image: {}", SDL_GetError());
    return;
  }
  mBodyTexture = mRenderer.createTextureFromImage(body_path);
  if (!mBodyTexture) {
    std::println("Error loading snake body image: {}", SDL_GetError());
    return;
  }
}

void Snake::draw() const {
  mRenderer.drawTexture(mHeadTexture, mBody[0]);
  for (int segmentId = 1; segmentId < mBody.size(); segmentId++) {
    mRenderer.drawTexture(mBodyTexture, mBody[segmentId]);
  }
}

void Snake::setDirection(float dx, float dy) {
  mDirection.x = dx;
  mDirection.y = dy;
}

SDL_FRect Snake::getHead() const { return mBody.front(); }

void Snake::grow() { mShouldGrow = true; }

void Snake::wrapSegment(SDL_FRect &segment) {
  float &x = segment.x;
  float &y = segment.y;
  float w = segment.w;
  float h = segment.h;
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
  mBody[0].x += mDirection.x * mSpeed * dt;
  mBody[0].y += mDirection.y * mSpeed * dt;
  wrapSegment(mBody[0]);
  mTrail.emplace_front(SDL_FPoint{mBody[0].x, mBody[0].y});
}

void Snake::moveSegment(int segmentId, float dt) {
  SDL_FRect &segment = mBody[segmentId];
  // not checking for correctness
  segment.x = mTrail[segmentId * mSegmentSize].position.x;
  segment.y = mTrail[segmentId * mSegmentSize].position.y;
}

void Snake::addSegment() {
  SDL_FRect tail;
  SDL_FPoint direction = mDirection;

  if (mBody.size() >= 2) {
    SDL_FRect last = mBody.back();
    SDL_FRect secondLast = mBody[mBody.size() - 2];
    SDL_FPoint direction{last.x - secondLast.x, last.y - secondLast.y};

    // Normalize direction
    float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.0f) {
      direction.x /= length;
      direction.y /= length;
    }
  }
  tail.x += direction.x * mSegmentSize;
  tail.y += direction.y * mSegmentSize;
  tail.w = mSegmentSize;
  tail.h = mSegmentSize;
  mBody.push_back(tail);
}

void Snake::update(float dt) {
  moveHead(dt);
  for (int i = 1; i < mBody.size(); i++)
    moveSegment(i, dt);

  if (mShouldGrow) {
    for (int i = 0; i < mSegmentsPerBody; i++)
      addSegment();
    mShouldGrow = false;
  }
}
