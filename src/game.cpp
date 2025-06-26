#include "game.hpp"
#include "config.hpp"
#include "input_handler.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_timer.h>
#include <chrono>
#include <thread>

Game::Game(char const *title, int width, int height, SDL_WindowFlags flags)
    : mWindowTitle(title), mWidth(width), mHeight(height), mFlags(flags),
      mSnake(), mFpsCounter(mRenderer, mFont), mTitle(mRenderer, mFont) {}

bool Game::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing SDL: %s", SDL_GetError());
    return false;
  }
  if (!mWindow.init(mWindowTitle, mWidth, mHeight, mFlags))
    return false;
  if (!mRenderer.init(mWindow.getWindow()))
    return false;
  if (!mFont.init()) {
    return false;
  }

  mTitle.update(0.0f);

  return true;
}

void Game::processInput() {
  mInputHandler.run();

  for (auto event : mInputHandler.triggeredEvents()) {
    if (event == InputEvents::Quit)
      mIsRunning = false;
    else if (event == InputEvents::WindowResize) {
      SDL_GetWindowSize(mWindow.getWindow(), &mWidth, &mHeight);
    };
  }

  for (auto &command : mInputHandler.triggeredCommands()) {
    command->execute(mSnake);
  }
}

void Game::update(float dt) {
  // collision
  SDL_FRect snakeHead = mSnake.getHead();
  SDL_FRect foodHead = mFood.getHead();
  if (SDL_HasRectIntersectionFloat(&snakeHead, &foodHead)) {
    mSnake.grow();
    mFood.respawn();
  }
  mSnake.update(dt);
  mFpsCounter.update(dt);
  // mTitle.update(dt);
}

void Game::generateOutput() {
  SDL_Color color{125, 125, 125, 255};
  mRenderer.clear(color);
  mSnake.draw(mRenderer);
  mFood.draw(mRenderer);
  mFpsCounter.draw();
  mTitle.draw();
  mRenderer.present();
}

bool Game::run() {
  if (!init())
    return false;

  constexpr std::chrono::duration<float> targetFrameDuration{
      1.0f / GameConfig::ExpectedFrameRate};
  auto lastTime = std::chrono::steady_clock::now();

  mFood.respawn();
  mIsRunning = true;

  while (mIsRunning) {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> dt = (now - lastTime); // deltatime

    if (dt < targetFrameDuration) {
      std::this_thread::sleep_until(lastTime + targetFrameDuration);
      continue;
    }
    lastTime = now;

    processInput();
    update(dt.count());
    generateOutput();
  }

  return true;
}

void Game::cleanup() { SDL_Quit(); }

Game::~Game() { cleanup(); }
