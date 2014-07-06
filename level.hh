#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "enemy.hh"
#include "utilities.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/* Example map:
 *  TTTTTTTTTT
 *  TTT C TTTT
 *  TT M M TTT
 *  WWW B WWWW
 *  WS      SW
 *  W    @  KW
 *  WWW D WWWW
 *  
 *  Where:
 *      'T' - Tree
 *      'W' - Wall
 *      'D' - Door
 *      'S' - Stairs
 *      'C' - Chest
 *      'K' - Key
 *      'M' - Monster
 *      'B' - Boss
 *      '@' - Player
 *      '#' - Solid
 */
namespace game_level {
	const static char EXIT 		= 'E';
	const static char TREE 		= 'T';
	const static char WALL 		= 'W';
	const static char DOOR 		= 'D';
	const static char STAIRS 	= 'S';
	const static char CHEST 	= 'C';
	const static char KEY 		= 'K';
	const static char MONSTER 	= 'M';
	const static char BOSS 		= 'B';
	const static char PLAYER 	= '@';
	const static char SOLID		= '#';
}
class Player; 

class Level {
private:
	char **data;
	int width;
	int height;
	
	vector<Enemy> enemies_;

	Enemy& generate_enemy(char type, int x, int y);
public:
	Level(const string);
	~Level();

	int get_width() const { return width;}
	int get_height() const { return height;}
	char get_cell(int x, int y) {
        return data[y][x];
    }
    void set_cell(int x, int y, char c) {
        data[y][x] = c;
    }
	void print_level();
	vector<Enemy> get_enemies() { return enemies_; }
	void set_player_position(Player* player);
	void change_player_position(Player *player, int last_x, int last_y);
};

#endif //LEVEL_H
