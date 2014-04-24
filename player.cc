#include "player.hh"
#include "weapon.hh"
#include "armor.hh"

#include <cstring>

Player::Player(string name) 
: name_(name), hp_(100), alcohol_(1) {
	memset(&inventory_, 0, sizeof(Usable*) * INVENTORY_SIZE);
	memset(&equipment_, 0, sizeof(Usable*) * EQUIPMENT_SIZE);
}

Player::~Player() {
	for (int i = 0; i < INVENTORY_SIZE; ++i) {
		if(inventory_[i] != NULL) {
			delete inventory_[i];
			inventory_[i] = NULL;
		}
	}

	for (int i = 0; i < EQUIPMENT_SIZE; ++i) {
		if(equipment_[i] != NULL) {
			delete equipment_[i];
			equipment_[i] = NULL;
		}
	}
}

int Player::add_to_inventory(Usable *usable) {
	int i = -1;
	while(inventory_[++i] && i < INVENTORY_SIZE)
		;
	if(i != INVENTORY_SIZE)
		inventory_[i] = usable;
	return i;
}

int Player::use_intentory_item(int entry) {
	if (inventory_[entry]) {
		if (inventory_[entry]->use(*this) == 1) {
			delete inventory_[entry];
			inventory_[entry] = NULL;
			return 1;
		}
	}
	return -1;
}

int Player::get_dmg() const {
	int dmg = BASE_DAMAGE;
	for(int i = 0; i < EQUIPMENT_SIZE; i++) {
		if ((equipment_[i] != 0) &&
			(equipment_[i]->get_type() == 'O' || equipment_[i]->get_type() == 'T')) {
			dmg += ((Weapon*) equipment_[i])->get_damage();
		}
	}
	return dmg;
}
	
int Player::get_armor() const {
	int armor = BASE_ARMOR;
	for(int i = 0; i < EQUIPMENT_SIZE; i++) {
		if ((equipment_[i] != 0) &&
			(equipment_[i]->get_type() != 'O' || equipment_[i]->get_type() != 'T')) {
			armor += ((Armor*) equipment_[i])->get_defense();
		}
	}
	return armor;
}

int Player::get_critical() const {
	int crit = BASE_CRIT;
	for(int i = 0; i < EQUIPMENT_SIZE; i++) {
		if ((equipment_[i] != 0) &&
			(equipment_[i]->get_type() == 'O' || equipment_[i]->get_type() == 'T')) {
			crit += ((Weapon*) equipment_[i])->get_critical();
		}
	}
	return crit;
}

float Player::get_miss_chance() const {
	return BASE_MISS + (alcohol_ * ALC_PERCENTAGE);
}

float Player::get_dodge_chance() const {
	// FIXME: thats why
	return BASE_DODGE - (hp_ * DOG_PERCENTAGE) + (alcohol_ * ALC_PERCENTAGE);
}