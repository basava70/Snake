#include "fps_counter.hpp"
#include "font.hpp"
#include "renderer.hpp"

FpsCounter::FpsCounter(Renderer &renderer, Font const &font)
    : mRenderer(renderer), mFont(font) {
  // I want to have sdl_surface and texture here
}

// TODO:
//  Use cache for textures
void FpsCounter::updateTexture() {}

void FpsCounter::update(float dt) {
  mAccumulatedTime += dt;
  mFrameCount++;

  if (mAccumulatedTime >= 1.0f) {
    mFps = mFrameCount / mAccumulatedTime;
    mAccumulatedTime = 0.0f;
    mFrameCount = 0;
    updateTexture();
  }
}
