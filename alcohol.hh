#ifndef __ALCOHOL_H__
#define __ALHOCOL_H__

#include "consumable.hh"

class Alcohol : public Consumable {
private:
	int alcohol_;
public:
	Alcohol(char type, string name, int alcohol)
	: Consumable(type, name) , alcohol_(alcohol){}

	int get_alcohol() const;
	virtual void print() const;
};

#endif