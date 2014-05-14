#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <string>

using std::string;

class Enemy {
    private:
        char type_;
        int hp_;
        int armor_;
        int dmg_;
        string name_;
    public:
        Enemy(char type, int hp, int armor, int dmg, string name)
            :type_(type), hp_(hp),armor_(armor), dmg_(dmg), name_(name) {}
        char get_type() const {return type_;}
        int get_hp() const {return hp_;}
        int get_armor() const {return armor_;}
        string get_name() const {return name_;}

        int change_hp(int change);
};

#endif //__ENEMY_H__
