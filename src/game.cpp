#include "game.hpp"
#include "input_handler.hpp"
#include <cstdint>

Game::Game(char const *title, int width, int height, SDL_WindowFlags flags)
    : mTitle(title), mWidth(width), mHeight(height), mFlags(flags),
      mSnake(width / 2.0f, height / 2.0f) {}

bool Game::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing SDL: %s", SDL_GetError());
    return false;
  }
  if (!mWindow.init(mTitle, mWidth, mHeight, mFlags))
    return false;
  if (!mRenderer.init(mWindow.getWindow()))
    return false;

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

void Game::update(float dt) { mSnake.update(dt); }

void Game::generateOutput() {
  SDL_Color color{125, 125, 125, 255};
  mRenderer.clear(color);
  mSnake.draw(mRenderer);
  mFood.draw(mRenderer);
  mRenderer.present();
}

bool Game::run() {
  if (!init())
    return false;

  constexpr float targetFrameTime = 1.0f / 120.0f;
  uint64_t lastTime = SDL_GetPerformanceCounter();
  const auto freq = static_cast<float>(SDL_GetPerformanceFrequency());

  mFood.respawn();
  mIsRunning = true;
  while (mIsRunning) {

    uint64_t now = SDL_GetPerformanceCounter();
    float dt = (now - lastTime) / freq; // deltatime
    lastTime = now;

    processInput();
    update(dt);
    generateOutput();

    float frameTime = (SDL_GetPerformanceCounter() - now) / freq;
    float sleepTime = targetFrameTime - frameTime;

    if (sleepTime > 0.0f)
      SDL_Delay(static_cast<Uint32>(sleepTime * 1000));
  }

  return true;
}

void Game::cleanup() {
  mWindow.destroy();
  SDL_Quit();
}

Game::~Game() { cleanup(); }
