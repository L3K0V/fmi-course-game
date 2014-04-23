#include "armor.hh"

int Armor::get_defense() const {
	return defense_;
}

void Armor::print() const {
	Usable::print();
	std::cout << "\t defense[" << defense_ << "]" << std::endl;
}