#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>

struct Entity{
    
    std::string imgPath;
    int imgWidth = 0;
    int imgHeight = 0;
    double pX;
    double pY;
    double vX;
    double vY;
    double angle;
    SDL_Texture* imgTexture = nullptr;
    SDL_RendererFlip imgFlip = SDL_FLIP_NONE;

    std::string label = "";
    SDL_Texture* txtTexture = nullptr;
    glm::vec2 txtPos = glm::vec2();
    int txtWidth = 0;
    int txtHeight = 0;
    double txtAngle = 0.0;
};