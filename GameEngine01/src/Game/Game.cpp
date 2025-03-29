#include "Game.hpp"
#include <iostream>

Game::Game() {
    std::cout <<"[GAME] se ejecuta\n";
}

Game::~Game() {

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
            default:
                break;
        }
    }
}

void Game::Update() {
    // TODO
}

void Game::Render() {
    SDL_SetRenderDrawColor(this->renderer, 31, 31, 31, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}