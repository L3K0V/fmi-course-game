#include "alcohol.hh"
#include "player.hh"

#include <iostream>

void Alcohol::print() const {
	Usable::print();
	std::cout << "\t alcohol[" << alcohol_ << "]" << std::endl;
}

int Alcohol::use(Player &player) {
	player.alcohol_ += alcohol_;
	return 1;
}