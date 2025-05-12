#ifndef ATTACKCOMPONENT_HPP
#define ATTACKCOMPONENT_HPP

#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct AttackComponent {

    int damage;
    int radius;
    int width;
    int height;
    std::string textureId;
    SDL_Rect srcRect;
    glm::vec2 velocity;
    std::string shootSoundFilePath;
    std::string hitSoundFilePath;
    int maxShots;
    int currentShots;
    bool left;
    glm::vec2 scale;
    double rotation;
    int lastShotTick;
    
    AttackComponent(int damage = 1, int radius = 0, int width = 0, int height = 0,
        const std::string& textureId = "none", int srcX = 0, int srcY = 0,
        glm::vec2 velVec = glm::vec2(0.0, 0.0), std::string soundFile = "",
        std::string hitSoundFilePath = "none", int maxShots = 0, bool left = false,
        glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0) {   

        this->damage = damage;
        this->radius = radius;
        this->width = width;
        this->height = height;
        this->textureId = textureId;
        this->srcRect = {srcX, srcY, width, height};
        this->velocity = velVec;
        this->shootSoundFilePath = soundFile;
        this->hitSoundFilePath = hitSoundFilePath;
        this->maxShots = maxShots;
        this->currentShots = 0;
        this->left = left;
        this->scale = scale;
        this->rotation = rotation;
        this->lastShotTick = 0;
    }

};

#endif // ATTACKCOMPONENT_HPP