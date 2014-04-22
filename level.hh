#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <vector>
#include <string>

using namespace std;

class Level {
private:
	int **data;
	int width;
	int height;
public:
	Level(const string);
	~Level();
	
	const int get_width();
	const int get_height();
	const char get_cell(int, int);

	void print_level();
};

#endif //LEVEL_H
