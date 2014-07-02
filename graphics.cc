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
	
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			char ch = level.get_cell(x, y);
			
			switch(ch) {
				case ' ':
				SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
				break;
				case '#': case 'T': case 'W':
				SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
				break;
				default: 
				SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
				break;
			}
			
			SDL_RenderDrawRect(renderer_, &cell);
			
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
	
}

// One-time initialization stuff
int Graphics::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Cannot initialize SDL, because of error = " << SDL_GetError() << std::endl;
		return -1;
	} else {
		
		if (TTF_Init() == -1) {
			
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
			status_popup_ = SDL_CreateTexture( renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 70, 100);
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
	
    SDL_Quit();
}
