#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <ncurses.h>

const int FIELD_H = 21;
const int FIELD_W = 21;
const int STATUS_H = 3;

class Game;

class Graphics {
    private:
        WINDOW *field_;
        WINDOW *status_;
        WINDOW *inventory_;

        Game &game_;

        int screen_x, screen_y;
        int inventory_h, inventory_w;

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
        void run();
        void stop();
        void render();
};

#endif // __GRAPHICS_H__
