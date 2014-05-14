#include "weapon.hh"
#include "player.hh"

#include <iostream>

void Weapon::print() const {
	Usable::print();
	std::cout << "\t damage[" << damage_ << "]" << std::endl;
	std::cout << "\t critical[" << crit_ << "]" << std::endl;
}

int Weapon::use(Player &player) {
	// TODO:
	return 0;
}