#include "AssetManager.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

AssetManager::AssetManager() {
    std::cout <<"[AssetManager] se crea\n";
}

AssetManager::~AssetManager() {
    std::cout <<"[AssetManager] se destruye\n";
}

void AssetManager::ClearAssets() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
}

void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& textureId,
    const std::string& filePath) {

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    textures.emplace(textureId, texture);

}

SDL_Texture* AssetManager::GetTexture(const std::string& textureId){
    return textures[textureId];
}