#include "config.hpp"
#include "renderer.hpp"
#include <random>

class Food {
public:
  void draw(Renderer &) const;
  void respawn();
  SDL_FRect getHead() const;

private:
  SDL_FRect mBody{0, 0, GameConfig::FoodSize, GameConfig::FoodSize};
  std::mt19937 mRng{std::random_device{}()};
  std::uniform_real_distribution<float> mDistX{0.0f, GameConfig::LogicalWidth -
                                                         GameConfig::FoodSize};
  std::uniform_real_distribution<float> mDistY{0.0f, GameConfig::LogicalHeight -
                                                         GameConfig::FoodSize};
};
