#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "enemy.hh"
#include "utilities.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace game_utilities;

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
class Level {
private:
	char **data;
	int width;
	int height;
	
	vector<Enemy> enemies_;
	
	Enemy& generate_enemy(char type, int x, int y) const;
public:
	Level(const string);
	~Level();

	int get_width() const { return width;}
	int get_height() const { return height;}
	char get_cell(int x, int y) const {
        return data[y][x];
    }
	void print_level();
};

#endif //LEVEL_H
