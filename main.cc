#include <iostream>
#include <iomanip>

#include "game.hh"

using namespace std;

int main() {
    Game game;
    game.load_level("levels/1.level");
    game.run();
}
