#include "junk.hh"
#include "player.hh"

#include <iostream>

void Junk::print() const {
	Usable::print();
	std::cout << "\t hp[" << hp_ << "]" << std::endl;
}

int Junk::use(Player &player) {
	// TODO:
	return 0;
}