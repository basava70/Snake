#include "snake.hpp"

Snake::Snake(float x, float y, float width, float height) {
  mBody.push_back({x, y, width, height});
}

void Snake::draw(Renderer &renderer) const {
  for (auto const &rect : mBody) {
    renderer.drawRect(rect, mColor);
  }
}
