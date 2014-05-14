#include "level.hh"
#include <fstream>
#include <deque>
#include <iostream>

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

		data = new int*[height];

		int line_num;
		for(line_num = 0; line_num < height; line_num++) {
			
			string line_c = buffer.back();
			data[line_num] = new int[width];
			std::cout << "loaded[" << line_c.size() << "]" << line_c << endl;

			int cell;
			for(cell = 0; cell < width; cell++) {
				data[line_num][cell] = line_c.c_str()[cell];
			}

			buffer.pop_back();
		}

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

void Level::print_level() {
	int x, y;
	
	for(y = 0; y < height; y++) {
		for(x = 0; x < width; x++) {
			std::cout << (char) get_cell(x,y);
		}
		std::cout << endl;
	}
}