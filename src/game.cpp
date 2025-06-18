#include "game.hpp"

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

bool Game::run() { return init(); }

void Game::cleanup() {
  mWindow.destroy();
  SDL_Quit();
}

Game::~Game() { cleanup(); }
