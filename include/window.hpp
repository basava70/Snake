#pragma once
#include <SDL3/SDL.h>
class Window {
public:
  bool init(char const *name, int width, int height, SDL_WindowFlags flags);
  void destroy();
  SDL_Window *getWindow() const;
  ~Window();

private:
  SDL_Window *mWindow{nullptr};
};
