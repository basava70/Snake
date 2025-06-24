#include "font.hpp"
#include "renderer.hpp"
class FpsCounter {
public:
  FpsCounter(Renderer &, Font const &);
  void update(float dt);
  void draw();
  ~FpsCounter();

private:
  void updateTexture();
  Renderer &mRenderer;
  Font const &mFont;
  SDL_Texture *mTexture{nullptr};

  int mFps{0};
  float mAccumulatedTime{0.0f};
  int mFrameCount{0};
};
