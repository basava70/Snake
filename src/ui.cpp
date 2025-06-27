#include "ui.hpp"
#include "config.hpp"
#include "renderer.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <print>

UI::UI(Renderer &renderer, Font const &font, SDL_Color color)
    : mRenderer(renderer), mFont(font), mColor(color) {}
UI::~UI() {
  if (mTexture) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }
}

FpsCounter::FpsCounter(Renderer &renderer, Font const &font)
    : UI(renderer, font) {
  mText = "FPS: " + std::to_string(mFps);
  // I want to have sdl_surface and texture here
}

// FpsCounter
void FpsCounter::updateTexture() {
  if (mLastFPS == mFps)
    return;

  mText = "FPS: " + std::to_string(mFps);

  auto it = mTextureCache.find(mText);
  if (it != mTextureCache.end()) {
    mTexture = it->second;
    return;
  }

  SDL_Surface *surface = mFont.createSurfaceBlended(mText, mColor);
  if (!surface) {
    std::println("Error creating surface in FpsCounter: {}", SDL_GetError());
    return;
  }
  mRect.w = static_cast<float>(surface->w);
  mRect.h = static_cast<float>(surface->h);
  mTexture = mRenderer.createTextureFromSurface(surface);
  SDL_DestroySurface(surface);
  if (!mTexture) {
    std::println("Error creating texture in FpsCounter: {}", SDL_GetError());
    return;
  }
  mTextureCache[mText] = mTexture;
}

void FpsCounter::update(float dt) {
  mAccumulatedTime += dt;
  mFrameCount++;

  if (mAccumulatedTime >= 1.0f) {
    mFps = mFrameCount / mAccumulatedTime;
    mAccumulatedTime = 0.0f;
    mFrameCount = 0;
    updateTexture();
    mLastFPS = mFps;
  }
}

void FpsCounter::draw() const {
  SDL_FRect finalRect = mRect;
  finalRect.x = GameConfig::LogicalWidth - mRect.w - 5.0f;
  finalRect.y = 5.0f;
  mRenderer.drawTexture(mTexture, finalRect);
}

// Title
Title::Title(Renderer &renderer, Font const &font) : UI(renderer, font) {
  mText = "Snake";
}

void Title::initTexture() {
  SDL_Surface *surface = mFont.createSurfaceBlended(mText, mColor);
  if (!surface) {
    std::println("Error creating surface in Title: {}", SDL_GetError());
    return;
  }
  mRect.w = static_cast<float>(surface->w);
  mRect.h = static_cast<float>(surface->h);
  mTexture = mRenderer.createTextureFromSurface(surface);
  SDL_DestroySurface(surface);
  if (!mTexture) {
    std::println("Error creating texture in Title: {}", SDL_GetError());
    return;
  }
}

void Title::update(float dt) {}

void Title::draw() const {
  SDL_FRect rect = mRect;
  rect.x = GameConfig::LogicalWidth / 2.0f - mRect.w / 2.0f;
  rect.y = 5.0f;
  mRenderer.drawTexture(mTexture, rect);
}

// BackGround
BackGround::BackGround(Renderer &renderer, Font const &font)
    : UI(renderer, font) {}

void BackGround::initTexture(const char *path) {
  mTexture = mRenderer.createTextureFromImage(path);
  if (!mTexture) {
    std::println("Error creating backgroung texture: {}", SDL_GetError());
    return;
  }
  SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);
}
void BackGround::update(float dt) {}

void BackGround::draw() const {
  const int tileSize = 512;

  int winW = GameConfig::LogicalWidth;
  int winH = GameConfig::LogicalHeight;

  for (int y = 0; y < winH; y += tileSize) {
    for (int x = 0; x < winW; x += tileSize) {
      SDL_FRect dst{static_cast<float>(x), static_cast<float>(y),
                    static_cast<float>(tileSize), static_cast<float>(tileSize)};
      mRenderer.drawTexture(mTexture, dst);
    }
  }
}
