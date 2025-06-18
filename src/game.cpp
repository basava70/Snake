#include "game.hpp"
#include "input_handler.hpp"

Game::Game(char const *title, int width, int height, SDL_WindowFlags flags)
    : mTitle(title), mWidth(width), mHeight(height), mFlags(flags) {}

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
  }

  for (auto &command : mInputHandler.triggeredCommands()) {
    command->execute();
  }
}
void Game::update() {}
void Game::generateOutput() {
  SDL_Color color_blue{0, 0, 255, 255};
  mRenderer.clear(color_blue);
  mRenderer.present();
}

bool Game::run() {
  if (!init())
    return false;
  mIsRunning = true;
  while (mIsRunning) {
    processInput();
    update();
    generateOutput();
  }

  return true;
}

void Game::cleanup() {
  mWindow.destroy();
  SDL_Quit();
}

Game::~Game() { cleanup(); }
