#include "food.hpp"

void Food::respawn() {

  mBody.x = mDistX(mRng);
  mBody.y = mDistY(mRng);
}

SDL_FRect Food::getHead() const { return mBody; }

void Food::draw(Renderer &renderer) const {
  SDL_Color color{255, 0, 0, 255};
  renderer.drawRect(mBody, color);
}
