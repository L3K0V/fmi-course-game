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
        int result = inventory_[entry]->use(*this);
        /* So...usable  */
        if (result == 1) {
            delete inventory_[entry];
            inventory_[entry] = NULL;
            return 1;
        }
        /* So...equipment  */
        if (result == 0) {
            equip_inventory_item(entry);
            return 0;
        }
    }
    return -1;
}

int Player::equip_inventory_item(int entry) {
    Usable *usable = inventory_[entry];

    if (usable->get_type() == 'O' || usable->get_type() == 'T') {
        /* Weapons */
        return equip_inventory_weapon(entry);
    } else {
        /* Armor */
        return equip_inventory_armor(entry);
    }
    return -1;
}

//TODO: Can be refactored!
int Player::equip_inventory_weapon(int entry) {
    Usable *usable = inventory_[entry];
    if (equipment_[MAIN] == 0) {
        if(usable->get_type() == 'T' && equipment_[OFF] == 0)
            equipment_[MAIN] = usable;
        if(usable->get_type() == 'O')
            equipment_[MAIN] = usable;
        inventory_[entry] = NULL;
        return 1;
    } else if(equipment_[OFF] == 0 && usable->get_type() == 'O') {
        equipment_[OFF] = usable;
        inventory_[entry] = NULL;
        return 1;
    } else {
        // There's weapon
        Usable *main = equipment_[MAIN] == 0 ? NULL : equipment_[MAIN];
        Usable *off = equipment_[OFF] == 0 ? NULL : equipment_[OFF];

        switch(usable->get_type()) {
            case 'T': // Setting two-handed weapon
                equipment_[MAIN] = usable;
                equipment_[OFF] = NULL;
                inventory_[entry] = NULL;
                if(main != NULL) add_to_inventory(main);
                if(main != NULL) add_to_inventory(off);
                return 1;
            case 'O': // Setting one-handed weapon (change weakest if slot busy)
                if (off == NULL) {
                    equipment_[MAIN] = usable;
                    equipment_[OFF] = NULL;
                    inventory_[entry] = NULL;
                    if( main != NULL) add_to_inventory(main);
                } else {
                    if (((Weapon*) equipment_[OFF])->get_damage() > ((Weapon*) equipment_[MAIN])->get_damage()) {
                        equipment_[OFF] = usable;
                        inventory_[entry] = NULL;
                        add_to_inventory(off);
                    } else {
                        equipment_[MAIN] = usable;
                        inventory_[entry] = NULL;
                        add_to_inventory(main);
                    }
                }
                return 1;
        }
        return -1;
    }
    return -1;
}
//TODO: Can be refactored!
int Player::equip_inventory_armor(int entry) {
    Usable *usable = inventory_[entry];
    Usable *item = NULL;

    switch(usable->get_type()) {
        case 'H':
            if (((Armor*) usable)->get_defense() > ((Armor*) equipment_[HELMET])->get_defense()) {
                item = equipment_[HELMET];
                equipment_[HELMET] = usable;
                inventory_[entry] = NULL;
                add_to_inventory(item);
            }
            return 1;
        case 'C':
            if (((Armor*) usable)->get_defense() > ((Armor*) equipment_[CHEST])->get_defense()) {

                item = equipment_[CHEST];
                equipment_[CHEST] = usable;
                inventory_[entry] = NULL;
                add_to_inventory(item);
            }
            return 1;
        case 'S':
            if (((Armor*) usable)->get_defense() > ((Armor*) equipment_[SHOWDERS])->get_defense()) {
                item = equipment_[SHOWDERS];
                equipment_[SHOWDERS] = usable;
                inventory_[entry] = NULL;
                add_to_inventory(item);
            }
            return 1;
        case 'L':
            if (((Armor*) usable)->get_defense() > ((Armor*) equipment_[LEGS])->get_defense()) {
                item = equipment_[LEGS];
                equipment_[LEGS] = usable;
                inventory_[entry] = NULL;
                add_to_inventory(item);
            }
            return 1;
        case 'B':
            if (((Armor*) usable)->get_defense() > ((Armor*) equipment_[BOOTS])->get_defense()) {
                item = equipment_[BOOTS];
                equipment_[BOOTS] = usable;
                inventory_[entry] = NULL;
                add_to_inventory(item);
            }
            return 1;
        default: return -1;
    }
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
