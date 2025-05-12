#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

#include "Game/Game.hpp"

int main (int argc, char* argv[]) {
      
    if(argc > 1) std::cout << argv [1] << std::endl;
    Game& game = Game::GetInstance();
    game.Init();
    game.Run();
    game.Destroy();

    return 0;
}