#include <iostream>
#include <iomanip>

#include "game.hh"

using namespace std;

int main() {
    Player kamunn("Kamunn");

    Game game;
    game.load_level("levels/1.level");
    game.attach_player(&kamunn);
    game.run();
}
