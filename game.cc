#include "game.hh"

void Game::run() {
    graphics->run();
}

Level& Game::get_level() const {
    return *level_;
}

int Game::load_level(const string name) {
    level_ = new Level(name);
    return 0;
}
