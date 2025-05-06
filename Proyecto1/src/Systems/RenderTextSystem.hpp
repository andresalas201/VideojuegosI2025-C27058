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

class RenderTextSystem : public System { 
    public:
        RenderTextSystem() {
            RequireComponent<TextComponent>();
            RequireComponent<TransformComponent>();
        }

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