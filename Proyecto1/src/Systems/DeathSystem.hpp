#ifndef DEATHSYSTEM_HPP
#define DEATHSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/DeathEvent.hpp"
#include "AudioSystem.hpp"

class DeathSystem : public System {
    public:
        DeathSystem() {
            RequireComponent<SpriteComponent>();
            RequireComponent<TransformComponent>();
        }

        void SubscribeToDeathEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<DeathEvent, DeathSystem>(this, &DeathSystem::OnDeath);
        }

        void Update(int MILISECS_PER_FRAME, int FPS, int windowHeight) {
            Uint32 maxTime = MILISECS_PER_FRAME * FPS * 0.5;
            for (auto& entity : GetSystemEntities()) {
                Entity& a = entity;
                if(a.GetComponent<SpriteComponent>().isDead) {
                    auto sprite = a.GetComponent<SpriteComponent>();
                    if (a.HasComponent<PlayerComponent>()) {
                        if (a.GetComponent<TransformComponent>().position.y > windowHeight) {
                            a.Kill();
                        }
                    } else if ((SDL_GetTicks() - sprite.deathTime) > maxTime) {
                        a.Kill();
                    }
                }
            }
        }

        void OnDeath(DeathEvent& e) {
            std::cout << "[DEATHSYSTEM] Se muere la entidad "  << e.a.GetId() << std::endl;
            if(e.a.HasComponent<SoundComponent>()) {
                std::string soundPath = e.a.GetComponent<SoundComponent>().soundName;
                e.a.registry->GetSystem<AudioSystem>().playSound(
                        Game::GetInstance().assetManager->GetSound(soundPath));
            }
            if(e.a.HasComponent<ShotComponent>() || e.a.HasComponent<UpgradeComponent>()) {
                if (e.a.HasComponent<FatherComponent>()) {
                    auto& father = e.a.GetComponent<FatherComponent>();
                    if(father.father->currentShots)father.father->currentShots --;
                }
                e.a.Kill();
                return;
            }
            if (e.a.HasComponent<SpriteComponent>()) {
                auto& sprite = e.a.GetComponent<SpriteComponent>();
                sprite.isDead = true;
                sprite.deathTime = SDL_GetTicks();
            }
            if (e.a.HasComponent<CircleColliderComponent>()) {
                auto& collider = e.a.GetComponent<CircleColliderComponent>();
                collider.isDead = true;
            }
        }
};

#endif // DEATHSYSTEM_HPP