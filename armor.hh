#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "usable.hh"

class Armor: public Usable {
private:
	int defense_;
public:
	Armor(char type, string name, int defense)
	: Usable(type, name) , defense_(defense){}

	int get_defense() const;
	virtual void print() const;
};

#endif