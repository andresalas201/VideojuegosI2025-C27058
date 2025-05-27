#include "Game.hpp"

#include <iostream>

#include "../Events/ClickEvent.hpp"

#include "../Systems/RenderSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/DeathSystem.hpp"
#include "../Systems/AudioSystem.hpp"
#include "../Systems/CleanShotSystem.hpp"
#include "../Systems/ClearHitSystem.hpp"
#include "../Systems/EnemySpawnSystem.hpp"
#include "../Systems/CleanEnemiesSystem.hpp"
#include "../Systems/DropSystem.hpp"
#include "../Systems/ScoreSystem.hpp"
#include "../Systems/LevelEndSystem.hpp"

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

    LoadConfig();

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

void Game::LoadConfig() {
    lua.script_file("assets/scripts/config.lua");
    sol::table config = lua["config"];
    FPS = config["fps"];
    MILLISECS_PER_FRAME = 1000 / FPS;
    secondsPerShot = config["seconds_per_shot"];
    windowWidth = config["width"];
    windowHeight = config["height"];
    spawnWait = config["spawn_wait"];
}

void Game::Run() {
    if (!this->isRunning) return;
    Setup();
    while (this->isRunning) {
        sceneManager->StartScene();
        RunScene();
    }
}

void Game::RunScene() {
    sceneManager->LoadScene();
    // TODO: Resetear lo que necesita reset
    this->registry->GetSystem<LevelEndSystem>().Reset();
    this->registry->GetSystem<EnemySpawnSystem>().Reset();
    this->milisecsPreviousFrame = SDL_GetTicks();
    while(isRunning && sceneManager->IsSceneRunning()) {
        ProcessInput();
        
        if (!isPaused) {
            Update();
            std::cout << "skibidiOver\n";
            Render();
        } else this->milisecsPreviousFrame = SDL_GetTicks();
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
                if (sdlEvent.key.keysym.sym == SDLK_p) {
                    this->isPaused = !this->isPaused;
                    break;
                }
                if(!this->isPaused)controllerManager->KeyDown(sdlEvent.key.keysym.sym);
                break;
            case SDL_KEYUP:
                controllerManager->KeyUp(sdlEvent.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                int x,y;
                SDL_GetMouseState(&x, &y);
                if(!this->isPaused) controllerManager->SetMousePosition(x, y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                controllerManager->SetMousePosition(sdlEvent.button.x,
                    sdlEvent.button.y);
                if(!this->isPaused) {
                    controllerManager->MouseButtonDown(static_cast<int>(sdlEvent.button.button));
                    eventManager->EmitEvent<ClickEvent>(static_cast<int>(sdlEvent.button.button),
                        sdlEvent.button.x, sdlEvent.button.y);
                }
                break;
            case SDL_MOUSEBUTTONUP:
            controllerManager->SetMousePosition(sdlEvent.button.x,
                sdlEvent.button.y);
            if(!this->isPaused) controllerManager->MouseButtonUp(static_cast<int>(sdlEvent.button.button));
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

    milisecsPreviousFrame = SDL_GetTicks();

    // Reiniciar las subscripciones
    eventManager->Reset();
    registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
    registry->GetSystem<UISystem>().SubscribeToClicEvent(eventManager);
    registry->GetSystem<DeathSystem>().SubscribeToDeathEvent(eventManager);
    registry->GetSystem<DropSystem>().SubscribeToGroupDeathEvent(eventManager);
    registry->GetSystem<ScoreSystem>().SubscribeToDeathEvent(eventManager);
    registry->Update();
    registry->GetSystem<ScriptSystem>().Update(lua);
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<CollisionSystem>().Update(eventManager);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<DamageSystem>().Update(eventManager);
    registry->GetSystem<CleanShotSystem>().Update(MILLISECS_PER_FRAME, FPS, secondsPerShot);
    registry->GetSystem<ClearHitSystem>().Update(MILLISECS_PER_FRAME, FPS);
    registry->GetSystem<DeathSystem>().Update(MILLISECS_PER_FRAME, FPS, windowHeight,
        eventManager);
    std::cout << "toilet1\n";
    registry->GetSystem<EnemySpawnSystem>().Update(registry, eventManager);
    std::cout << "toilet2\n";
    registry->GetSystem<CleanEnemiesSystem>().Update(registry);
    std::cout << "toilet2\n";
    registry->GetSystem<ScoreSystem>().Update();
    std::cout << "toilet3\n";
    registry->GetSystem<LevelEndSystem>().Update(registry, sceneManager);
    std::cout << "skibidi4\n";
}

void Game::Setup() {
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<ScriptSystem>();
    registry->AddSystem<RenderTextSystem>();
    registry->AddSystem<UISystem>();
    registry->AddSystem<DeathSystem>();
    registry->AddSystem<AudioSystem>();
    registry->AddSystem<CleanShotSystem>();
    registry->AddSystem<ClearHitSystem>();
    registry->AddSystem<EnemySpawnSystem>();
    registry->AddSystem<CleanEnemiesSystem>();
    registry->AddSystem<DropSystem>();
    registry->AddSystem<ScoreSystem>();
    registry->AddSystem<LevelEndSystem>();
    
    registry->GetSystem<CleanShotSystem>().setSecondsPerShot(secondsPerShot);
    registry->GetSystem<DamageSystem>().SetDamageWait(FPS, MILLISECS_PER_FRAME, 1);
    registry->GetSystem<EnemySpawnSystem>().SetParameter(this->spawnWait,
        this->windowWidth, this->windowHeight);
    registry->GetSystem<CleanEnemiesSystem>().SetParameter(this->windowHeight,
        this->windowWidth);
    sceneManager->LoadSceneFromScript("assets/scripts/scenes.lua", lua);

    lua.open_libraries(sol::lib::base, sol::lib::math);
    registry->GetSystem<ScriptSystem>().CreateLuaBinding(lua);
}



void Game::Render() {
    SDL_SetRenderDrawColor(this->renderer, 31, 31, 31, 255);
    SDL_RenderClear(this->renderer);
    registry->GetSystem<RenderSystem>().Update(renderer, assetManager);
    registry->GetSystem<RenderTextSystem>().update(renderer, assetManager);
    SDL_RenderPresent(this->renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    registry->GetSystem<AudioSystem>().stopMusic();
    TTF_Quit();
    SDL_Quit();
}