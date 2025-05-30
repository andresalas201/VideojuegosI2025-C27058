/**
 * @file RenderTextSystem.hpp
 * @brief Header file for the RenderTextSystem class
 */

#ifndef RENDERTEXTSYSTEM_HPP
#define RENDERTEXTSYSTEM_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <iostream>
#include "../ECS/ECS.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../AssetManager/AssetManager.hpp"

/**
 * @class RenderTextSystem
 * @brief System responsible for rendering text entities to the screen
 * 
 * This system handles the rendering of text components by creating SDL textures
 * from text strings and rendering them at the appropriate positions and scales.
 * It requires entities to have both TextComponent and TransformComponent.
 */
class RenderTextSystem : public System {
public:
    /**
     * @brief Constructor for RenderTextSystem
     * 
     * Sets up the system to require TextComponent and TransformComponent
     * for entities to be processed by this system.
     */
    RenderTextSystem() {
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }
    
    /**
     * @brief Updates and renders all text entities
     * 
     * Iterates through all entities with required components, creates SDL surfaces
     * and textures from their text data, and renders them to the screen at the
     * positions and scales specified by their transform components.
     * 
     * @param renderer Pointer to the SDL renderer used for drawing
     * @param assetManager Unique pointer to the asset manager containing fonts
     */
    void update(SDL_Renderer* renderer,
                const std::unique_ptr<AssetManager>& assetManager) {
        for (auto entity : GetSystemEntities()){
            auto& text = entity.GetComponent<TextComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            SDL_Surface* surface = TTF_RenderText_Blended(
                assetManager->GetFont(text.fontId), text.text.c_str(), text.color);
            text.width = surface->w;
            text.height = surface->h;
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                text.width * static_cast<int>(transform.scale.x),
                text.height * static_cast<int>(transform.scale.y)
            };
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
};
#endif // RENDERTEXTSYSTEM_HPP