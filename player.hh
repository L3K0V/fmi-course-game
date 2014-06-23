#ifndef __PlAYER_H__
#define __PLAYER_H__

#include <string>

using std::string;

class Usable;

namespace game_player {

const int EQUIPMENT_SIZE 	= 12;
const int INVENTORY_SIZE 	= 20;

const int BASE_DAMAGE 		= 3;
const int BASE_CRIT 		= 2;
const int BASE_ARMOR 		= 0;
const float BASE_MISS		= 1.f;
const float BASE_DODGE		= 2.f;
const float ALC_PERCENTAGE	= 15.f / 100.f;
const float DOG_PERCENTAGE	= 20.f / 100.f;

/* EQUIPMENT INDEXES */
const int HELMET    = 0;
const int CHEST     = 1;
const int SHOWDERS  = 2;
const int LEGS      = 3;
const int BOOTS     = 4;
const int MAIN      = 5;
const int OFF       = 6;

}

using namespace game_player;

/*
 *   | 0 |
 *   |/|\|
 *  _ / \_
 */
class Player {
    private:
        friend class Alcohol;
        string name_;
        int hp_;
        int alcohol_;
        Usable *inventory_[INVENTORY_SIZE];

        /*
         * [0] - Helmet
         * [1] - Chest
         * [2] - Showders
         * [3] - Legs
         * [4] - Boots
         * [5] - Main hand
         * [6] - Off hand
         */
        Usable *equipment_[EQUIPMENT_SIZE];

        int equip_inventory_item(int entry);
        int equip_inventory_weapon(int entry);

        /*
         * Equip armor. Change if armor piece exist and it's weak compare to selected one.
         * Return 1 if equipped.
         * Return 0 if already equipped armor piece it's more strong
         * Return -1 if failure.
         */
        int equip_inventory_armor(int entry);
        int equip_armor(int type, int entry);
    public:
        Player(string name);
        ~Player();
        int add_to_inventory(Usable *usable);

        /* Return 1 if consumed (Usable like alcohol, junk food etc...)
         * Return 0 if not consumed (Weapons, Armor Equipment)
         * Return -1 if not exist */
        int use_inventory_item(int entry);
        int get_hp() const { return hp_;}
        int get_dmg() const;
        int get_armor() const;
        int get_critical() const;
        int get_alcohol() const { return alcohol_;}
        float get_miss_chance() const;
        float get_dodge_chance() const;
};

#endif //__PLAYER_H__
