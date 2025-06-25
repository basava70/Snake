#include "renderer.hpp"
#include "config.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

bool Renderer::init(SDL_Window *window) {
  mRenderer = SDL_CreateRenderer(window, 0);
  if (!mRenderer) {
    SDL_Log("Error creating Renderer: %s", SDL_GetError());
    return false;
  }
  SDL_SetRenderLogicalPresentation(mRenderer, GameConfig::LogicalWidth,
                                   GameConfig::LogicalHeight,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);
  return true;
}

void Renderer::clear(SDL_Color color) {
  SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(mRenderer);
}

void Renderer::present() { SDL_RenderPresent(mRenderer); }

void Renderer::drawRect(SDL_FRect const &rect, SDL_Color color) {
  SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(mRenderer, &rect);
}

void Renderer::drawTexture(SDL_Texture *texture, SDL_FRect const &dst) {
  SDL_RenderTexture(mRenderer, texture, 0, &dst);
}

SDL_Texture *Renderer::createTextureFromSurface(SDL_Surface *surface) const {
  return SDL_CreateTextureFromSurface(mRenderer, surface);
}

Renderer::~Renderer() {
  if (mRenderer) {
    SDL_DestroyRenderer(mRenderer);
    SDL_Log("Destroying Renderer");
  }
}
