#include "game.hh"

void Game::run() {
	is_running = true;
	graphics->start();
	while(is_running) {
		graphics->render();
		handle_input();
	}
    graphics->stop();
}

Level& Game::get_level() const {
    return *level_;
}

int Game::load_level(const string name) {
	if (level_ != NULL) {
		delete level_;
		level_ = NULL;
	}
    level_ = new Level(name);
	// TODO: map meta data!
    return 0;
}

int Game::attach_player(Player *player) {
    level_->set_player_position(player);
    player_ = player;
	
	// TODO: now we can draw player!
}

void Game::handle_input() {
	
}
