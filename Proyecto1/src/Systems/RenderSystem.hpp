/**
 * @file RenderSystem.hpp
 * @brief Rendering system implementation for ECS architecture
 */

#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP
#include <SDL2/SDL.h>
#include "../AssetManager/AssetManager.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"

/**
 * @class RenderSystem
 * @brief System responsible for rendering sprites to the screen
 * 
 * This system handles the visual rendering of all entities with sprite and transform
 * components. It supports different visual states including normal, hit, and death
 * animations with appropriate sprite rectangle switching and hit effect blinking.
 */
class RenderSystem : public System {
public:
    /**
     * @brief Constructor for RenderSystem
     * 
     * Sets up the system to require SpriteComponent and TransformComponent
     * for all entities it will process.
     */
    RenderSystem() {
        RequireComponent<SpriteComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Renders all entities with sprites to the screen
     * 
     * @param renderer SDL renderer used for drawing operations
     * @param assetManager Reference to asset manager for texture retrieval
     * 
     * Iterates through all renderable entities and draws them with appropriate
     * visual states:
     * - Dead entities use death sprite rectangle
     * - Hit entities blink between normal and hit sprite rectangles
     * - Normal entities use standard sprite rectangle
     * 
     * Applies transform scaling, positioning, and rotation during rendering.
     */
    void Update(SDL_Renderer* renderer,
    const std::unique_ptr<AssetManager>& assetManager) {
        std::vector<Entity> entityTest = GetSystemEntities();
        for (auto entity : GetSystemEntities()) {
            auto& sprite = entity.GetComponent<SpriteComponent>();
            const auto transform = entity.GetComponent<TransformComponent>();
            SDL_Rect srcRect = sprite.srcRect;
            if (sprite.isDead) {
                srcRect = sprite.deathRect;
            } else if (sprite.isHit) {
                if (sprite.showHitCounter % 4 == 0) {
                    srcRect = sprite.hitSrcRect;
                }
                sprite.showHitCounter++;
            }
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