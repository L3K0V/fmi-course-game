#include "enemy.hh"

const float Enemy::BOSS_MULTIPL = 1.3f;

int Enemy::change_hp(int change) {
    hp_ -= change;
    return hp_;
}

int Enemy::take_damage(int dmg) {
	dmg -= 0.4 * armor_;
	hp_ -= dmg;
	return hp_;
}