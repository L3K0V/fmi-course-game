#include  <unistd.h>

#include "graphics.hh"
#include "level.hh"
#include "game.hh"

void Graphics::start() {
    init();
}

void Graphics::stop() {
	// Some stuff before destroy graphics.
	is_running = false;
	cleanup();
}

void Graphics::render() {
    handle_resize();
    render_ui_borders(field_);
    render_ui_borders(inventory_);
    render_ui_borders(status_);
    render_ui();
    render_level();
	update_panels();
	
	printw("Hello from panel maybe?!");
	doupdate();
}

// One-time initialization stuff
void Graphics::init() {
    initscr();
    curs_set(false);
    getmaxyx(stdscr, screen_y, screen_x);

    start_color();

    field_ = newwin(screen_y - STATUS_H, screen_x / 2, 0, 0);
    inventory_ = newwin(screen_y - STATUS_H, screen_x / 2, 0, screen_x / 2);
    status_ = newwin(STATUS_H, screen_x, screen_y - STATUS_H, 0);
	debug_ = new_panel(inventory_);
	
	is_running = true;
}

void Graphics::cleanup() {
    delwin(field_);
    delwin(status_);
    delwin(inventory_);
    endwin();
}

void Graphics::exit_ncurses_for_a_while() {
	def_prog_mode();
	endwin();
}
void Graphics::return_to_ncurses() {
	reset_prog_mode();
	refresh();
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
    mvwprintw(field_, 1, 1, "");
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
    int scr_w, scr_h;
    float real_w, real_h;

    Level &level = game_.get_level();

    init_pair(1, COLOR_RED, COLOR_BLACK);

    // Field window size
    getmaxyx(field_, scr_h, scr_w);

    // Ratio between window and actual level size
    real_w = level.get_width() / float(scr_w);
    real_h = level.get_height() / float(scr_h);

    int width, height;

    for(height = 1; height < scr_h-1; ++height) {
        for(width = 1; width < scr_w-1; ++width) {
            char cell = level.get_cell(float(width) * real_w,float(height)* real_h);
            if (cell == '$') {
                attron(COLOR_PAIR(1));
            } else {
                attroff(COLOR_PAIR(1));
            }
            mvwprintw(field_, height, width, &cell);
        }
    }
}
