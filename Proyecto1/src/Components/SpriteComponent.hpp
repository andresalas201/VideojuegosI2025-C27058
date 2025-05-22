#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

struct SpriteComponent {
    std::string textureId;
    int width;
    int height;
    SDL_Rect srcRect;
    SDL_Rect hitSrcRect;
    bool isHit;
    int hitTime;
    int showHitCounter;
    int srcRectBase;
    int hitSrcRectBase;
    int upX;
    int downX;
    int hitUpX;
    int hitDownX;

    SpriteComponent(const std::string& textureId = "none", int width = 0, 
        int height = 0, int srcRectX = 0, int srcRectY = 0,
        int hitRectX = 0, int hitRectY = 0, int upX = 0, int downX = 0,
        int hitUpX = 0, int hitDownX = 0) {
        
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->srcRect = {srcRectX, srcRectY, width, height};
        this->srcRectBase = srcRectX;
        this->hitSrcRect = {hitRectX, hitRectY, width, height};
        this->hitSrcRectBase = hitRectX;
        this->isHit = false;
        this->showHitCounter = 0;
        this->upX = upX;
        this->downX = downX;
        this->hitUpX = hitUpX;
        this->hitDownX = hitDownX;
    }

};

#endif // SPRITECOMPONENT_HPP