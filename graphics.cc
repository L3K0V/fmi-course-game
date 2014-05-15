#include  <unistd.h>

#include "graphics.hh"
#include "level.hh"
#include "game.hh"

void Graphics::run() {

    init();
    while(1) {
        handle_resize();
        render_ui_borders(field_);
        render_ui_borders(inventory_);
        render_ui_borders(status_);
        render_ui();
    }
    cleanup();
}

// One-time initialization stuff
void Graphics::init() {
    initscr();

    curs_set(false);
    getmaxyx(stdscr, screen_y, screen_x);

    field_ = newwin(screen_y - STATUS_H, screen_x / 2, 0, 0);
    inventory_ = newwin(screen_y - STATUS_H, screen_x / 2, 0, screen_x / 2);
    status_ = newwin(STATUS_H, screen_x, screen_y - STATUS_H, 0);
}

void Graphics::cleanup() {
    delwin(field_);
    delwin(status_);
    delwin(inventory_);
    endwin();
}

void Graphics::handle_resize() {
    int new_x, new_y;
    getmaxyx(stdscr, new_y, new_x);

    if (new_y != screen_y || new_x != screen_x) {
        screen_y = new_y;
        screen_x = new_x;

        wresize(field_, new_y - STATUS_H, new_x / 2);
        wresize(inventory_, new_y - STATUS_H, new_x / 2);
        wresize(status_, STATUS_H, new_x);
        mvwin(status_, new_y - STATUS_H, 0);
        mvwin(inventory_, 0, new_x / 2);

        wclear(stdscr);
        wclear(field_);
        wclear(inventory_);
        wclear(status_);
    }
}

void Graphics::render_ui() {
    mvwprintw(field_, 1, 1, "Board");
    mvwprintw(status_, 1, 1, "Status");
    mvwprintw(inventory_, 1, 1, "Inventory");

    wrefresh(field_);
    wrefresh(inventory_);
    wrefresh(status_);
}

void Graphics::render_ui_borders(WINDOW *window) {
    int elm, x, y;

    getmaxyx(window, y, x);

    // 4 Corners
    mvwprintw(window, 0, 0, "+");
    mvwprintw(window, y - 1, 0, "+");
    mvwprintw(window, 0, x - 1, "+");
    mvwprintw(window, y - 1, x - 1, "+");

    // sides
    for (elm = 1; elm < (y - 1); elm++) {
        mvwprintw(window, elm, 0, "|");
        mvwprintw(window, elm, x - 1, "|");
    }

    // top and bottom
    for (elm = 1; elm < (x - 1); elm++) {
        mvwprintw(window, 0, elm, "-");
        mvwprintw(window, y - 1, elm, "-");
    }
}

void Graphics::render_level() {
    Level &level = game_.get_level();
    int width, height;
    for(height = 0; height < level.get_height(); height++) {
        for(width = 0; width < level.get_width(); width++) {
            addch(level.get_cell(width, height));
        }
        addch('\n');
    }
}
