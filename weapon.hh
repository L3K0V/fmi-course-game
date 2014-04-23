#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "usable.hh"

class Weapon: public Usable {
private:
	int damage_;
	float crit_;
public:
	Weapon(char type, string name, int damage, float crit)
	: Usable(type, name) , damage_(damage), crit_(crit){}

	int get_damage() const;
	float get_critical() const;
	int get_critical_damage() const;
	virtual void print() const;
};

#endif