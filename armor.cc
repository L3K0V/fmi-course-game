#include "armor.hh"
#include "player.hh"

#include <iostream>

void Armor::print() const {
	Usable::print();
	std::cout << "\t defense[" << defense_ << "]" << std::endl;
}

int Armor::use(Player &player) {
	return 0;
}