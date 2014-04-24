#include "usable.hh"

#include <iostream>

void Usable::print() const {
	std::cout << name_ << "[" << type_ << "]" << std::endl;
}

Usable::~Usable() {}