#include "fps_counter.hpp"
#include "config.hpp"
#include "font.hpp"
#include "renderer.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <print>
#include <string>

FpsCounter::FpsCounter(Renderer &renderer, Font const &font)
    : mRenderer(renderer), mFont(font) {
  mText = "FPS: " + std::to_string(mFps);
  // I want to have sdl_surface and texture here
}

// TODO:
//  Use cache for textures
void FpsCounter::updateTexture() {
  if (mLastFPS == mFps)
    return;

  if (mTexture) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }

  mText = "FPS: " + std::to_string(mFps);

  SDL_Surface *surface = mFont.createSurfaceBlended(mText, mColor);
  if (!surface) {
    std::println("Error creating surface in FpsCounter: {}", SDL_GetError());
    return;
  }
  mDstRect.w = static_cast<float>(surface->w);
  mDstRect.h = static_cast<float>(surface->h);
  mTexture = mRenderer.createTextureFromSurface(surface);
  SDL_DestroySurface(surface);
  if (!mTexture) {
    std::println("Error creating texture in FpsCounter: {}", SDL_GetError());
    return;
  }
}

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

void FpsCounter::draw() const {
  SDL_FRect finalRect = mDstRect;
  finalRect.x = GameConfig::LogicalWidth - mDstRect.w - 5.0f;
  finalRect.y = 5.0f;
  mRenderer.drawTexture(mTexture, finalRect);
}

FpsCounter::~FpsCounter() {
  if (mTexture)
    SDL_DestroyTexture(mTexture);
}
