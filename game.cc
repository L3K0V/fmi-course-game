#include "game.hh"

void Game::run() {
	graphics->start();
	while(!flag_quit) {
		handle_input();
		graphics->render();
	}
    graphics->stop();
}

void Game::load() {
	loader_->load_level_entries();
	level_ = &loader_->load_next_level();
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
	
	switch(level_->get_cell(player_->get_x(), player_->get_y())) {
		case game_level::EXIT:
			level_ = &loader_->load_next_level();
			level_->set_player_position(player_);
		break;
		case game_level::MONSTER: case game_level::BOSS: {
			fight();
		} default:
			level_->change_player_position(player_, last_x, last_y);
		break;
	}
}

int Game::fight() {
	Enemy enemy = get_enemy(player_->get_x(), player_->get_y());
	
	
	std::cout << "Fight between: player and " << enemy.get_name() << " started!" << endl; 
	
	
	while(player_->get_hp() > 0 || enemy.get_hp() > 0) {
		if (game_utilities::random(0, 2) != 1) {
			player_->take_damage(enemy.get_dmg());
		} else {
			enemy.take_damage(player_->deal_damage());
		}
		std::cout << "Player: " << player_->get_hp() << ", " << enemy.get_name() << " " << enemy.get_hp() << std::endl;
		
		if (player_->get_hp() <= 0) {
			flag_quit = true;
			return 0;
		} else if (enemy.get_hp() <= 0) {
			return 1;
		}
	}
}

Enemy& Game::get_enemy(int x, int y) {
	for(int e = 0; e < level_->get_enemies().size(); e++) {
		if(level_->get_enemies()[e].get_x() == x && 
			level_->get_enemies()[e].get_y() == y) {
				return level_->get_enemies()[e];
		}
	}
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
