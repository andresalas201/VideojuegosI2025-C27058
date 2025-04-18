#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>

class AssetManager {
    private:

        std::map<std::string, SDL_Texture*> textures;


    public:

        AssetManager();
        ~AssetManager();

        void ClearAssets();

        void AddTexture(SDL_Renderer* renderer, const std::string& textureId,
            const std::string& filePath);
        SDL_Texture* GetTexture(const std::string& textureId);
};

#endif // ASSETMANAGER_HPP