#include <iostream>
#include <iomanip>

#include "game.hh"

using namespace std;

int main() {
    Player kamunn("Kamunn");

    Game game;
    game.load_level("levels/3.level");
    game.attach_player(&kamunn);
    game.run();
}
