#pragma once
#include <SDL3/SDL.h>
class Window {
public:
  bool init(char const *name, int width, int height, SDL_WindowFlags flags);
  SDL_Window *getWindow() const;
  ~Window();

private:
  void destroy();
  SDL_Window *mWindow{nullptr};
};
