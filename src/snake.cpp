#include "snake.hpp"
#include "config.hpp"

Snake::Snake(float x, float y, float width, float height) {
  mBody.push_back({x, y, width, height});
}

void Snake::draw(Renderer &renderer) const {
  for (auto const &rect : mBody) {
    renderer.drawRect(rect, mColor);
  }
}

void Snake::setDirection(float dx, float dy) {
  mVelocity.x = dx * GameConfig::SnakeSpeed;
  mVelocity.y = dy * GameConfig::SnakeSpeed;
}

SDL_FRect Snake::getHead() const { return mBody.front(); }

void Snake::grow() { mShouldGrow = true; }

void Snake::update(float dt) {
  SDL_FRect tail = mBody.back();

  for (std::size_t i = mBody.size() - 1; i > 0; --i)
    mBody[i] = mBody[i - 1];

  mBody[0].x += mVelocity.x * dt;
  mBody[0].y += mVelocity.y * dt;

  SDL_FRect &head = mBody[0];
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
    SDL_Log("old: tail.x = %.3f, old tail.y = %.3f", tail.x, tail.y);
    SDL_Log("old: tail.w = %.3f, old tail.h = %.3f", tail.w, tail.h);
    tail.x -= dx * GameConfig::GridCellSize;
    tail.y -= dy * GameConfig::GridCellSize;
    mBody.push_back(tail);
    SDL_Log("GROW: tail.x = %.3f, tail.y = %.3f", tail.x, tail.y);
    SDL_Log("old: tail.w = %.3f, old tail.h = %.3f", tail.w, tail.h);
    SDL_Log("HEAD: head.x = %.3f, head.y = %.3f", mBody[0].x, mBody[0].y);
    SDL_Log("HEAD: head.w = %.3f, head.h = %.3f", mBody[0].w, mBody[0].h);
    mShouldGrow = false;
  }
}
