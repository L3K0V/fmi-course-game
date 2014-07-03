#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <string>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

using std::string;

class Game;

class Graphics {
    private:
        Game &game_;
		SDL_Window *window_ = NULL;
		SDL_Surface *surface_ = NULL;
		
		SDL_Texture *field_ = NULL;
		SDL_Texture *inventory_ = NULL;
		SDL_Texture *status_popup_ = NULL;
		
		SDL_Renderer *renderer_ = NULL;
		
		TTF_Font *font = NULL;
		
		bool inventory_active = false;

        int init();
        void cleanup();
		void render_field();
		void render_inventory();
		void render_popup();
		void render_text(const string&, SDL_Color);
    public:
        Graphics(Game &game)
        : game_(game){}

        void update();
        void start();
        void stop();
        void render();
		
		void switch_inventory_state() { inventory_active = !inventory_active; }
		bool is_inventory_active() { return inventory_active; }
		void handle_popup(int x, int y);
};

#endif // __GRAPHICS_H__
