#pragma once
#include <SDL3/SDL.h>
class Window {
public:
  bool init(char const *name, int height, int width, SDL_WindowFlags flags);
  void destroy();
  SDL_Window *getWindow() const { return mWindow; };
  ~Window();

private:
  SDL_Window *mWindow{nullptr};
};
