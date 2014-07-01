#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <ncurses.h>
#include <panel.h>

const int FIELD_H = 21;
const int FIELD_W = 21;
const int STATUS_H = 3;

class Game;

class Graphics {
    private:
        WINDOW *field_;
        WINDOW *status_;
        WINDOW *inventory_;
		
		PANEL *debug_;

        Game &game_;

        int screen_x, screen_y;
        int inventory_h, inventory_w;
		bool is_running = false;

        void handle_resize();
        void render_level();
        void render_ui_borders(WINDOW *window);
        void render_ui();
        void init();
        void cleanup();
    public:
        Graphics(Game &game)
        : game_(game) {
            init();
        }

        void update();
        void start();
        void stop();
        void render();
		void exit_ncurses_for_a_while();
		void return_to_ncurses();
};

#endif // __GRAPHICS_H__
