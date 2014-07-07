#include <iostream>
#include <iomanip>

#include "game.hh"
#include "armor.hh"
#include "weapon.hh"

using namespace std;

int main() {
    Player kamunn("Kamunn");
	kamunn.use_inventory_item(kamunn.add_to_inventory(new Armor('C', "C#hest", 15)));
	kamunn.use_inventory_item(kamunn.add_to_inventory(new Weapon('T', "Mighty Java Sword", 20, 10)));

    Game* game = new Game();
    game->load();
    game->attach_player(&kamunn);
    game->run();
}
