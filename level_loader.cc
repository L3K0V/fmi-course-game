#include "level_loader.hh"

int LevelLoader::load_level_entries() {
	DIR *dpdf;
	struct dirent *epdf;
	
	int skip = 0;

	dpdf = opendir("./levels");
	if (dpdf != NULL){
	   while ((epdf = readdir(dpdf)) && ++skip){
		   if(skip > 2) {
		   		std::cout << "Filename: " << epdf->d_name << std::endl;
				levels_.push_back(string(epdf->d_name));
		   }
	   }
	}
}

Level& LevelLoader::load_next_level() {
	if (level_ != NULL) {
		delete level_;
		level_ = NULL;
	}
	
	level_ = new Level(LEVELS_HOME + levels_.front());
	levels_.pop_front();
	return *level_;
}

Level& LevelLoader::get_current_level() const {
	return *level_;
}

LevelLoader::~LevelLoader() {
	if(level_ != NULL) {
		delete level_;
		level_ = NULL;
	}
}