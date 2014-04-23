#include "weapon.hh"

int Weapon::get_damage() const {
	return damage_;
}

float Weapon::get_critical() const {
	return crit_;
}

int Weapon::get_critical_damage() const {
	return damage_ * crit_;
}

void Weapon::print() const {
	Usable::print();
	std::cout << "\t damage[" << damage_ << "]" << std::endl;
	std::cout << "\t critical[" << crit_ << "]" << std::endl;
	std::cout << "\t critical_damage[" << get_critical_damage() << "]" << std::endl; 
}