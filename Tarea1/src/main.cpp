#include <iostream>
#include "game/Game.h"
#include <sol/sol.hpp>

int main (int argc, char* argv[]) {
    Game game;
    game.init();
    game.run();
    game.destroy();
    return 0;
}