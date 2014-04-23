#include "usable.hh"

char Usable::get_type() const {
	return type_;
}

string Usable::get_name() const {
	return name_;
}

void Usable::print() const {
	cout << name_ << "[" << type_ << "]" << endl;
}