#include "alcohol.hh"

int Alcohol::get_alcohol() const {
	return alcohol_;
}

void Alcohol::print() const {
	Consumable::print();
	std::cout << "\t alcohol[" << alcohol_ << "]" << std::endl;
}