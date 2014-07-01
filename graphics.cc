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
	SDL_UpdateWindowSurface( window_ );
	
	//Clear screen
    SDL_RenderClear( renderer_ );

    //Update screen
	SDL_RenderPresent( renderer_ );
}

// One-time initialization stuff
int Graphics::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Cannot initialize SDL, because of error = " << SDL_GetError() << std::endl;
		return -1;
	} else {
		window_ = SDL_CreateWindow( "fmi-course-game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		
		if(window_ == NULL) {
			std::cout << "Cannot create SDL Window, because of error = " << SDL_GetError() << std::endl;
			return -1;
		} else {
            renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED );
            if( renderer_ == NULL ) {
				std::cout << "Cannot create SDL Render, because of error = " << SDL_GetError() << std::endl;
                return -1;
            } else {
                SDL_SetRenderDrawColor( renderer_, 0xFF, 0xFF, 0xFF, 0xFF );

            }
			
			surface_ = SDL_GetWindowSurface(window_);
		}
	}
	return 1;
}

void Graphics::cleanup() {
	SDL_DestroyRenderer( renderer_ );
    SDL_DestroyWindow( window_ );
	
	window_ = NULL;
	renderer_ = NULL;
	
    SDL_Quit();
}

/* void Graphics::render_level() {
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
*/
