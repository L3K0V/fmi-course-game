#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "player.hh"
#include "level.hh"
#include "enemy.hh"

class Game {
    private:
        Level *level_;
        Player *player_;
        vector<Enemy> enemies_;
        //TODO: add graphics class
    public:
        int load_level(string name);
        int attach_player(const Player *player);

        Level* get_level() const;
        Player* get_player() const;
        vector<Enemy> get_enemies() const;

        void run();
        void update();
        void render();
        void exit();
}


#endif // __GAME_H__
