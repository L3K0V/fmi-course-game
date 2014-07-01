#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Game;

class Graphics {
    private:
        Game &game_;
		SDL_Window *window_ = NULL;
		SDL_Surface *surface_ = NULL;
		
		SDL_Renderer *renderer_ = NULL;

        int init();
        void cleanup();
    public:
        Graphics(Game &game)
        : game_(game){}

        void update();
        void start();
        void stop();
        void render();
};

#endif // __GRAPHICS_H__
