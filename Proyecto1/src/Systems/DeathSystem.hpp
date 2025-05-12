#ifndef DEATHSYSTEM_HPP
#define DEATHSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"
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

        void OnDeath(DeathEvent& e) {
            // TODO(any) Implementar la muerte
            if(e.a.HasComponent<SoundComponent>()) {
                e.a.registry->GetSystem<AudioSystem>().playSound(
                        e.a.GetComponent<SoundComponent>().soundPath);
            }
        }
};

#endif // DEATHSYSTEM_HPP