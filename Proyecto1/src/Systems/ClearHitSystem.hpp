#ifndef CLEARHITSYSTEM_HPP
#define CLEARHITSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"

class ClearHitSystem : public System {
    public:
        ClearHitSystem() {
            RequireComponent<SpriteComponent>();
        }

        void Update(int MILLISECS_PER_FRAME, int FPS) {
            Uint32 twoSeconds = MILLISECS_PER_FRAME * FPS * 1;
            for (auto& entity : GetSystemEntities()) {
                Entity& a = entity;
                if (!a.GetComponent<SpriteComponent>().isHit) continue;
                auto& sprite = a.GetComponent<SpriteComponent>();
                if (SDL_GetTicks() - sprite.hitTime >= twoSeconds) {
                    sprite.isHit = false;
                }   
            }
        }

};

#endif // CLEARHITSYSTEM_HPP