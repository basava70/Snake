#pragma once
#include "input_handler.hpp"
#include "renderer.hpp"
#include "snake.hpp"
#include "window.hpp"

class Game {
public:
  Game(char const *title, int width = 800, int height = 600,
       SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE);
  bool run();
  void cleanup();
  ~Game();

private:
  bool init();
  Window mWindow;
  Renderer mRenderer;

  void processInput();
  InputHandler mInputHandler;

  Snake mSnake;

  void update(float);
  void generateOutput();

  char const *mTitle{nullptr};
  int mWidth = 800;
  int mHeight = 600;
  SDL_WindowFlags mFlags = SDL_WINDOW_RESIZABLE;
  bool mIsRunning = false;
};
