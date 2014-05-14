#include <iostream>
#include <iomanip>
#include <ncurses.h>

#include "level.hh"
#include "alcohol.hh"
#include "junk.hh"
#include "weapon.hh"
#include "player.hh"
#include "armor.hh"

using namespace std;

int main() {
	Level level1("levels/1.level");
	cout << "W: " << level1.get_width() << " H: " << level1.get_height() << endl;
	level1.print_level();

	Alcohol *weak = new Alcohol('c', "Summersby", 10);

	Player sasho("Sashko");
	sasho.use_inventory_item(sasho.add_to_inventory(weak));
	sasho.use_inventory_item(sasho.add_to_inventory(new Alcohol('j', "Sokche", 11)));

    sasho.use_inventory_item(sasho.add_to_inventory(new Weapon('O', "Razer Mouse", 10, 12)));
    sasho.use_inventory_item(sasho.add_to_inventory(new Weapon('O', "Razer Mouse", 10, 12)));

    sasho.use_inventory_item(sasho.add_to_inventory(new Weapon('T', "CM Fire Brown", 30, 50)));

    sasho.use_inventory_item(sasho.add_to_inventory(new Armor('H', "GUnit", 10)));

    cout << setw(20) << left << "Armor" << " = " << sasho.get_armor() << endl;
	cout << setw(20) << left << "Alcohol" << " = " << sasho.get_alcohol() << endl;
	cout << setw(20) << left << "Damage" <<  " = " << sasho.get_dmg() << endl;
	cout << setw(20) << left << "Critical" << " = " << sasho.get_critical() << endl;
	cout << setw(20) << left << "Miss chance" << " = " << sasho.get_miss_chance() << endl;
	cout << setw(20) << left << "Dodge chance" << " = " << sasho.get_dodge_chance() << endl;
}
