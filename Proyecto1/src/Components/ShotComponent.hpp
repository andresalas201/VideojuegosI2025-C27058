#ifndef SHOTCOMPONENT_HPP
#define SHOTCOMPONENT_HPP

#include <SDL2/SDL.h>

struct ShotComponent {
    bool isShot;
    bool playerShot;
    int shotTime;

    ShotComponent (bool isShot = true, bool playerShot = false) {
        this->isShot = isShot;
        this->shotTime = SDL_GetTicks();
        this->playerShot = playerShot;
    }
};

#endif // SHOTCOMPONENT_HPP