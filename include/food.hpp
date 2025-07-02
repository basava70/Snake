#include "config.hpp"
#include "renderer.hpp"
#include <SDL3/SDL_rect.h>
#include <random>

class Food {
public:
  Food(Renderer &);
  void draw() const;
  void respawn();
  SDL_FRect getHead() const;
  void initTexture(char const *);
  SDL_FPoint getFoodPosition() const;

private:
  constexpr static int mFoodSize = GameConfig::FoodSize;
  SDL_FRect mBody{0, 0, mFoodSize, mFoodSize};
  std::mt19937 mRng{std::random_device{}()};
  std::uniform_real_distribution<float> mDistX{0.0f, GameConfig::LogicalWidth -
                                                         mFoodSize};
  std::uniform_real_distribution<float> mDistY{0.0f, GameConfig::LogicalHeight -
                                                         mFoodSize};
  Renderer &mRenderer;
  SDL_Texture *mTexture{nullptr};
};
