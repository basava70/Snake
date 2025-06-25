#include "font.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <print>

bool Font::init() {
  if (!TTF_Init()) {
    std::println("Error initializing TTF: {}", SDL_GetError());
    return false;
  }

  mFont = TTF_OpenFont("fonts/MapleMono-NF-Regular.ttf", 12);
  if (!mFont) {
    std::print("Error unable to locate font: {}", SDL_GetError());
    return false;
  }
  return true;
}

SDL_Surface *Font::createSurfaceBlended(std::string const &text,
                                        SDL_Color color) const {
  return TTF_RenderText_Blended(mFont, text.c_str(), 0, color);
}

Font::~Font() {
  if (!mFont)
    TTF_CloseFont(mFont);
  TTF_Quit();
}
