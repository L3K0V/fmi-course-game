#include "game.hh"

void Game::run() {
	graphics->start();
	while(!flag_quit) {
		handle_input();
		graphics->render();
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
	while(SDL_PollEvent(&event_) != 0) {
		if(event_.type == SDL_QUIT) {
			flag_quit = true;
		} else if (event_.type == SDL_KEYDOWN){
			switch(event_.key.keysym.sym) {
				//Navigation
				case SDLK_UP: case SDLK_w:
				
				break;
				case SDLK_DOWN: case SDLK_s:
				
				break;
				case SDLK_LEFT: case SDLK_a:
				
				break;
				case SDLK_RIGHT: case SDLK_d:
				
				break;
				// Inventory
				case SDLK_i:
				
				break;
				//Equip/Use
				case SDLK_u:
				
				break;
				default:
				
				break;
			}
		}
	}
}
