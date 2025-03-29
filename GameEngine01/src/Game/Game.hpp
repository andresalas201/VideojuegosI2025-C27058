#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    
        int windowWidth = 0;
        int windowHeight = 0;
        
        bool isRunning = false;

        void ProcessInput();
        void Update();
        void Render();

        Game();
        ~Game();

    public:
        static Game& GetInstance();
        

        void Init();
        void Run();
        void Destroy();
};

#endif // GAME_HPP