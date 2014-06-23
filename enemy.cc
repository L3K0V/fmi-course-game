#include "enemy.hh"

int Enemy::change_hp(int change) {
    hp_ += change;
    return hp_;
}
