#include "snake.hpp"
#include "config.hpp"
// #include <print>

Snake::Snake() {
  mBody.emplace_back(SDL_FRect{GameConfig::LogicalWidth / 2.0f,
                               GameConfig::LogicalHeight / 2.0f,
                               GameConfig::GridCellSize,
                               GameConfig::GridCellSize},
                     SDL_FPoint{1.0f, 0.0f});
}

Snake::Snake(float x, float y, float width, float height) {
  mBody.push_back({x, y, width, height});
}

void Snake::draw(Renderer &renderer) const {
  for (auto const &segment : mBody) {
    renderer.drawRect(segment.mRect, mColor);
  }
}

void Snake::setDirection(float dx, float dy) {
  mBody[0].mDirection.x = dx;
  mBody[0].mDirection.y = dy;
  // mVelocity.x = dx * GameConfig::SnakeSpeed;
  // mVelocity.y = dy * GameConfig::SnakeSpeed;
}

SDL_FRect Snake::getHead() const { return mBody.front().mRect; }

// void Snake::setHead(SDL_FRect const &rect) {
//   mBody[0].x = rect.x;
//   mBody[0].y = rect.y;
// }

void Snake::grow() { mShouldGrow = true; }

void Snake::moveSegment(SnakeSegment &segment, float dt) {
  segment.mRect.x += segment.mDirection.x * GameConfig::SnakeSpeed * dt;
  segment.mRect.y += segment.mDirection.y * GameConfig::SnakeSpeed * dt;
}

void Snake::update(float dt) {
  SnakeSegment tail = mBody.back();

  for (std::size_t i = mBody.size() - 1; i > 0; --i) {
    mBody[i].mDirection = mBody[i - 1].mDirection;
  }

  for (auto &segment : mBody)
    moveSegment(segment, dt);

  SDL_FRect &head = mBody[0].mRect;
  int maxX = GameConfig::LogicalWidth;
  int maxY = GameConfig::LogicalHeight;
  int cell = GameConfig::GridCellSize;

  if (head.x >= maxX)
    head.x = 0;
  else if (head.x + cell <= 0)
    head.x = maxX - cell;

  if (head.y >= maxY)
    head.y = 0;
  else if (head.y + cell <= 0)
    head.y = maxY - cell;

  if (mShouldGrow) {
    int dx = (mVelocity.x > 0) - (mVelocity.x < 0);
    int dy = (mVelocity.y > 0) - (mVelocity.y < 0);
    tail.mRect.x -= dx * GameConfig::GridCellSize;
    tail.mRect.y -= dy * GameConfig::GridCellSize;
    mBody.push_back(tail);
    // std::println("Begin print of size: {}", mBody.size());
    // for (auto const &rect : mBody) {
    //   std::println("rect.x : {}, rect.y : {}", rect.x, rect.y);
    // }
    mShouldGrow = false;
  }
}
