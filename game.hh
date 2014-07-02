#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "player.hh"
#include "level.hh"
#include "enemy.hh"
#include "graphics.hh"

enum Position {
	Left, Right, Up, Down
};

class Game {
    private:
        Level *level_;
        Player *player_;
        Graphics *graphics;
		
		bool flag_quit = false;
		
		SDL_Event event_;
		
		int move(Position pos);
    public:
        Game() {
           graphics = new Graphics(*this);
        }

        ~Game() {
			graphics->stop();
            delete graphics;
        }

        int load_level(const string name);
        int attach_player(Player *player);

        Level& get_level() const;
        Player& get_player() const;

        void run();
        void update();
		void handle_input();
        void render();
        void exit();
};


#endif // __GAME_H__
