#include "window.hpp"

bool Window::init(char const *title, int height, int width,
                  SDL_WindowFlags flags) {
  mWindow = SDL_CreateWindow(title, width, height, flags);
  if (!mWindow) {
    SDL_Log("Error creating window: %s", SDL_GetError());
    return false;
  }
  return true;
}
void Window::destroy() {
  if (mWindow) {
    SDL_Log("Destroying SDL_Window");
    SDL_DestroyWindow(mWindow);
  }
  mWindow = nullptr;
}

Window::~Window() { destroy(); }
