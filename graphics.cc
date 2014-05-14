#include <ncurses.h>
#include "graphics.hh"

void Graphics::run() {
    initscr();
    printw("Hello World");
    refresh();
    getch();
    endwin();
}
