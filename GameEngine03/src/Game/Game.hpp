#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>


#include "../AssetManager/AssetManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"

const int FPS = 30;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    
        int windowWidth = 0;
        int windowHeight = 0;
        
        int milisecsPreviousFrame = 0;

        bool isRunning = false;

        std::unique_ptr<AssetManager> assetManager;
        std::unique_ptr<EventManager> eventManager;
        std::unique_ptr<Registry> registry;

        sol::state lua;
        
        void Setup();
        void ProcessInput();
        void Update();
        void Render();

        Game();
        ~Game();

    public:
        static Game& GetInstance();
        std::unique_ptr<ControllerManager> controllerManager;

        void Init();
        void Run();
        void Destroy();
};

#endif // GAME_HPP