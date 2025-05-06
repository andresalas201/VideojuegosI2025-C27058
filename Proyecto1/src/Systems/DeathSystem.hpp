#ifndef DEATHSYSTEM_HPP
#define DEATHSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/DeathEvent.hpp"

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
        }
};

#endif // DEATHSYSTEM_HPP