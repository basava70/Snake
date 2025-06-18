#include "renderer.hpp"
#include "window.hpp"

class Game {
    public:
        Game(char const *title, int width = 1200, int height = 1000,
             SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE);
        bool run();
        void cleanup();
        ~Game();

    private:
        bool init();
        Window mWindow;
        Renderer mRenderer;
        char const *mTitle{nullptr};
        int mWidth = 1200;
        int mHeight = 800;
        SDL_WindowFlags mFlags = SDL_WINDOW_RESIZABLE;
};
