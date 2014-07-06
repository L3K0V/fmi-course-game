#include  <unistd.h>

#include "graphics.hh"
#include "level.hh"
#include "game.hh"

void Graphics::start() {
    init();
}

void Graphics::stop() {
	// Some stuff before destroy graphics.
	cleanup();
}

void Graphics::render() {	
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	
	//Clear screen
    SDL_RenderClear( renderer_ );
	
	render_field();
	
	if(popup_active) 
		render_popup();
	
	if(inventory_active)
		render_inventory();
	
    //Update screen
	SDL_RenderPresent( renderer_ );
}

void Graphics::render_inventory() {
	
	if(SDL_SetRenderTarget(renderer_, inventory_) < 0) {
		std::cerr << "Cannot change renderer texture, because of error = " << SDL_GetError() << std::endl;
		return;
	}
	
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	SDL_RenderClear(renderer_);
	
	SDL_Rect inventory_border = {0, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 10};
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer_, &inventory_border);
	
	if(SDL_SetRenderTarget(renderer_, NULL) < 0) {
		std::cerr << "Cannot change renderer texture, because of error = " << SDL_GetError() << std::endl;
		return;
	}
	
	SDL_Rect bounds = {SCREEN_WIDTH / 2 - SCREEN_WIDTH / 6, 10, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 10};
	SDL_RenderCopy(renderer_, inventory_, NULL, &bounds);
}

void Graphics::render_field() {
	
	if(SDL_SetRenderTarget(renderer_, field_) < 0) {
		std::cerr << "Cannot change renderer texture, because of error = " << SDL_GetError() << std::endl;
		return;
	}
	
	Level &level = game_.get_level();
	
	int width = level.get_width();
	int height = level.get_height();
	
	int x, y, pos_x, pos_y;
	
	pos_x = SCREEN_WIDTH / 2 - SCREEN_WIDTH / 3;
	pos_y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3;
	
	int size = width > height ? ((SCREEN_WIDTH - 2 * pos_x) / width) : ((SCREEN_HEIGHT - 2 * pos_y) / height);
	
	SDL_Rect cell = {pos_x, pos_y, size, size};
	
	// Clear
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_ );
	
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			char ch = level.get_cell(x, y);
			
			switch(ch) {
				case ' ':
					SDL_SetRenderDrawColor(renderer_, 20, 160, 45, 255);
					SDL_RenderDrawRect(renderer_, &cell);
				break;
				// PATH
				case '-':
					SDL_SetRenderDrawColor(renderer_, 30, 100, 180, 255);
					SDL_RenderDrawRect(renderer_, &cell);
				break;
				// SOLID
				case game_level::SOLID: case game_level::TREE: case game_level::WALL:
					SDL_SetRenderDrawColor(renderer_, 84, 84, 84, 255);
					SDL_RenderDrawRect(renderer_, &cell);
				break;
				case game_level::MONSTER: {
					SDL_SetRenderDrawColor(renderer_, 20, 160, 45, 255);
					SDL_RenderDrawRect(renderer_, &cell);
					SDL_SetRenderDrawColor(renderer_, 170, 20, 5, 255);
				
					SDL_Rect enemy = {cell.x + size / 4, cell.y + size / 4, size / 2, size / 2};
					SDL_RenderDrawRect(renderer_, &enemy);
				} break;
				case game_level::BOSS: {
					SDL_SetRenderDrawColor(renderer_, 170, 20, 5, 255);
					SDL_RenderDrawRect(renderer_, &cell);
					SDL_SetRenderDrawColor(renderer_, 170, 20, 5, 255);
				
					SDL_Rect enemy = {cell.x + size / 4, cell.y + size / 4, size / 2, size / 2};
					SDL_RenderDrawRect(renderer_, &enemy);
				} break;
				case game_level::PLAYER: {
					SDL_SetRenderDrawColor(renderer_, 30, 100, 180, 255);
					SDL_RenderDrawRect(renderer_, &cell);
					SDL_SetRenderDrawColor(renderer_, 30, 100, 180, 255);
			
					SDL_Rect player = {cell.x + size / 4, cell.y + size / 4, size / 2, size / 2};
					SDL_RenderDrawRect(renderer_, &player);
				} break;
				case game_level::CHEST: {
					SDL_SetRenderDrawColor(renderer_, 160, 65, 160, 255);
					SDL_RenderDrawRect(renderer_, &cell);
					SDL_SetRenderDrawColor(renderer_, 160, 65, 160, 255);
			
					SDL_Rect player = {cell.x + size / 4, cell.y + size / 4, size / 2, size / 2};
					SDL_RenderDrawRect(renderer_, &player);
				} break;
				case game_level::EXIT: {
					SDL_SetRenderDrawColor(renderer_, 240, 210, 10, 255);
					SDL_RenderDrawRect(renderer_, &cell);
					SDL_SetRenderDrawColor(renderer_, 240, 210, 10, 255);
			
					SDL_Rect player = {cell.x + size / 4, cell.y + size / 4, size / 2, size / 2};
					SDL_RenderDrawRect(renderer_, &player);
				} break;
				default: 
					SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
					SDL_RenderDrawRect(renderer_, &cell);
				break;
			}

			cell.x += size;
		}
		cell.y += size;
		cell.x -= size * width;
	}
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	
	if(SDL_SetRenderTarget(renderer_, NULL) < 0) {
		std::cerr << "Cannot change renderer texture, because of error = " << SDL_GetError() << std::endl;
		return;
	}
	
	SDL_RenderCopy(renderer_, field_, NULL, NULL);
}

void Graphics::render_popup() {
	if(SDL_SetRenderTarget(renderer_, status_popup_) < 0) {
		std::cerr << "Cannot change renderer texture, because of error = " << SDL_GetError() << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
	SDL_RenderClear(renderer_);

	SDL_Rect popup_border = {0, 0, 150, 100};
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer_, &popup_border);

	if (game_.get_player().get_x() == s_popup_x && game_.get_player().get_y() == s_popup_y) {
		render_text("Health points: " + std::to_string(game_.get_player().get_hp()), {0,0,0,255}, 18);
		render_text("Armor points: " + std::to_string(game_.get_player().get_armor()), {0,0,0,255}, 36);
		render_text("Damage points: " + std::to_string(game_.get_player().get_dmg()), {0,0,0,255}, 52);
	} else {
		Enemy enemy = game_.get_enemy(s_popup_x, s_popup_y);
	
		render_text("Name: " + enemy.get_name(), {0,0,0,255}, 0);
		render_text("Health points: " + std::to_string(enemy.get_hp()), {0,0,0,255}, 18);
		render_text("Armor points: " + std::to_string(enemy.get_armor()), {0,0,0,255}, 36);
		render_text("Damage points: " + std::to_string(enemy.get_dmg()), {0,0,0,255}, 52);
	}
	
	if(SDL_SetRenderTarget(renderer_, NULL) < 0) {
		std::cerr << "Cannot change renderer texture, because of error = " << SDL_GetError() << std::endl;
		return;
	}

	SDL_Rect bounds = {m_popup_x + 10, m_popup_y + 10, 150, 100};
	SDL_RenderCopy(renderer_, status_popup_, NULL, &bounds);
}

void Graphics::render_text(const std::string& text, SDL_Color color, int offsetY) {
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(),  color);
	
	if(surface == NULL) {
		std::cout << SDL_GetError() << std::endl;
	}
	
	SDL_Texture *font = SDL_CreateTextureFromSurface(renderer_, surface);
	
	SDL_Rect rect = {0,offsetY, 120,18};
	
	SDL_RenderCopy(renderer_, font, NULL, &rect);
	SDL_DestroyTexture(font);
	SDL_FreeSurface(surface);
}

void Graphics::handle_popup(int m_x, int m_y) {
	Level &level = game_.get_level();
	
	int width = level.get_width();
	int height = level.get_height();
	
	int x, y, pos_x, pos_y;
	
	pos_x = SCREEN_WIDTH / 2 - SCREEN_WIDTH / 3;
	pos_y = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 3;
	
	int size = width > height ? ((SCREEN_WIDTH - 2 * pos_x) / width) : ((SCREEN_HEIGHT - 2 * pos_y) / height);
	
	SDL_Rect cell = {pos_x, pos_y, size, size};
	
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if ((m_x >= cell.x && m_x < cell.x + cell.w)
				&& (m_y >= cell.y && m_y < cell.y + cell.h)) {
					// DEBUG std::cout << "selected cell [" << x << ";" << y << "]" << std::endl;
					
					if(level.get_cell(x, y) == game_level::MONSTER || level.get_cell(x, y) == game_level::BOSS || level.get_cell(x,y) == game_level::PLAYER) {
						popup_active = true;
						m_popup_x = m_x;
						m_popup_y = m_y;
						
						s_popup_x = x;
						s_popup_y = y;
					} else 
						popup_active = false;
					
					return;
				}
				cell.x += size;
		}
		cell.y += size;
		cell.x -= size * width;
	}
	
	popup_active = false;
}

// One-time initialization stuff
int Graphics::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Cannot initialize SDL, because of error = " << SDL_GetError() << std::endl;
		return -1;
	} else {
		
		if (TTF_Init() == -1) {
			return -1;
		} else {
			font = TTF_OpenFont("Helvetica.ttf", 16);
			
			if(font == NULL) {
				std::cerr << SDL_GetError() << std::endl;
			}
		}
		
		window_ = SDL_CreateWindow( "fmi-course-game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		
		if(window_ == NULL) {
			std::cerr << "Cannot create SDL Window, because of error = " << SDL_GetError() << std::endl;
			return -1;
		} else {
            renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED );
            if( renderer_ == NULL ) {
				std::cerr << "Cannot create SDL Render, because of error = " << SDL_GetError() << std::endl;
                return -1;
            }
			inventory_ = SDL_CreateTexture( renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 10);
			field_ = SDL_CreateTexture( renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
			status_popup_ = SDL_CreateTexture( renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 150, 100);
		}
	}
	return 1;
}

void Graphics::cleanup() {
	SDL_DestroyTexture( inventory_ );
	SDL_DestroyTexture( status_popup_ );
	SDL_DestroyTexture( field_ );
	SDL_DestroyRenderer( renderer_ );
    SDL_DestroyWindow( window_ );
	
	window_ = NULL;
	renderer_ = NULL;
	
	TTF_Quit();
    SDL_Quit();
}
