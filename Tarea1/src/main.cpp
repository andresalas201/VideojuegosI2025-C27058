#include <iostream>
#include <fstream>
#include "game/Game.h"
#include <sol/sol.hpp>
#include <string>

int main (int argc, char* argv[]) {
    Game game;
    game.init();
    game.run();
    game.destroy();
    return 0;
}