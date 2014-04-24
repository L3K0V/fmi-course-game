#ifndef __PlAYER_H__
#define __PLAYER_H__

#include <string>

using std::string;

class Usable;

const int EQUIPMENT_SIZE 	= 12;
const int INVENTORY_SIZE 	= 20;
const int BASE_DAMAGE 		= 3;
const int BASE_CRIT 		= 2;
const int BASE_ARMOR 		= 0;
const float BASE_MISS		= 1.f;
const float BASE_DODGE		= 2.f;
const float ALC_PERCENTAGE	= 15.f / 100.f;
const float DOG_PERCENTAGE	= 20.f / 100.f;

class Player {
private:
	friend class Alcohol;
	string name_;
	int hp_;
	int alcohol_;
	Usable *inventory_[INVENTORY_SIZE];
	Usable *equipment_[EQUIPMENT_SIZE];
	
public:
	Player(string name);
	~Player();
	int add_to_inventory(Usable *usable);
	
	/* Return 1 if consumed, 
 	 * Return 0 if not consumed,
 	 * Return -1 if not exist */
	int use_intentory_item(int entry);

	int get_hp() const { return hp_;}
	int get_dmg() const;
	int get_armor() const;
	int get_critical() const;
	int get_alcohol() const { return alcohol_;}
	float get_miss_chance() const;
	float get_dodge_chance() const;
};

#endif //__PLAYER_H__
