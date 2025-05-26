#ifndef DROPCOMPONENT_HPP
#define DROPCOMPONENT_HPP

#include <sol/sol.hpp>

struct DropComponent {
    int increase;
    std::string path;
    int width;
    int height;
    double rotation;
    std::string textureId;
    SDL_Rect srcRect;
    std::string soundName;

    DropComponent(int increase = 1, const std::string& path = "none", int width = 0,
        int height = 0, double rotation = 0, const std::string& textureId = "none",
        int srcX = 0, int srcY = 0, const std::string& soundName = "none") {
        this->increase = increase;
        this->path = path;
        this->width = width;
        this->height = height;
        this->rotation = rotation;
        this->textureId = textureId;
        this->srcRect = {srcX, srcY, width, height};
        this->soundName = soundName;
    }
};

#endif // DROPCOMPONENT_HPP