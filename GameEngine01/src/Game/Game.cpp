#include "Game.hpp"

#include <iostream>
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"


Game::Game() {
    std::cout <<"[GAME] se ejecuta\n";

    registry = std::make_unique<Registry>();
    assetManager = std::make_unique<AssetManager>();
}

Game::~Game() {
    registry.reset();
    assetManager.reset();
    std::cout << "[GAME] se destruye\n";
}

Game& Game::GetInstance() {
    static Game game;
    return game;
}

void Game::Init() {

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL no se abrió correctamente\n";
        return;
    }

    this->windowWidth = 800;
    this->windowHeight = 600;
    this->window = SDL_CreateWindow(
        "Motor de juegos",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->windowWidth,
        this->windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!this->window) {
        std::cout << "[GAME] Error al crear la ventana\n"; 
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, 0 );

    if (TTF_Init() != 0) {
        std::cout << "Error al abrir TTF\n";
        return;
    }
    this->isRunning = true;
}

void Game::Run() {
    Setup();
    while (this->isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                this->isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    this->isRunning = false;
                }
                break;

            default:
                break;
        }
    }
}

void Game::Update() {
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks())
        - milisecsPreviousFrame;
        if(0 < timeToWait && timeToWait <= MILLISECS_PER_FRAME) {
            SDL_Delay(timeToWait);
        }
        double deltaTime = (SDL_GetTicks() - milisecsPreviousFrame) / 1000.0;
        // TODO: Agregar esta variable al estado de LUA

        milisecsPreviousFrame = SDL_GetTicks();

        registry->Update();
        registry->GetSystem<MovementSystem>().Update(deltaTime);
}

void Game::Setup() {
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<MovementSystem>();
    assetManager->AddTexture(renderer, 
        "enemy_alan", "assets/images/enemy_alan.png");
    Entity enemy = registry->CreateEntity();
    enemy.AddComponent<TransformComponent>(glm::vec2(100.0,100.0), 
        glm::vec2(2.0, 2.0), 0.0);
    enemy.AddComponent<SpriteComponent>("enemy_alan", 16, 16, 0, 0);
    enemy.AddComponent<RigidBodyComponent>(glm::vec2(50, 0));
    registry->AddEntityToSystems(enemy);
    
}

void Game::Render() {
    SDL_SetRenderDrawColor(this->renderer, 31, 31, 31, 255);
    SDL_RenderClear(this->renderer);
    registry->GetSystem<RenderSystem>().Update(renderer, assetManager);

    SDL_RenderPresent(this->renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}