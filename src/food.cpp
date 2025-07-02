#include "food.hpp"
#include "renderer.hpp"
#include <SDL3/SDL_rect.h>
#include <print>

Food::Food(Renderer &renderer) : mRenderer(renderer) {}

void Food::initTexture(char const *path) {
  mTexture = mRenderer.createTextureFromImage(path);
  if (!mTexture) {
    std::println("Error loading apple.png into texture: {}", SDL_GetError());
    return;
  }
}

void Food::respawn() {
  mBody.x = mDistX(mRng);
  mBody.y = mDistY(mRng);
}

SDL_FRect Food::getHead() const { return mBody; }
SDL_FPoint Food::getFoodPosition() const {
  return {mBody.x + mFoodSize / 2.0f, mBody.y + mFoodSize / 2.0f};
}

void Food::draw() const { mRenderer.drawTexture(mTexture, mBody); }
