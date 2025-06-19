#include "config.hpp"
#include "renderer.hpp"

class Food {
public:
  void draw(Renderer &) const;
  void respawn();

private:
  SDL_FRect mBody{0, 0, GameConfig::GridCellSize, GameConfig::GridCellSize};
};
