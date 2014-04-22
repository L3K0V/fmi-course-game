#ifndef __JUNK_H__
#define __JUNK_H__

#include "consumable.hh"

class Junk : public Consumable {
private:
	int hp_;
public:
	Junk(char type, string name, int hp) 
	: Consumable(type, name), hp_(hp) {}

	int get_hp() const;
	virtual void print() const;
};


#endif