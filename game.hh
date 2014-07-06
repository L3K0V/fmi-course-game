#ifndef __GAME_H__
#define __GAME_H__

#include "player.hh"
#include "enemy.hh"
#include "graphics.hh"
#include "level_loader.hh"

enum Position {
	Left, Right, Up, Down
};

class Game {
    private:
        Level 		*level_;
        Player 		*player_;
        Graphics 	*graphics;
		LevelLoader *loader_;
		
		bool flag_quit = false;
		
		SDL_Event event_;
		
		int move(Position pos);
		int fight();
    public:
        Game()
		:loader_(new LevelLoader()), graphics(new Graphics(*this))
		{}

        ~Game() {
			graphics->stop();
            delete graphics;
			delete loader_;
        }
		
		Level& get_level() const {return loader_->get_current_level();}
		
        int attach_player(Player *player);

        void run();
		void load();
        void update();
		void handle_input();
        void render();
        void exit();
};


#endif // __GAME_H__
