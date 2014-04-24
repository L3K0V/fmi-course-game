#ifndef __ALCOHOL_H__
#define __ALHOCOL_H__

#include "usable.hh"

class Alcohol : public Usable {
private:
	int alcohol_;
public:
	Alcohol(char type, string name, int alcohol)
	: Usable(type, name) , alcohol_(alcohol){}

	int get_alcohol() const { return alcohol_;}
	virtual void print() const;
	virtual int use(Player &player);
};

#endif