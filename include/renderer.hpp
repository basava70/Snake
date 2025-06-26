#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

class Renderer {
public:
  bool init(SDL_Window *window);
  void clear(SDL_Color);
  void present();
  void drawRect(SDL_FRect const &, SDL_Color);
  void drawTexture(SDL_Texture *texture, SDL_FRect const &dst);
  void drawTexture(SDL_Texture *texture);
  SDL_Texture *createTextureFromImage(const char *) const;
  SDL_Texture *createTextureFromSurface(SDL_Surface *) const;
  ~Renderer();

private:
  SDL_Renderer *mRenderer{nullptr};
};
