#include "consumable.hh"

char Consumable::get_type() const {
	return type_;
}

string Consumable::get_name() const {
	return name_;
}

void Consumable::print() const {
	cout << name_ << "[" << type_ << "]" << endl;
}