#include "Game.hpp"

#include <iostream>

#include "../Events/ClickEvent.hpp"

#include "../Systems/RenderSystem.hpp"
#include "../Systems/CircleCollisionSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/CameraMovementSystem.hpp"
#include "../Systems/BoxCollisionSystem.hpp"
#include "../Systems/RenderBoxColliderSystem.hpp"


Game::Game() {
    std::cout <<"[GAME] se ejecuta\n";

    registry = std::make_unique<Registry>();
    assetManager = std::make_unique<AssetManager>();
    eventManager = std::make_unique<EventManager>();
    controllerManager = std::make_unique<ControllerManager>();
    sceneManager = std::make_unique<SceneManager>();
}

Game::~Game() {
    registry.reset();
    assetManager.reset();
    controllerManager.reset();
    sceneManager.reset();
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

    this->camera.x = 0;
    this->camera.y = 0;
    this->camera.w = this->windowWidth;
    this->camera.h = this->windowHeight;

    this->isRunning = true;
}

void Game::Run() {
    Setup();
    while (this->isRunning) {
        sceneManager->StartScene();
        RunScene();
    }
}

void Game::RunScene() {
    sceneManager->LoadScene();
    
    while(isRunning && sceneManager->IsSceneRunning()) {
        ProcessInput();
        Update();
        Render();
    }

    assetManager->ClearAssets();
    registry->ClearAllEntities();
}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                this->isRunning = false;
                sceneManager->StopScene();
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    this->isRunning = false;
                    sceneManager->StopScene();
                    break;
                }
                if (sdlEvent.key.keysym.sym == SDLK_i) {
                    this->isDebugMode = !this->isDebugMode;
                }
                controllerManager->KeyDown(sdlEvent.key.keysym.sym);
                break;
            case SDL_KEYUP:
                controllerManager->KeyUp(sdlEvent.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                int x,y;
                SDL_GetMouseState(&x, &y);
                controllerManager->SetMousePosition(x, y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                controllerManager->SetMousePosition(sdlEvent.button.x,
                    sdlEvent.button.y);
                controllerManager->MouseButtonDown(static_cast<int>(sdlEvent.button.button));
                eventManager->EmitEvent<ClickEvent>(static_cast<int>(sdlEvent.button.button),
                    sdlEvent.button.x, sdlEvent.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
            controllerManager->SetMousePosition(sdlEvent.button.x,
                sdlEvent.button.y);
            controllerManager->MouseButtonUp(static_cast<int>(sdlEvent.button.button));
                break;
            default:
                break;
        }
    }
}

void Game::Update() {
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks()
        - milisecsPreviousFrame);
    if(0 < timeToWait && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }
    double deltaTime = (SDL_GetTicks() - milisecsPreviousFrame) / 1000.0;
    // TODO: Agregar esta variable al estado de LUA

    milisecsPreviousFrame = SDL_GetTicks();


    // Reiniciar las subscripciones
    eventManager->Reset();
    registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
    registry->GetSystem<UISystem>().SubscribeToClicEvent(eventManager);

    registry->Update();
    registry->GetSystem<ScriptSystem>().Update(lua);
    registry->GetSystem<CameraMovementSystem>().Update(this->camera);
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<CircleCollisionSystem>().Update(eventManager);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<BoxCollisionSystem>().Update(lua);
}

void Game::Setup() {
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<CircleCollisionSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<ScriptSystem>();
    registry->AddSystem<RenderTextSystem>();
    registry->AddSystem<UISystem>();
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<BoxCollisionSystem>();
    registry->AddSystem<RenderBoxColliderSystem>();
    
    sceneManager->LoadSceneFromScript("assets/scripts/scenes.lua", lua);

    lua.open_libraries(sol::lib::base, sol::lib::math);
    registry->GetSystem<ScriptSystem>().CreateLuaBinding(lua);
}

void Game::Render() {
    SDL_SetRenderDrawColor(this->renderer, 31, 31, 31, 255);
    SDL_RenderClear(this->renderer);
    registry->GetSystem<RenderSystem>().Update(renderer, camera, assetManager);
    registry->GetSystem<RenderTextSystem>().update(renderer, assetManager);
    if (isDebugMode) {
        registry->GetSystem<RenderBoxColliderSystem>().update(renderer, camera);
    }
    SDL_RenderPresent(this->renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}