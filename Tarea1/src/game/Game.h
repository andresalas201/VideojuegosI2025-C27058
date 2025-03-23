#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include "Entity.h"
const int FPS = 60;
const int MILLISEC_PER_FRAME = 1000 / FPS;

class Game {
    public:
        Game();
        ~Game();
        void init();
        void run();
        void destroy();
    private:
        void processInput();
        void update();
        void render();

        void initWindow(int red, int green, int blue);
        void initFont(std::string path);
        void initEntity();
        void initText();
        void readConfig();
        void moveEntity(double deltaTime);

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        
        size_t windowWidth = 0;
        size_t windowHeight = 0;

        bool isRunning = false;
        bool isPaused = false;
        int mPrvsFrame = 0;
        
        // Atributos de la imagen
        Entity* entity = nullptr; 
        SDL_Rect srcRect = {0,0,0,0};


        // Font
        TTF_Font* font = nullptr;
        int fontSize = 0;
        SDL_Color fontColor = {0,0,0};


        
};
#endif // GAME_H