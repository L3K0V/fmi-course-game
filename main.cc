#include <iostream>
#include "level.hh"

using namespace std;

int main() {
	Level level1("levels/1.level");
	cout << "W: " << level1.get_width() << " H: " << level1.get_height() << endl;
	level1.print_level();
return  0;
}
