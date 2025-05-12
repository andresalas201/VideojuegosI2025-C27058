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
#include "../SceneManager/SceneManager.hpp"

extern int FPS;
extern int MILLISECS_PER_FRAME;

class Game {
    private:
        SDL_Window* window = nullptr;
    
        int windowWidth = 0;
        int windowHeight = 0;
        
        int milisecsPreviousFrame = 0;

        bool isRunning = false;
        
        void Setup();
        void RunScene();
        void ProcessInput();
        void Update();
        void Render();
        void LoadConfig();

        Game();
        ~Game();

    public:
        
        std::unique_ptr<AssetManager> assetManager;
        std::unique_ptr<EventManager> eventManager;
        std::unique_ptr<Registry> registry;
        std::unique_ptr<SceneManager> sceneManager;
        sol::state lua;
        SDL_Renderer* renderer = nullptr;
        SDL_AudioDeviceID* audioDevice = nullptr;
        std::unique_ptr<ControllerManager> controllerManager;

        static Game& GetInstance();

        void Init();
        void Run();
        void Destroy();
};

#endif // GAME_HPH