#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Font {
public:
  bool init();
  SDL_Surface *createSurfaceBlended(std::string const &, SDL_Color) const;
  ~Font();

private:
  TTF_Font *mFont{nullptr};
};
