#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

class Font {
public:
  bool init();
  ~Font();

private:
  TTF_Font *mFont{nullptr};
};
