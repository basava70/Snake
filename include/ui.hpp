#include "font.hpp"
#include "renderer.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <unordered_map>

class UI {
public:
  UI(Renderer &, Font const &, SDL_Color color = {0, 0, 0, 255});
  virtual void update(float) = 0;
  virtual void draw() const = 0;
  virtual ~UI() = 0;

protected:
  std::string mText;
  Font const &mFont;
  Renderer &mRenderer;
  SDL_FRect mRect;
  SDL_Texture *mTexture{nullptr};
  SDL_Color mColor;
};

// FPSCounter
class FpsCounter : public UI {
public:
  FpsCounter(Renderer &, Font const &, SDL_Color color = {0, 0, 0, 255});
  void update(float) override;
  void draw() const override;
  ~FpsCounter() override;

private:
  void updateTexture();
  int mFps{0};
  int mLastFPS{0};
  float mAccumulatedTime{0.0f};
  int mFrameCount{0};
  std::unordered_map<std::string, SDL_Texture *> mTextureCache;
};

// Title
class Title : public UI {
public:
  Title(Renderer &, Font const &, SDL_Color color = {0, 0, 0, 255});
  void update(float) override;
  void draw() const override;
  ~Title() override;
  void initTexture();
};

// Background
class BackGround : public UI {
public:
  BackGround(Renderer &, Font const &);
  void update(float) override;
  void draw() const override;
  ~BackGround() override;
  void initTexture(const char *);
};
