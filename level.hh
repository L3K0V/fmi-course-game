#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Level {
private:
	int **data; //FIXME: CHAR
	int width;
	int height;
public:
	Level(const string);
	~Level();

	int get_width() const { return width;}
	int get_height() const { return height;}
	char get_cell(int x, int y) const {
        return (char) data[y][x];
    }
	void print_level();
};

#endif //LEVEL_H
