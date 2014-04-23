#ifndef __JUNK_H__
#define __JUNK_H__

#include "usable.hh"

class Junk : public Usable {
private:
	int hp_;
public:
	Junk(char type, string name, int hp) 
	: Usable(type, name), hp_(hp) {}

	int get_hp() const;
	virtual void print() const;
};


#endif