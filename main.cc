#include <iostream>
#include <iomanip>

#include "game.hh"

using namespace std;

int main() {
    Player kamunn("Kamunn");

    Game* game = new Game();
    game->load();
    game->attach_player(&kamunn);
    game->run();
}
