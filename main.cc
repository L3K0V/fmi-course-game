#include <iostream>
#include "level.hh"
#include "alcohol.hh"
#include "junk.hh"
#include "weapon.hh"
#include "player.hh"
#include <iomanip>

using namespace std;

int main() {
	Level level1("levels/1.level");
	cout << "W: " << level1.get_width() << " H: " << level1.get_height() << endl;
	level1.print_level();

	Alcohol *weak = new Alcohol('c', "Summersby", 10);

	Player sasho("Sashko");
	sasho.use_intentory_item(sasho.add_to_inventory(weak));
	sasho.use_intentory_item(sasho.add_to_inventory(new Alcohol('j', "Sokche", 11)));

	cout << setw(20) << left << "Alcohol" << " = " << sasho.get_alcohol() << endl;
	cout << setw(20) << left << "Damage" <<  " = " << sasho.get_dmg() << endl;
	cout << setw(20) << left << "Critical" << " = " << sasho.get_critical() << endl;
	cout << setw(20) << left << "Miss chance" << " = " << sasho.get_miss_chance() << endl;
	cout << setw(20) << left << "Dodge chance" << " = " << sasho.get_dodge_chance() << endl;
}
