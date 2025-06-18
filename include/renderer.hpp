#include <SDL3/SDL.h>

class Renderer {
    public:

    bool init(SDL_Window* window);
    ~Renderer();
    private:
    SDL_Renderer *mRenderer{nullptr};

};
