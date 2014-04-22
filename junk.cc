#include "junk.hh"

int Junk::get_hp() const {
	return hp_;
}

void Junk::print() const {
	Consumable::print();
	std::cout << "\t hp[" << hp_ << "]" << std::endl;
}