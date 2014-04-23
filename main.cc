#include <iostream>
#include "level.hh"
#include "alcohol.hh"
#include "junk.hh"
#include "weapon.hh"

using namespace std;

int main() {
	Level level1("levels/1.level");
	cout << "W: " << level1.get_width() << " H: " << level1.get_height() << endl;
	level1.print_level();

	Alcohol a('B', "Hainaken", 5);
	Alcohol b('B', "Zagorga", 3);

	a.print();
	b.print();

	Junk k('B', "Whooper", 10);
	Junk l('B', "Grander Texas", 18);

	k.print();
	l.print();

	Weapon r('M', "Razer Keyboard", 10, 1.5f);
	r.print();

	Weapon r2('O', "Razer Mouse", 8, 1.2f);
	r2.print();
return  0;
}
