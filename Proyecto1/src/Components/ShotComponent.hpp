#ifndef SHOTCOMPONENT_HPP
#define SHOTCOMPONENT_HPP

#include <SDL2/SDL.h>

struct ShotComponent {
    bool isShot;
    int shotTime;

    ShotComponent (bool isShot = true) {
        this->isShot = isShot;
        this->shotTime = SDL_GetTicks();
    }
};

#endif // SHOTCOMPONENT_HPP