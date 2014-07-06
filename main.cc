#include <iostream>
#include <iomanip>

#include "game.hh"
#include "armor.hh"
#include "weapon.hh"

using namespace std;

int main() {
    Player kamunn("Kamunn");
	kamunn.use_inventory_item(kamunn.add_to_inventory(new Armor('C', "C#hest", 50)));
	kamunn.use_inventory_item(kamunn.add_to_inventory(new Weapon('T', "Might Java Sword", 25, 35)));

    Game* game = new Game();
    game->load();
    game->attach_player(&kamunn);
    game->run();
}
