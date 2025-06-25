#include "font.hpp"
#include "renderer.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <string>
class FpsCounter {
public:
  FpsCounter(Renderer &, Font const &);
  void update(float dt);
  void draw() const;
  ~FpsCounter();

private:
  void updateTexture();
  Renderer &mRenderer;
  Font const &mFont;
  SDL_Color mColor{0, 0, 0, 255};
  SDL_Texture *mTexture{nullptr};
  std::string mText;
  SDL_FRect mDstRect{};

  int mFps{0};
  int mLastFPS{0};
  float mAccumulatedTime{0.0f};
  int mFrameCount{0};
};
