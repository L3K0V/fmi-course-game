#include "level.hh"
#include "player.hh"

#include <fstream>
#include <deque>
#include <iostream>

using namespace game_utilities;

/*
 * Buffer all level data to get level size, then
 * initialize level data array.
 */
Level::Level(const string filename) {
	deque<string> buffer;
	ifstream ifs(filename.c_str(), ios::binary);

	// Ensure setting default, preventing segmentation fault in destructor
	width = 0;
	height = 0;

	if(ifs.good()) {
		string line;

		while(!ifs.eof()) {
			getline(ifs, line);
			buffer.push_front(line);
		}

		// Exclude /n character
		width = buffer.back().size() -1;

		// Exclude last (empty) line
		height = buffer.size() -1;

		data = new char*[height];

		int line_num;
		for(line_num = 0; line_num < height; line_num++) {
			
			string line_c = buffer.back();
			data[line_num] = new char[width];
			std::cout << "loaded[" << line_c.size() << "]" << line_c << endl;

			int cell;
			for(cell = 0; cell < width; cell++) {
				data[line_num][cell] = line_c.c_str()[cell];
				
				char type = line_c.c_str()[cell];
				if (type == '$') {
				    generate_enemy(type, line_num, cell);
				}
			}

			buffer.pop_back();
		}
    
        // Clear enemies from loaded map, Game will draw them
        //for (line_num = 0; line_num < height; line_num++) {
            //int cell;
            //for(cell = 0; cell < width; cell++) {
                //if(get_cell(cell, line_num) == '$') {
                    //set_cell(cell, line_num, ' ');
                //}
            //}
        //}

		ifs.close();
	} else {
		std::cout << "Opening '" << filename << "' failed!" << endl;
	}
}

Level::~Level() {
	/* 	Check if level was not loaded, 
		otherwise will try to clear wrong memory */
	if(width != 0) {
		for (int i = 0; i < height; ++i) {
			delete [] data[i];
		}
		delete [] data;
	}
}

Enemy& Level::generate_enemy(char type, int x, int y) {
    static int enemy_count = 1;

    int hp      = random(Enemy::BASE_HP,    Enemy::BASE_HP      + Enemy::TOLERANCE_HP);
    int armor   = random(Enemy::BASE_ARMOR, Enemy::BASE_ARMOR   + Enemy::TOLERANCE_ARMOR);
    int damage  = random(Enemy::BASE_DMG,   Enemy::BASE_DMG     + Enemy::TOLERANCE_DMG);
    
    hp      *= type == '$' ? Enemy::BOSS_MULTIPL : 1.0f;
    armor   *= type == '$' ? Enemy::BOSS_MULTIPL : 1.0f;
    damage  *= type == '$' ? Enemy::BOSS_MULTIPL : 1.0f;
    
    Enemy enemy(type, hp, armor, damage, "Enemy_" + std::to_string(enemy_count++));
    enemy.set_x(x);
    enemy.set_y(y);
    
    std::cerr <<"Enemy loaded = " << hp << "," << armor << "," << damage << "," << enemy.get_name() << endl;
    
    enemies_.push_back(enemy);
    
    return enemies_.back();
}

void Level::set_player_position(Player* player) {
    int x, y;
	
	
    
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            if (get_cell(x,y) == '@') {
                player->set_x(x);
                player->set_y(y);
            }
        }
    }
    std::cerr << "Player loaded on = {" << player->get_x() << "," << player->get_y() << "}" << std::endl;
}

void Level::change_player_position(Player *player, int last_x, int last_y) {
	set_cell(last_x, last_y, '-');
	set_cell(player->get_x(), player->get_y(), '@');
	
}

void Level::print_level() {
	int x, y;
	
	for(y = 0; y < height; y++) {
		for(x = 0; x < width; x++) {
			std::cout << (char) get_cell(x,y);
		}
		std::cout << endl;
	}
}
