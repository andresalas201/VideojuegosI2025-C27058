#include "AssetManager.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

AssetManager::AssetManager() {
    std::cout <<"[ASSETMANAGER] se crea\n";
}

AssetManager::~AssetManager() {
    std::cout <<"[ASSETMANAGER] se destruye\n";
}

void AssetManager::ClearAssets() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto font : fonts) {
        TTF_CloseFont(font.second);
    }
    fonts.clear();

    for(auto sound : sounds) {
        SDL_CloseAudioDevice(sound.second->soundDevice);
        SDL_FreeWAV(sound.second->soundBuffer);
        delete sound.second;
    }
    sounds.clear();
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

void AssetManager::AddFont(const std::string& fontId, const std::string& filePath,
    int fontSize) {

    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (font == NULL) {
        std::string error = TTF_GetError();
        std::cerr << "[ASSETMANAGER] " << error << std::endl;
        return;
    }
    fonts.emplace(fontId, font);
}

TTF_Font* AssetManager::GetFont(const std::string& fontId) {
    return fonts[fontId];
}

static void soundCallback(void* voidSystem, Uint8* stream, int len) {
    SoundStruct* soundStruct = static_cast<SoundStruct*>(voidSystem);
    if (soundStruct->soundBuffer == nullptr || soundStruct->soundLength == 0) {
        SDL_memset(stream, 0, len);
        return;
    }

    Uint32 remaining = soundStruct->soundLength - soundStruct->soundPosition;
    if (remaining > (Uint32)len) {
        remaining = len;
    }

    SDL_memcpy(stream, soundStruct->soundBuffer + soundStruct->soundPosition, remaining);
    soundStruct->soundPosition += remaining;
}

void AssetManager::AddSound(const std::string& soundId, const std::string& filePath) {
    SoundStruct* soundStruct = new SoundStruct();
    soundStruct->soundBuffer = NULL;
    soundStruct->soundLength = 0;
    soundStruct->soundPosition = 0;
    soundStruct->isPlayingSound = false;
    soundStruct->filePath = filePath;
    if (SDL_LoadWAV(filePath.c_str(), &soundStruct->soundSpec, &soundStruct->soundBuffer, &soundStruct->soundLength) == NULL) {
        std::cerr << "[ASSETMANAGER] Error al cargar sonido: " << SDL_GetError() << std::endl;
        delete soundStruct;
        return;
    }
    soundStruct->soundSpec.callback = soundCallback;
    soundStruct->soundSpec.userdata = soundStruct;
    soundStruct->soundDevice = SDL_OpenAudioDevice(NULL, 0, &soundStruct->soundSpec, NULL, 0);
    sounds.emplace(soundId, soundStruct);
}

SoundStruct* AssetManager::GetSound(const std::string& soundId) {
    return sounds[soundId];
}

