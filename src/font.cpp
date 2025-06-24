#include "font.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <print>

bool Font::init() {
  if (!TTF_Init()) {
    std::println("Error initializing TTF: {}", SDL_GetError());
    return false;
  }

  mFont = TTF_OpenFont("fonts/MapleMono-NF-Regular", 12);
  if (!mFont) {
    std::print("Error unable to locate font: {}", SDL_GetError());
    return false;
  }
  return true;
}

Font::~Font() {
  if (!mFont)
    TTF_CloseFont(mFont);
  TTF_Quit();
}
