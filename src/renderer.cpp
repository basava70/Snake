#include "renderer.hpp"

bool Renderer::init(SDL_Window *window) {
    mRenderer = SDL_CreateRenderer(window, 0);
    if (!mRenderer) {
        SDL_Log("Error creating Renderer: %s", SDL_GetError());
        return false;
    }
    return true;
}

Renderer::~Renderer() {
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        SDL_Log("Destroying Renderer");
    }
}
