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

void Snake::update(float dt) {
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
  ;
}
