#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "usable.hh"

class Armor: public Usable {
    private:
        int defense_;
    public:
        /*
         * Armor types:
         *	'C' - Chest
         *	'B' - Boots
         *	'H' - Helmet
         *	'L' - Legs
         */
        Armor(char type, string name, int defense)
            : Usable(type, name) , defense_(defense){}

        int get_defense() const {return defense_;}
        virtual void print() const;
        virtual int use(Player &player);
};

#endif
