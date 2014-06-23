#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "usable.hh"

class Weapon: public Usable {
private:
	int damage_;
	int crit_;
public:
	/* 
	 * Weapon types:
	 *	'O' - One hand
	 *  'T' - Two hand
	 */
	Weapon(char type, string name, int damage, int crit)
	: Usable(type, name) , damage_(damage), crit_(crit){}

	int get_damage() const {return damage_;}
	int get_critical() const {return crit_;}
	virtual int get_attribute() const;
	virtual void print() const;
	virtual int use(Player &player);
};

#endif
