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
}

int Game::move(Position pos) {
	int last_x, last_y;
	
	last_x = player_->get_x();
	last_y = player_->get_y();
	
	switch(pos) {
		case Left: {
		
		int left = last_x - 1;
		
		if (left >= 0 && (level_->get_cell(left, last_y) != game_level::SOLID 
			&& level_->get_cell(left, last_y) != game_level::TREE 
			&& level_->get_cell(left, last_y) != game_level::WALL))
				player_->set_x(left);
		} break;
		
		case Right: {
		
		int right = last_x + 1;	
			
		if (right < level_->get_width() && (level_->get_cell(right, last_y) != game_level::SOLID 
			&& level_->get_cell(right, last_y) != game_level::TREE 
			&& level_->get_cell(right, last_y) != game_level::WALL))
				player_->set_x(right);
		} break;
		
		case Up: {
		
		int up = last_y - 1;
		
		if (up >= 0 && (level_->get_cell(last_x, up) != game_level::SOLID 
			&& level_->get_cell(last_x, up) != game_level::TREE 
			&& level_->get_cell(last_x, up) != game_level::WALL))
				player_->set_y(up);
		} break;
		
		case Down: {
		
		int down = last_y + 1;
		
		if (down < level_->get_height() && (level_->get_cell(last_x, down) != game_level::SOLID 
			&& level_->get_cell(last_x, down) != game_level::TREE 
			&& level_->get_cell(last_x, down) != game_level::WALL))
				player_->set_y(down);
		} break;
	}
	
	level_->change_player_position(player_, last_x, last_y);
}

void Game::handle_input() {
	while(SDL_PollEvent(&event_) != 0) {
		if(event_.type == SDL_QUIT) {
			flag_quit = true;
		} else if (event_.type == SDL_KEYDOWN){
			switch(event_.key.keysym.sym) {
				//Navigation
				case SDLK_UP: case SDLK_w:
					move(Up);
				break;
				case SDLK_DOWN: case SDLK_s:
					move(Down);
				break;
				case SDLK_LEFT: case SDLK_a:
					move(Left);
				break;
				case SDLK_RIGHT: case SDLK_d:
					move(Right);
				break;
				// Inventory
				case SDLK_i:
				graphics->switch_inventory_state();
				break;
				//Equip/Use
				case SDLK_u:
				
				break;
				
				case SDLK_q:
					flag_quit = true;
				break;
				default:
				
				break;
			}
		} else if (event_.type == SDL_MOUSEMOTION) {
		    int x, y;
            
            SDL_GetMouseState(&x, &y);
            graphics->handle_popup(x, y);
		}
	}
}
