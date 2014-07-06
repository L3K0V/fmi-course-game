#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

using std::string;

class Usable;

enum equipment {
    HELMET, CHEST, SHOWDERS, LEGS, BOOTS, MAIN, OFF
};

/*
 *   | 0 |
 *   |/|\|
 *  _ / \_
 */
class Player {
    public:
    
        const static int EQUIPMENT_SIZE 	= 12;
        const static int INVENTORY_SIZE 	= 20;

        const static int BASE_DAMAGE 		= 3;
        const static int BASE_CRIT 		    = 2;
        const static int BASE_ARMOR 		= 0;
        const static float BASE_MISS;
        const static float BASE_DODGE;
        const static float ALC_PERCENTAGE;
        const static float DOG_PERCENTAGE;
    
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
        int get_x() { return x_;}
        int get_y() { return y_;}
        void set_x(int x) { x_ = x; }
        void set_y(int y) { y_ = y; }
		
		int take_damage(int dmg);
		int deal_damage();
    private:
        friend class Alcohol;
        string name_;
        int hp_;
        int alcohol_;
        int x_,y_;
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
};

#endif //__PLAYER_H__
