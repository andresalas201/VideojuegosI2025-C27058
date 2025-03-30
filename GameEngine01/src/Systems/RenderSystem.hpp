#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../AssetManager/AssetManager.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"

class RenderSystem : public System {
    public:
        RenderSystem() {
            RequireComponent<SpriteComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update(SDL_Renderer* renderer, 
            const std::unique_ptr<AssetManager>& assetManager) {
            
            std::vector<Entity> entityTest = GetSystemEntities();
            for (auto entity : GetSystemEntities()) {
                const auto sprite = entity.GetComponent<SpriteComponent>();
                const auto transform = entity.GetComponent<TransformComponent>();
                SDL_Rect srcRect = sprite.srcRect;
                SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
                };
                
                SDL_RenderCopyEx(
                    renderer,
                    assetManager->GetTexture(sprite.textureId),
                    &srcRect,
                    &dstRect,
                    transform.rotation,
                    NULL,
                    SDL_FLIP_NONE
                );
            }
        }
};


#endif // RENDERSYSTEM_HPP