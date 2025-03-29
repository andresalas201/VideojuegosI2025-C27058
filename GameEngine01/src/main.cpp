#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

#include "Game/Game.hpp"

int main (int argc, char* argv[]) {
    
    std::cout << "Skibidi\n";
  
    Game& game = Game::GetInstance();
    game.Init();
    game.Run();
    game.Destroy();

    return 0;
}