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
        
        int x_,y_;
    public:
        const static int BASE_HP = 100;
        const static int TOLERANCE_HP = 25;

        const static int BASE_ARMOR = 20;
        const static int TOLERANCE_ARMOR = 10;

        const static int BASE_DMG = 10;
        const static int TOLERANCE_DMG = 5;

        const static float BOSS_MULTIPL;

        /*
         * Enemy types:
         *  'B' - Boss
         *  'M' - Monster
         */
        Enemy(char type, int hp, int armor, int dmg, string name)
            :type_(type), hp_(hp),armor_(armor), dmg_(dmg), name_(name) {}
        char get_type() const {return type_;}
        int get_hp() const {return hp_;}
        int get_armor() const {return armor_;}
        string get_name() const {return name_;}

        int change_hp(int change);
        
        int get_x() const { return y_; }
        int get_y() const { return x_; }
        
        void set_x(int x) { x_ = x; }
        void set_y(int y) { y_ = y; }
};

#endif //__ENEMY_H__
