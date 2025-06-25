#pragma once
#include "font.hpp"
#include "food.hpp"
#include "fps_counter.hpp"
#include "input_handler.hpp"
#include "renderer.hpp"
#include "snake.hpp"
#include "window.hpp"
#include <SDL3/SDL_video.h>

class Game {
public:
  Game(char const *title, int width = 800, int height = 600,
       SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN);
  bool run();
  void cleanup();
  ~Game();

private:
  bool init();
  Window mWindow;
  Renderer mRenderer;
  Font mFont;

  void processInput();
  InputHandler mInputHandler;

  Snake mSnake;
  Food mFood;
  FpsCounter mFpsCounter;

  void update(float);
  void generateOutput();

  char const *mTitle{nullptr};
  int mWidth = 800;
  int mHeight = 600;
  SDL_WindowFlags mFlags = SDL_WINDOW_RESIZABLE;
  bool mIsRunning = false;
};
