#include "enemy.hh"

const float Enemy::BOSS_MULTIPL = 1.3f;

int Enemy::change_hp(int change) {
    hp_ += change;
    return hp_;
}
