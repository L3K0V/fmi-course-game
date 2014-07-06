#ifndef __LEVEL_LOADER_H__
#define __LEVEL_LOADER_H__

#define LEVELS_HOME "./levels/"

#include <deque>
#include <dirent.h>

#include "level.hh"

class LevelLoader {
public:
	~LevelLoader();
	
	int load_level_entries();
	Level& load_next_level();
	Level& get_current_level() const ;
private:
	deque<string> levels_;
	Level* level_;
};

#endif