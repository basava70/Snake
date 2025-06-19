#include "food.hpp"
#include "config.hpp"
#include <cstdlib>

void Food::respawn() {
  int numColumns = GameConfig::LogicalWidth / GameConfig::GridCellSize;
  int numRows = GameConfig::LogicalHeight / GameConfig::GridCellSize;

  int gridX = rand() % numColumns;
  int gridY = rand() % numRows;

  mBody.x = static_cast<float>(gridX * GameConfig::GridCellSize);
  mBody.y = static_cast<float>(gridY * GameConfig::GridCellSize);
}

void Food::draw(Renderer &renderer) const {
  SDL_Color color{255, 0, 0, 255};
  renderer.drawRect(mBody, color);
}
