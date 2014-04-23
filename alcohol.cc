#include "alcohol.hh"

int Alcohol::get_alcohol() const {
	return alcohol_;
}

void Alcohol::print() const {
	Usable::print();
	std::cout << "\t alcohol[" << alcohol_ << "]" << std::endl;
}