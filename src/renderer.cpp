#include "renderer.hpp"

bool Renderer::init(SDL_Window *window) {
  mRenderer = SDL_CreateRenderer(window, 0);
  if (!mRenderer) {
    SDL_Log("Error creating Renderer: %s", SDL_GetError());
    return false;
  }
  return true;
}

void Renderer::clear(SDL_Color color) {
  SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(mRenderer);
}

void Renderer::present() { SDL_RenderPresent(mRenderer); }

Renderer::~Renderer() {
  if (mRenderer) {
    SDL_DestroyRenderer(mRenderer);
    SDL_Log("Destroying Renderer");
  }
}
